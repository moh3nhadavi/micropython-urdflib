#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#include "lib/urdflib-ext/sord/sord.h"

#include "globals.h"
#include "graph.h"
#include "terms.h"

STATIC mp_obj_t graph_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    // check the number of arguments
    mp_arg_check_num(n_args, n_kw, 0, 1, true);

    graph_obj_t *self = m_new_obj(graph_obj_t);
    self->base.type = &urdflib_graph_type;
    urdflib_globals_init0();

    mp_print_str(&mp_plat_print, "graph_make_new\n");
    if (n_args == 0)
    {
        bnode_obj_t *_bnode = m_new_obj(bnode_obj_t);
        _bnode->base.type = &urdflib_bnode_type;
        _bnode->bnode = middleware_terms_bnode_new(_generateRandomString(16));
        self->graph = middleware_graph_graph_new(_bnode->bnode->node);
    }
    else
    {
        if (mp_obj_is_type(args[0], &urdflib_uriref_type))
        {
            uriref_obj_t *_uriref = MP_OBJ_TO_PTR(args[0]);
            self->graph = middleware_graph_graph_new(_uriref->uri_ref->node);
        }
        else if (mp_obj_is_type(args[0], &urdflib_bnode_type))
        {
            bnode_obj_t *_bnode = MP_OBJ_TO_PTR(args[0]);
            self->graph = middleware_graph_graph_new(_bnode->bnode->node);
        }
        else
        {
            mp_raise_TypeError((mp_rom_error_text_t) "The optional argument must be a URIRef or BNode");
        }
    }
    return MP_OBJ_FROM_PTR(self);
}

STATIC void graph_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    (void)kind;
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(print, "URDFLib;Graph(");
    mp_print_str(print, (const char *)sord_node_get_string(self->graph->context));
    mp_print_str(print, ")");
}

STATIC mp_obj_t graph_len(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(middleware_graph_num_quads(self->graph));
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_len_obj, graph_len);

STATIC mp_obj_t graph_close(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(&mp_plat_print, "graph_close\n");
    middleware_graph_close(self->graph);
    mp_print_str(&mp_plat_print, "done\n");
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_close_obj, graph_close);

SordNode **_extractTriple(mp_obj_tuple_t *triple_in)
{
    SordNode **nodes = malloc(3 * sizeof(SordNode *));
    for (int8_t i = 0; i < 3; i++)
    {
        if (strcmp(mp_obj_get_type_str(triple_in->items[i]), "URIRef") != 0)
        {
            uriref_obj_t *_uriref = MP_OBJ_TO_PTR(triple_in->items[i]);
            nodes[i] = _uriref->uri_ref->node;
        }
        else if (strcmp(mp_obj_get_type_str(triple_in->items[i]), "BNode") != 0)
        {
            bnode_obj_t *_bnode = MP_OBJ_TO_PTR(triple_in->items[i]);
            nodes[i] = _bnode->bnode->node;
        }
        else if (strcmp(mp_obj_get_type_str(triple_in->items[i]), "Literal") != 0)
        {
            literal_obj_t *_literal = MP_OBJ_TO_PTR(triple_in->items[i]);
            nodes[i] = _literal->literal->node;
        }
        else
        {
            mp_raise_ValueError((mp_rom_error_text_t) "Wrong type of subject");
        }
    }
    return nodes;
}

STATIC mp_obj_t graph_add(mp_obj_t self_in, mp_obj_t triple_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_tuple_t *triple = MP_OBJ_TO_PTR(triple_in);
    if (triple->len != 3)
    {
        mp_raise_ValueError((mp_rom_error_text_t) "Triple must be a tuple of length 3");
    }

    SordNode **nodes = _extractTriple(triple);
    if (middleware_graph_add(self->graph, nodes[0], nodes[1], nodes[2]))
    {
        mp_print_str(&mp_plat_print, "Added to the graph\n");
    }
    else
    {
        mp_print_str(&mp_plat_print, "Failed to add to the graph\n");
    }
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(graph_add_obj, graph_add);

STATIC mp_obj_t graph_remove(mp_obj_t self_in, mp_obj_t triple_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_tuple_t *triple = MP_OBJ_TO_PTR(triple_in);
    if (triple->len != 3)
    {
        mp_raise_ValueError((mp_rom_error_text_t) "Triple must be a tuple of length 3");
    }
    SordNode **nodes = _extractTriple(triple);
    middleware_graph_remove(self->graph, nodes[0], nodes[1], nodes[2]);

    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(graph_remove_obj, graph_remove);

mp_obj_t sordNode_to_tuple_obj(SordNode *node)
{
    mp_print_str(&mp_plat_print, "sordNode_to_tuple_obj\n");
    if (strcmp(middleware_terms_get_type(node), "URIRef") == 0)
    {
        mp_print_str(&mp_plat_print, "3\n");
        uriref_obj_t *uriref = m_new_obj(uriref_obj_t);
        uriref->base.type = &urdflib_uriref_type;
        URIRef *_uri = (URIRef *)malloc(sizeof(URIRef));
        _uri->node = node;
        uriref->uri_ref = _uri;
        return MP_OBJ_FROM_PTR(uriref);
    }
    else if (strcmp(middleware_terms_get_type(node), "BNode") == 0)
    {
        mp_print_str(&mp_plat_print, "3-1\n");
        bnode_obj_t *bnode = m_new_obj(bnode_obj_t);
        bnode->base.type = &urdflib_bnode_type;
        BNode *_bnode = (BNode *)malloc(sizeof(BNode));
        _bnode->node = node;
        bnode->bnode = _bnode;
        return MP_OBJ_FROM_PTR(bnode);
    }
    else if (strcmp(middleware_terms_get_type(node), "Literal") == 0)
    {
        mp_print_str(&mp_plat_print, "3-2\n");
        literal_obj_t *literal = m_new_obj(literal_obj_t);
        literal->base.type = &urdflib_literal_type;
        Literal *_literal = (Literal *)malloc(sizeof(Literal));
        _literal->node = node;
        literal->literal = _literal;
        return MP_OBJ_FROM_PTR(literal);
    }
    else
    {
        mp_raise_ValueError((mp_rom_error_text_t) "Wrong type of subject");
    }
}

mp_obj_t sordNodes_to_tuple(SordNode **nodes, int array_size)
{
    mp_print_str(&mp_plat_print, "2\n");
    mp_obj_t tuple[array_size];
    for (int i = 0; i < array_size; i++)
    {
        mp_print_str(&mp_plat_print, "2-1\n");
        tuple[i] = sordNode_to_tuple_obj(nodes[i]);
        mp_print_str(&mp_plat_print, "2-2\n");
    }
    return mp_obj_new_tuple(array_size, tuple);
}

STATIC mp_obj_t graph_subjects(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int array_size = 0;
    mp_print_str(&mp_plat_print, "Getting subjects\n");
    SordNode **nodes = middleware_graph_get_nodes_of_quads(self->graph, &array_size, 0);
    mp_print_str(&mp_plat_print, "1\n");
    return sordNodes_to_tuple(nodes, array_size);
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_subjects_obj, graph_subjects);

STATIC mp_obj_t graph_predicates(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int array_size = 0;
    SordNode **nodes = middleware_graph_get_nodes_of_quads(self->graph, &array_size, 1);
    return sordNodes_to_tuple(nodes, array_size);
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_predicates_obj, graph_predicates);

STATIC mp_obj_t graph_objects(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int array_size = 0;
    SordNode **nodes = middleware_graph_get_nodes_of_quads(self->graph, &array_size, 2);
    return sordNodes_to_tuple(nodes, array_size);
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_objects_obj, graph_objects);

STATIC mp_obj_t graph_subject_predicates(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int subjects_size, predicates_size = 0;
    SordNode2D nodes = middleware_graph_get_2D_nodes_of_quads(self->graph, &subjects_size, &predicates_size, 0, 1);
    mp_obj_t tuple[2];
    tuple[0] = sordNodes_to_tuple(nodes.nodes1, subjects_size);
    tuple[1] = sordNodes_to_tuple(nodes.nodes2, predicates_size);
    return mp_obj_new_tuple(2, tuple);
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_subject_predicates_obj, graph_subject_predicates);

STATIC mp_obj_t graph_subject_objects(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int subjects_size, objects_size = 0;
    SordNode2D nodes = middleware_graph_get_2D_nodes_of_quads(self->graph, &subjects_size, &objects_size, 0, 2);
    mp_obj_t tuple[2];
    tuple[0] = sordNodes_to_tuple(nodes.nodes1, subjects_size);
    tuple[1] = sordNodes_to_tuple(nodes.nodes2, objects_size);
    return mp_obj_new_tuple(2, tuple);
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_subject_objects_obj, graph_subject_objects);

STATIC mp_obj_t graph_predicate_objects(mp_obj_t self_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int predicates_size, objects_size = 0;
    SordNode2D nodes = middleware_graph_get_2D_nodes_of_quads(self->graph, &predicates_size, &objects_size, 1, 2);
    mp_obj_t tuple[2];
    tuple[0] = sordNodes_to_tuple(nodes.nodes1, predicates_size);
    tuple[1] = sordNodes_to_tuple(nodes.nodes2, objects_size);
    return mp_obj_new_tuple(2, tuple);
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_predicate_objects_obj, graph_predicate_objects);

STATIC const mp_rom_map_elem_t graph_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_length), MP_ROM_PTR(&graph_len_obj)},
    {MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&graph_close_obj)},
    {MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&graph_add_obj)},
    {MP_ROM_QSTR(MP_QSTR_remove), MP_ROM_PTR(&graph_remove_obj)},

    {MP_ROM_QSTR(MP_QSTR_subjects), MP_ROM_PTR(&graph_subjects_obj)},
    {MP_ROM_QSTR(MP_QSTR_predicates), MP_ROM_PTR(&graph_predicates_obj)},
    {MP_ROM_QSTR(MP_QSTR_objects), MP_ROM_PTR(&graph_objects_obj)},
    {MP_ROM_QSTR(MP_QSTR_subject_predicates), MP_ROM_PTR(&graph_subject_predicates_obj)},
    {MP_ROM_QSTR(MP_QSTR_subject_objects), MP_ROM_PTR(&graph_subject_objects_obj)},
    {MP_ROM_QSTR(MP_QSTR_predicate_objects), MP_ROM_PTR(&graph_predicate_objects_obj)},

};
STATIC MP_DEFINE_CONST_DICT(graph_locals_dict, graph_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    urdflib_graph_type,
    MP_QSTR_Graph,
    MP_TYPE_FLAG_NONE,
    make_new, graph_make_new,
    print, graph_print,
    locals_dict, &graph_locals_dict);

// const mp_obj_type_t urdflib_graph_type = {
//     {&mp_type_type},
//     .name = MP_QSTR_Graph,
//     .print = graph_print,
//     .make_new = graph_make_new,
//     .locals_dict = (mp_obj_dict_t *)&graph_locals_dict,
// };