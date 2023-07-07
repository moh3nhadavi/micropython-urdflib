#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "py/objstr.h"


// #include "extmod/sord/sord.h"
#include "lib/urdflib-ext/sord/sord.h"
// #include "../lib/test.h"

#include "terms.h"
#include "graph.h"



STATIC mp_obj_t urdflib_info(void)
{
    // mp_print_str(&mp_plat_print, intToString(m_get_current_bytes_allocated()));
    // mp_print_str(&mp_plat_print, "\n");
    // SordWorld *world = sord_world_new();
    // mp_print_str(&mp_plat_print, intToString(m_get_current_bytes_allocated()));
    // mp_print_str(&mp_plat_print, "\n");
    // SordNode *node = sord_new_blank(world, (const uint8_t *)_generateRandomString2(16));
    // mp_print_str(&mp_plat_print, intToString(m_get_current_bytes_allocated()));
    // mp_print_str(&mp_plat_print, "\n");
    // mp_print_str(&mp_plat_print, (char *)sord_node_get_string(node));
    // mp_print_str(&mp_plat_print, "\n");
    return mp_obj_new_str("urdflib v0.0.1", 14);
    // return mp_obj_new_str(moh3n_test(), 17);
    // return mp_obj_new_str((char *)sord_node_get_string(node), 16);
}
MP_DEFINE_CONST_FUN_OBJ_0(urdflib_info_obj, urdflib_info);


STATIC const mp_rom_map_elem_t mp_module_urdflib_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_urdflib)},
    {MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&urdflib_info_obj)},
    {MP_ROM_QSTR(MP_QSTR_BNode),(mp_obj_t)&urdflib_bnode_type},
    {MP_ROM_QSTR(MP_QSTR_URIRef),(mp_obj_t)&urdflib_uriref_type},
    {MP_ROM_QSTR(MP_QSTR_Literal),(mp_obj_t)&urdflib_literal_type},
    {MP_ROM_QSTR(MP_QSTR_Graph), (mp_obj_t)&urdflib_graph_type},

};
STATIC MP_DEFINE_CONST_DICT(mp_module_urdflib_globals, mp_module_urdflib_globals_table);

const mp_obj_module_t mp_module_urdflib = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&mp_module_urdflib_globals,
};
MP_REGISTER_MODULE(MP_QSTR_urdflib, mp_module_urdflib);