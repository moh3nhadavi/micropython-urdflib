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

size_t middleware_graph_num_quads(Graph *g)
{
    return sord_num_quads(g->model);
}

void middleware_graph_close(Graph *g)
{
    sord_free(g->model);
    free(g);
}

bool middleware_graph_add(Graph *g, SordNode *subject, SordNode *predicate, SordNode *object)
{
    return sord_add(g->model, (SordQuad){subject, predicate, object, g->context});
}

