#include <stdlib.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "py/objstr.h"

#include "../lib/sord/sord.h"

#include "terms.h"
#include "graph.h"

#include "middleware.h"


// void graph_serialize(Graph *g, const char *filename, SerdSyntax syntax)
// {
//     FILE *output_file = fopen(filename, "w");
//     if (!output_file) {
//         fprintf(stderr, "Failed to open output file '%s'\n", filename);
//         return;
//     }
//     SerdURI *base_uri = {0};
//     serd_env_get_base_uri(g->env, base_uri);
//     SerdWriter *writer = serd_writer_new(
//         syntax,
//         SERD_STYLE_ABBREVIATED,
//         g->env,
//         base_uri,
//         serd_file_sink,
//         output_file);
//     sord_write(g->model, writer, NULL);
//     serd_writer_finish(writer);
//     fclose(output_file);
// }

STATIC mp_obj_t urdflib_info(void)
{
    return mp_obj_new_str("urdflib v0.0.1", 14);
}
MP_DEFINE_CONST_FUN_OBJ_0(urdflib_info_obj, urdflib_info);

STATIC mp_obj_t urdflib_model_new(void)
{
    return MP_OBJ_FROM_PTR(model_new());
}
MP_DEFINE_CONST_FUN_OBJ_0(urdflib_model_new_obj, urdflib_model_new);

STATIC mp_obj_t urdflib_length(const mp_obj_t model_in)
{
    Model *model = MP_OBJ_TO_PTR(model_in);
    return mp_obj_new_int(middleware_num_quads(model));
}
MP_DEFINE_CONST_FUN_OBJ_1(urdflib_length_obj, urdflib_length);

STATIC const mp_rom_map_elem_t mp_module_urdflib_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_urdflib)},
    {MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&urdflib_info_obj)},
    {MP_ROM_QSTR(MP_QSTR_new_model), MP_ROM_PTR(&urdflib_model_new_obj)},
    {MP_ROM_QSTR(MP_QSTR_length), MP_ROM_PTR(&urdflib_length_obj)},
    {MP_ROM_QSTR(MP_QSTR_BNode),(mp_obj_t)&urdflib_bnode_type},
    {MP_ROM_QSTR(MP_QSTR_URIRef),(mp_obj_t)&urdflib_uriref_type},
    {MP_ROM_QSTR(MP_QSTR_Literal),(mp_obj_t)&urdflib_literal_type},
    {MP_OBJ_NEW_QSTR(MP_QSTR_Graph), (mp_obj_t)&urdflib_graph_type},

};
STATIC MP_DEFINE_CONST_DICT(mp_module_urdflib_globals, mp_module_urdflib_globals_table);

const mp_obj_module_t mp_module_urdflib = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&mp_module_urdflib_globals,
};
MP_REGISTER_MODULE(MP_QSTR_urdflib, mp_module_urdflib);