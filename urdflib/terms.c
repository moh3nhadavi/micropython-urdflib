#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#include "globals.h"
#include "terms.h"
#include "middleware/terms.h"

typedef struct _bnode_obj_t
{
    mp_obj_base_t base;
    BNode *bnode;
} bnode_obj_t;

const mp_obj_type_t urdflib_bnode_type;

typedef struct _uriref_obj_t
{
    mp_obj_base_t base;
    URIRef *uri_ref;
} uriref_obj_t;

const mp_obj_type_t urdflib_uriref_type;

typedef struct _literal_obj_t
{
    mp_obj_base_t base;
    Literal *literal;
} literal_obj_t;

const mp_obj_type_t urdflib_literal_type;

char *_generateRandomString(int length)
{
    static const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *randomString = (char *)malloc((length + 1) * sizeof(char));
    if (randomString == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        randomString[i] = charset[index];
    }
    randomString[length] = '\0';
    return randomString;
}

STATIC mp_obj_t bnode_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    // check the number of arguments
    mp_arg_check_num(n_args, n_kw, 0, 1, true);

    bnode_obj_t *self = m_new_obj(bnode_obj_t);
    self->base.type = &urdflib_bnode_type;
    urdflib_globals_init0();

    if (n_args == 1 && strcmp(mp_obj_get_type_str(args[0]), "str") == 0)
    {
        self->bnode = middleware_terms_bnode_new(mp_obj_str_get_str(args[0]));
    }
    else
    {
        char *randomString = _generateRandomString(16);
        self->bnode = middleware_terms_bnode_new(randomString);
    }
    return MP_OBJ_FROM_PTR(self);
}

STATIC void bnode_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    (void)kind;
    bnode_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(print, "URDFLib;BNode(");
    mp_print_str(print, (char *)sord_node_get_string(self->bnode->node));
    mp_print_str(print, ")");
    mp_print_str(print, mp_obj_get_type_str(self_in));
}

STATIC const mp_rom_map_elem_t bnode_locals_dict_table[] = {
    // {MP_ROM_QSTR(MP_QSTR_length), MP_ROM_PTR(&graph_len_obj)},
};
STATIC MP_DEFINE_CONST_DICT(bnode_locals_dict, bnode_locals_dict_table);

const mp_obj_type_t urdflib_bnode_type = {
    {&mp_type_type},
    .name = MP_QSTR_BNode,
    .print = bnode_print,
    .make_new = bnode_make_new,
    .locals_dict = (mp_obj_dict_t *)&bnode_locals_dict,
};

STATIC mp_obj_t uriref_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    // check the number of arguments
    mp_arg_check_num(n_args, n_kw, 1, 2, true);

    uriref_obj_t *self = m_new_obj(uriref_obj_t);
    self->base.type = &urdflib_uriref_type;
    urdflib_globals_init0();
    const char *uri = mp_obj_str_get_str(args[0]);
    if (n_args == 2)
    {
        const char *base = mp_obj_str_get_str(args[1]);
        self->uri_ref = middleware_terms_uriref_new(uri, base);
    }
    else
    {
        self->uri_ref = middleware_terms_uriref_new(uri, NULL);
    }
    return MP_OBJ_FROM_PTR(self);
}

STATIC void uriref_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    (void)kind;
    uriref_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(print, "URDFLib;URIRef(");
    mp_print_str(print, (char *)sord_node_get_string(self->uri_ref->node));
    mp_print_str(print, ")");
}

STATIC const mp_rom_map_elem_t uriref_locals_dict_table[] = {
    // {MP_ROM_QSTR(MP_QSTR_length), MP_ROM_PTR(&graph_len_obj)},
};
STATIC MP_DEFINE_CONST_DICT(uriref_locals_dict, uriref_locals_dict_table);

const mp_obj_type_t urdflib_uriref_type = {
    {&mp_type_type},
    .name = MP_QSTR_URIRef,
    .print = uriref_print,
    .make_new = uriref_make_new,
    .locals_dict = (mp_obj_dict_t *)&uriref_locals_dict,
};

char *intToString(int value)
{
    int length = snprintf(NULL, 0, "%d", value);
    char *str = (char *)malloc((length + 1) * sizeof(char));
    snprintf(str, length + 1, "%d", value);
    return str;
}

char *floatToString(float value)
{
    int length = snprintf(NULL, 0, "%f", value);
    char *str = (char *)malloc((length + 1) * sizeof(char));
    snprintf(str, length + 1, "%f", value);
    return str;
}

char *boolToString(int value)
{
    if (value)
    {
        return strdup("true");
    }
    else
    {
        return strdup("false");
    }
}

STATIC mp_obj_t literal_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    enum
    {
        ARG_value,
        ARG_datatype,
        ARG_language
    };
    mp_arg_check_num(n_args, n_kw, 1, 3, true);

    literal_obj_t *self = m_new_obj(literal_obj_t);
    self->base.type = &urdflib_literal_type;
    urdflib_globals_init0();

    static const mp_arg_t allowed_args[] = {
        {MP_QSTR_value, MP_ARG_REQUIRED | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL}},
        // {MP_QSTR_datatype, MP_ARG_OBJ, {.u_rom_obj = MP_ROM_PTR(&urdflib_uriref_type)}},
        {MP_QSTR_datatype, MP_ARG_REQUIRED | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL}},
        {MP_QSTR_language, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL}},
    };

    mp_arg_val_t args_parsed[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, args_parsed);
    
    mp_obj_t tempVal = args_parsed[ARG_value].u_obj;
    const char *value = NULL;
    if (strcmp(mp_obj_get_type_str(args_parsed[ARG_value].u_obj), "int") == 0)
    {
        value = intToString(mp_obj_get_int(tempVal));
    }
    else if (strcmp(mp_obj_get_type_str(args_parsed[ARG_value].u_obj), "float") == 0)
    {
        value = floatToString(mp_obj_get_float(tempVal));
    }
    else if (strcmp(mp_obj_get_type_str(args_parsed[ARG_value].u_obj), "str") == 0)
    {
        value = strdup(mp_obj_str_get_str(tempVal));
    }
    else if (strcmp(mp_obj_get_type_str(args_parsed[ARG_value].u_obj), "bool") == 0)
    {
        value = boolToString(mp_obj_get_int(tempVal));
    }
    else
    {
        mp_raise_ValueError("Unknown type");
    }

    // TODO: Accept the datatype as a URIRef object
    // URIRef *datatype = NULL;
    const char *datatype = NULL;
    if(mp_obj_is_str(args_parsed[ARG_datatype].u_obj)) {
        datatype = mp_obj_str_get_str(args_parsed[ARG_datatype].u_obj);
    }
    // if(mp_obj_is_type(args_parsed[ARG_datatype].u_obj, &urdflib_uriref_type)) {
    //     datatype = MP_OBJ_TO_PTR(args_parsed[ARG_datatype].u_obj);
    //     // datatype = get_uriref_obj(args_parsed[ARG_datatype].u_obj);
    // }
    // else {
    //     datatype = NULL;
    // }

    const char *language = NULL;
    if(args_parsed[ARG_language].u_obj != MP_OBJ_NULL && mp_obj_is_str(args_parsed[ARG_language].u_obj)) {
        language = mp_obj_str_get_str(args_parsed[ARG_language].u_obj);
    }

    // const char *language = NULL;
    // if (strcmp(mp_obj_get_type_str(args_parsed[ARG_language].u_obj), "str") == 0) 
    // {
    //     mp_print_str(&mp_plat_print, "Language:\n");
    //     language = mp_obj_str_get_str(args_parsed[ARG_language].u_obj);
    // }

    self->literal = middleware_terms_literal_new(value, datatype, language);
    return MP_OBJ_FROM_PTR(self);
}

STATIC void literal_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    (void)kind;
    literal_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(print, "URDFLib;Literal(");
    mp_print_str(print, (char *)sord_node_get_string(self->literal->node));
    mp_print_str(print, ",");
    mp_print_str(print, (char *)sord_node_get_string(sord_node_get_datatype(self->literal->node)));
    if(sord_node_get_language(self->literal->node) != NULL){
        mp_print_str(print, ",");
        mp_print_str(print, sord_node_get_language(self->literal->node));    
    }
    mp_print_str(print, ")");
}

STATIC const mp_rom_map_elem_t literal_locals_dict_table[] = {
    // {MP_ROM_QSTR(MP_QSTR_length), MP_ROM_PTR(&graph_len_obj)},
};
STATIC MP_DEFINE_CONST_DICT(literal_locals_dict, literal_locals_dict_table);

const mp_obj_type_t urdflib_literal_type = {
    {&mp_type_type},
    .name = MP_QSTR_Literal,
    .print = literal_print,
    .make_new = literal_make_new,
    .locals_dict = (mp_obj_dict_t *)&literal_locals_dict,
};
