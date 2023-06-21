#include <stdio.h>
#include <string.h>
#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#include "../lib/sord/sord.h"

#include "graph.h"
#include "globals.h"
#include "middleware.h"

typedef struct _graph_obj_t
{
    mp_obj_base_t base;
    Graph *graph;
} graph_obj_t;

const mp_obj_type_t urdflib_graph_type;



STATIC mp_obj_t graph_remove(mp_obj_t self_in, mp_obj_t triple_in)
{
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_tuple_t *triple = MP_OBJ_TO_PTR(triple_in);
    if (triple->len != 3)
    {
        mp_raise_ValueError("Triple must be a tuple of length 3");
    }
    middleware_graph_remove_triple(self->graph,
                                    mp_obj_str_get_str(triple->items[0]),
                                    mp_obj_str_get_str(triple->items[1]),
                                    mp_obj_str_get_str(triple->items[2]));
    
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(graph_remove_obj, graph_remove);


STATIC mp_obj_t graph_subjects(mp_obj_t self_in){
    mp_print_str(&mp_plat_print, "subjects\n");
    graph_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_list_t *subjects = m_new_obj(mp_obj_list_t);
    subjects->base.type = &mp_type_list;
    subjects->len = 0;
    subjects->alloc = 0;
    subjects->items = NULL;
    mp_print_str(&mp_plat_print, "1\n");
    SordIter *iter = sord_begin(self->graph->model->model);
    mp_print_str(&mp_plat_print, "2\n");
    for (; !sord_iter_end(iter); sord_iter_next(iter))
    {
        SordQuad quad = {NULL, NULL, NULL, NULL};
        sord_iter_get(iter, quad);
        if (sord_node_equals(quad[3], self->graph->node))
        {
            mp_print_str(&mp_plat_print, "3\n");
            GET_STR_DATA_LEN(sord_node_get_string(quad[0]), str, str_len);
            // char out_str[str_len];
            // strcpy(out_str, (char *)str);
            // for(size_t i=0; i < (str_len-1)/2; i++) {
            //     byteswap(out_str[i], out_str[str_len-i-1]);
            // }
            mp_obj_list_append(subjects, mp_obj_new_str((char *)str, str_len));
            mp_print_str(&mp_plat_print, "4\n");
        }
    }
    sord_iter_free(iter);
    mp_print_str(&mp_plat_print, "5\n");
    // return subjects;
    // int length;
    // char *subjects = middleware_graph_get_subjects(self->graph, &length);
    middleware_graph_get_subjects(self->graph);
    // for (int i = 0; i < length; i++)
    // {
    //     mp_print_str(&mp_plat_print, subjects[i]);
    // }
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(graph_subjects_obj, graph_subjects);

STATIC const mp_rom_map_elem_t graph_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_length), MP_ROM_PTR(&graph_len_obj)},
    {MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&graph_close_obj)},
    {MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&graph_add_obj)},
    {MP_ROM_QSTR(MP_QSTR_remove), MP_ROM_PTR(&graph_remove_obj)},

    {MP_ROM_QSTR(MP_QSTR_subjects), MP_ROM_PTR(&graph_subjects_obj)},
};
STATIC MP_DEFINE_CONST_DICT(graph_locals_dict, graph_locals_dict_table);

const mp_obj_type_t urdflib_graph_type = {
    {&mp_type_type},
    .name = MP_QSTR_urdflib,
    .print = graph_print,
    .make_new = graph_make_new,
    .locals_dict = (mp_obj_dict_t *)&graph_locals_dict,
};
