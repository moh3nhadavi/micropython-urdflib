#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#include "../lib/sord/sord.h"
#include "globals.h"
#include "terms.h"
#include "middleware/terms.h"

typedef struct _bnode_obj_t
{
    mp_obj_base_t base;
    BNode *bnode;
} bnode_obj_t;

const mp_obj_type_t urdflib_bnode_type;

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

    if (strcmp(mp_obj_get_type_str(args[0]), "str") == 0)
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
}

STATIC const mp_rom_map_elem_t bnode_locals_dict_table[] = {
    // {MP_ROM_QSTR(MP_QSTR_length), MP_ROM_PTR(&graph_len_obj)},
};
STATIC MP_DEFINE_CONST_DICT(bnode_locals_dict, bnode_locals_dict_table);

const mp_obj_type_t urdflib_bnode_type = {
    {&mp_type_type},
    .name = MP_QSTR_urdflib,
    .print = bnode_print,
    .make_new = bnode_make_new,
    .locals_dict = (mp_obj_dict_t *)&bnode_locals_dict,
};