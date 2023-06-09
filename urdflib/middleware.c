#include <stdlib.h>
#include "../lib/sord/sord.h"
#include "middleware.h"

Model *model_new()
{
    Model *model = (Model *)malloc(sizeof(Model));
    model->world = sord_world_new();
    model->model = sord_new(model->world, SORD_SPO, false);
    model->env = serd_env_new(NULL);
    return model;
}

Graph *graph_new(Model *model, const char *base_uri)
{
    if(model == NULL){
        Model *model = (Model *)malloc(sizeof(Model));
        model->world = sord_world_new();
        model->model = sord_new(model->world, SORD_SPO, false);
        model->env = serd_env_new(NULL);
    }
    if (base_uri) {
        SerdNode uri = serd_node_new_uri_from_string((const uint8_t *)base_uri, NULL,NULL );
        serd_env_set_base_uri(model->env, &uri);
    }else{
        base_uri = "http://example.org/";
    }
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->node = sord_new_uri(model->world, (const uint8_t *)base_uri);
    g->model = model;
    return g;
}