#include <stdio.h>
#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#include "../lib/sord/sord.h"

#include "graph.h"

typedef struct _graph_obj_t{
    mp_obj_base_t base;
} graph_obj_t;

const mp_obj_type_t urdflib_graph_type;

STATIC mp_obj_t graph_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    graph_obj_t *self = m_new_obj(graph_obj_t);
    self->base.type = &urdflib_graph_type;
    
    return MP_OBJ_FROM_PTR(self);
}

STATIC void graph_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void)kind;
    // Graph_obj_t *self = m_new_obj(self_in);
    mp_print_str(print, "URDFLib;Graph()");
}

STATIC mp_obj_t graph_add(mp_obj_t self_in,mp_obj_t subject, mp_obj_t predicate, mp_obj_t object) {
    // Graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(&mp_plat_print, "Graph add:\nsubject: ");
    mp_obj_print_helper(&mp_plat_print, subject, PRINT_REPR);
    mp_print_str(&mp_plat_print, "\n predicate: ");
    mp_obj_print_helper(&mp_plat_print, predicate, PRINT_REPR);
    mp_print_str(&mp_plat_print, "\n object: ");
    mp_obj_print_helper(&mp_plat_print, object, PRINT_REPR);
    // mp_printf(&mp_plat_print, "Graph add: %s %s %s\n", mp_obj_str_get_str(subject), mp_obj_str_get_str(predicate), mp_obj_str_get_str(object));
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_3(graph_add_obj, graph_add);

STATIC const mp_rom_map_elem_t graph_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&graph_add_obj) },
};
STATIC MP_DEFINE_CONST_DICT(graph_locals_dict, graph_locals_dict_table);

const mp_obj_type_t urdflib_graph_type = {
    { &mp_type_type },
    .name = MP_QSTR_urdflib,
    .print = graph_print,
    .make_new = graph_make_new,
    .locals_dict = (mp_obj_dict_t*)&graph_locals_dict,
};
