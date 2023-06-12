#include <stdio.h>
// #include <string.h>
#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#include "../lib/sord/sord.h"

#include "graph.h"
#include "middleware.h"

typedef struct _graph_obj_t
{
    mp_obj_base_t base;
    Graph *graph;
} graph_obj_t;

const mp_obj_type_t urdflib_graph_type;

STATIC mp_obj_t graph_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    // check the number of arguments
    mp_arg_check_num(n_args, n_kw, 0, 2, true);

    graph_obj_t *self = m_new_obj(graph_obj_t);
    self->base.type = &urdflib_graph_type;

    // check first argument -> model
    Model *model;
    if (args[0] == mp_const_none)
    {
        model = model_new();
    }
    else
    {
        model = MP_OBJ_TO_PTR(args[0]);
    }

    // check second argument -> base_uri
    const char *base_uri;
    if (args[1] == mp_const_none)
    {
        base_uri = mp_obj_new_str("http://example.org/", 18);
    }
    else
    {
        base_uri = mp_obj_str_get_str(args[1]);
    }

    // create graph
    self->graph = graph_new(model, base_uri);
    return MP_OBJ_FROM_PTR(self);
}

STATIC void graph_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    (void)kind;
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(print, "URDFLib;Graph(");
    mp_print_str(print, ")\n");
    SordIter *iter = sord_begin(self->graph->model->model);
    for (; !sord_iter_end(iter); sord_iter_next(iter))
    {
        SordQuad quad = {NULL, NULL, NULL, NULL};
        sord_iter_get(iter, quad);
        if (sord_node_equals(quad[3], self->graph->node))
        {
            printf("<%s> <%s> <%s> <%s>\n", sord_node_get_string(quad[0]), sord_node_get_string(quad[1]), sord_node_get_string(quad[2]), sord_node_get_string(quad[3]));
        }
    }
    sord_iter_free(iter);
}

// right now, we only support adding uris
STATIC mp_obj_t graph_add(mp_obj_t self_in, mp_obj_t triple_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_tuple_t *triple = MP_OBJ_TO_PTR(triple_in);
    if (triple->len != 3)
    {
        mp_raise_ValueError("Triple must be a tuple of length 3");
    }
    if (graph_add_triple(self->graph, mp_obj_str_get_str(triple->items[0]), mp_obj_str_get_str(triple->items[1]), mp_obj_str_get_str(triple->items[2])))
    {
        mp_print_str(&mp_plat_print, "Added to the graph\n");
    }
    else
    {
        mp_print_str(&mp_plat_print, "Failed to add to the graph\n");
    }

    // mp_print_str(&mp_plat_print, "Graph add:\nsubject: ");
    // mp_obj_print_helper(&mp_plat_print, subject, PRINT_REPR);
    // mp_print_str(&mp_plat_print, "\npredicate: ");
    // mp_obj_print_helper(&mp_plat_print, predicate, PRINT_REPR);
    // mp_print_str(&mp_plat_print, "\n");
    // mp_print_str(&mp_plat_print, "\n object: ");
    // mp_obj_print_helper(&mp_plat_print, object, PRINT_REPR);
    // mp_printf(&mp_plat_print, "Graph add: %s %s %s\n", mp_obj_str_get_str(subject), mp_obj_str_get_str(predicate), mp_obj_str_get_str(object));
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(graph_add_obj, graph_add);

STATIC const mp_rom_map_elem_t graph_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&graph_add_obj)},
};
STATIC MP_DEFINE_CONST_DICT(graph_locals_dict, graph_locals_dict_table);

const mp_obj_type_t urdflib_graph_type = {
    {&mp_type_type},
    .name = MP_QSTR_urdflib,
    .print = graph_print,
    .make_new = graph_make_new,
    .locals_dict = (mp_obj_dict_t *)&graph_locals_dict,
};
