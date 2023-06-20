#include <stdlib.h>
#include "../../lib/sord/sord.h"
#include "../globals.h"
#include "graph.h"

SordModel *_middleware_new_model()
{
    return (SordModel *)sord_new(world->world, SORD_SPO, true);
}

Graph *middleware_graph_graph_new(SordNode *graph)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->context = graph;
    g->model = _middleware_new_model();
    return g;
}

Dataset *middleware_graph_dataset_new()
{
    Dataset *d = (Dataset *)malloc(sizeof(Dataset));
    d->model = _middleware_new_model();
    return d;
}

