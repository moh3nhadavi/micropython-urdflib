#include <stdlib.h>
#include "../../lib/sord/sord.h"
#include "../globals.h"
#include "graph.h"
#include "terms.h"

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

void middleware_graph_remove(Graph *g, SordNode *subject, SordNode *predicate, SordNode *object)
{
    sord_remove(g->model, (SordQuad){subject, predicate, object, g->context});
}

SordNode ** middleware_graph_subjects(Graph *g, int *arraySize)
{
    int capacity = 1;  // Initial capacity of the array
    int count = 0;     // Number of elements currently in the array

    SordNode** nodes = malloc(capacity * sizeof(SordNode*));

    SordIter *iter = sord_begin(g->model);
    for (; !sord_iter_end(iter); sord_iter_next(iter))
    {
        SordQuad quad = {NULL, NULL, NULL, NULL};
        sord_iter_get(iter, quad);
        if (sord_node_equals(quad[3], g->context))
        {
            if (count >= capacity) {
                capacity += 1;
                nodes = realloc(nodes, capacity * sizeof(SordNode*));
            }
            nodes[count] = sord_node_copy(quad[0]);
            count++;
            // printf("%s\n", sord_node_get_string(quad[0]));
        }
    }
    sord_iter_free(iter);

    *arraySize = count;  // Update the size variable with the actual number of elements
    return nodes;
}

