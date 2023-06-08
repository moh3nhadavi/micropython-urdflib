#include <stdlib.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "py/objstr.h"

#include "../lib/sord/sord.h"

#include "graph.h"

typedef struct {
    SordWorld *world;
    SordModel *model;
    SerdEnv *env;
} Graph;

Graph *graph_new(const char *base_uri)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->world = sord_world_new();
    g->model = sord_new(g->world, SORD_SPO, false);
    g->env = serd_env_new(NULL);
    if (base_uri) {
        //  SerdURI *base_uri = {0};
        // SerdURI uri = serd_uri_from_string(base_uri, NULL);
        SerdNode uri = serd_node_new_uri_from_string((const uint8_t *)base_uri, NULL,NULL );
        serd_env_set_base_uri(g->env, &uri);
    }
    return g;
}

void graph_free(Graph *g)
{
    serd_env_free(g->env);
    sord_free(g->model);
    sord_world_free(g->world);
    free(g);
}

void graph_add_triple(Graph *g, const char *subject, const char *predicate, const char *object)
{
    SordNode *s = sord_new_uri(g->world, (const uint8_t *)subject);
    SordNode *p = sord_new_uri(g->world, (const uint8_t *)predicate);
    SordNode *o = sord_new_uri(g->world, (const uint8_t *)object);
    sord_add(g->model, (SordQuad){s, p, o, NULL});
}

void graph_add_literal(Graph *g, const char *subject, const char *predicate, const char *object, const char *lang, const char *datatype)
{
    SordNode *s = sord_new_uri(g->world, (const uint8_t *)subject);
    SordNode *p = sord_new_uri(g->world, (const uint8_t *)predicate);

    SordNode *datatype2 = sord_new_uri(g->world, (const uint8_t *)"http://www.w3.org/2001/XMLSchema#string");
    // (SordWorld *world, SordNode *datatype, const uint8_t *str, const char *lang)
    // SerdNode *o = serd_node_new_literal((const uint8_t *)object, lang ? (const uint8_t *)lang : NULL, datatype ? (const uint8_t *)datatype : NULL);
    SordNode *o = sord_new_literal(g->world, datatype2, (const uint8_t *) object, lang);
    // sord_add(g->model, (SordQuad){s, p, (SordNode *)o, NULL});
    sord_add(g->model, (SordQuad){s, p, o, NULL});
}

// void graph_add_prefix(Graph *g, const char *name, const char *uri)
// {
//     serd_env_set_prefix(g->env, (const uint8_t *)name, (const uint8_t *)uri);
// }

// void graph_add_base(Graph *g, const char *uri)
// {
//     // SerdURI *base_uri = {0};
//     // SerdURI uri = serd_uri_from_string(uri, NULL);
//     SerdNode uri = serd_node_new_uri_from_string((const uint8_t *)uri, NULL,NULL );
//     serd_env_set_base_uri(g->env, &uri);
// }

// void graph_load(Graph *g, const char *filename, SerdSyntax syntax)
// {
//     SerdURI *base_uri = {0};
//     serd_env_get_base_uri(g->env, base_uri);
//     SerdReader *reader = serd_reader_new(
//         syntax,
//         g->env,
//         base_uri,
//         NULL,
//         NULL);
//     FILE *input_file = fopen(filename, "r");
//     if (!input_file) {
//         fprintf(stderr, "Failed to open input file '%s'\n", filename);
//         return;
//     }
//     serd_reader_set_file_handle(reader, input_file, false);
//     sord_read(g->model, reader, NULL, NULL);
//     serd_reader_free(reader);
//     fclose(input_file);
// }

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


STATIC mp_obj_t urdflib_info(void) {
    Graph *g = graph_new("http://example.org/");
    graph_add_literal(g, "http://example.org/bob", "http://xmlns.com/foaf/0.1/name", "Bob", "en", NULL);
    graph_add_literal(g, "http://example.org/bob", "http://xmlns.com/foaf/0.1/age", "42", NULL, NULL);
    // graph_serialize(g, "urdf.ttl", SERD_TURTLE);
    return mp_obj_new_str("urdflib v0.0.1", 14);
}
MP_DEFINE_CONST_FUN_OBJ_0(urdflib_info_obj, urdflib_info);



STATIC const mp_rom_map_elem_t mp_module_urdflib_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_urdflib) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&urdflib_info_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_Graph), (mp_obj_t)&urdflib_graph_type },
};
STATIC MP_DEFINE_CONST_DICT(mp_module_urdflib_globals, mp_module_urdflib_globals_table);

const mp_obj_module_t mp_module_urdflib = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mp_module_urdflib_globals,
};
MP_REGISTER_MODULE(MP_QSTR_urdflib, mp_module_urdflib);