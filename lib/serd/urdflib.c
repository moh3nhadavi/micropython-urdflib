#include "py/obj.h"
#include "py/runtime.h"
#include "py/urdflib/sord/sord.h"

STATIC mp_obj_t urdflib_info(void) {
    return mp_obj_new_str("urdflib v0.0.1", 14);
    // return MP_OBJ_NEW_SMALL_INT();
}
MP_DEFINE_CONST_FUN_OBJ_0(urdflib_info_obj, urdflib_info);


STATIC const mp_rom_map_elem_t mp_module_urdflib_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_urdflib) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&urdflib_info_obj) },
};
STATIC MP_DEFINE_CONST_DICT(mp_module_urdflib_globals, mp_module_urdflib_globals_table);

const mp_obj_module_t mp_module_urdflib = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mp_module_urdflib_globals,
};
MP_REGISTER_MODULE(MP_QSTR_urdflib, mp_module_urdflib);