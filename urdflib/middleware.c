#include <stdlib.h>
#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#include "../lib/sord/sord.h"
#include "middleware.h"
#include "globals.h"



Model *model_new()
{
    Model *model = (Model *)malloc(sizeof(Model));
    model->model = sord_new(world->world, SORD_SPO, false);
    return model;
}

Graph *graph_new(Model *model, const char *base_uri)
{
    if (model == NULL)
    {
        Model *model = (Model *)malloc(sizeof(Model));
        model->model = sord_new(world->world, SORD_SPO, false);
        world->env = serd_env_new(NULL);
    }
    if (base_uri)
    {
        SerdNode uri = serd_node_new_uri_from_string((const uint8_t *)base_uri, NULL, NULL);
        serd_env_set_base_uri(world->env, &uri);
    }
    else
    {
        base_uri = "http://example.org/";
    }
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->node = sord_new_uri(world->world, (const uint8_t *)base_uri);
    g->model = model;
    return g;
}

void middleware_graph_close(Graph *g)
{
    sord_free(g->model->model);
    sord_world_free(world->world);
    serd_env_free(world->env);
    free(g->model);
    free(g);
}

size_t middleware_num_quads(Model *model)
{
    return sord_num_quads(model->model);
}

bool middleware_graph_add_triple(Graph *g, const char *subject, const char *predicate, const char *object)
{
    SordNode *s = sord_new_uri(world->world, (const uint8_t *)subject);
    SordNode *p = sord_new_uri(world->world, (const uint8_t *)predicate);
    SordNode *o = sord_new_uri(world->world, (const uint8_t *)object);
    return sord_add(g->model->model, (SordQuad){s, p, o, g->node});
}

void middleware_graph_remove_triple(Graph *g, const char *subject, const char *predicate, const char *object)
{
    SordNode *s = sord_new_uri(world->world, (const uint8_t *)subject);
    SordNode *p = sord_new_uri(world->world, (const uint8_t *)predicate);
    SordNode *o = sord_new_uri(world->world, (const uint8_t *)object);
    sord_remove(g->model->model, (SordQuad){s, p, o, g->node});
}

void middleware_graph_get_subjects(Graph *g)
{
    // int count = 0;
    SordIter *iter = sord_begin(g->model->model);
    // for (; !sord_iter_end(iter); sord_iter_next(iter))
    // {
    //     SordQuad quad = {NULL, NULL, NULL, NULL};
    //     sord_iter_get(iter, quad);
    //     if (sord_node_equals(quad[3], g->node))
    //     {
    //         count++;
    //     }
    // }
    // char *subjects[count];
    // SordNode *subjects = (SordNode *)malloc(count * sizeof(SordNode));
    // int i = 0;
    // iter = sord_begin(g->model->model);
    for (; !sord_iter_end(iter); sord_iter_next(iter))
    {
        SordQuad quad = {NULL, NULL, NULL, NULL};
        sord_iter_get(iter, quad);
        if (sord_node_equals(quad[3], g->node))
        {
            printf("%s\n", sord_node_get_string(quad[0]));
            // mp_print_str(&mp_plat_print, sord_node_get_string(quad[0]));
            // subjects[i] = sord_node_get_string(quad[0]);
            // i++;
        }
    }
    // length = count;
    sord_iter_free(iter);
    // return subjects;
}