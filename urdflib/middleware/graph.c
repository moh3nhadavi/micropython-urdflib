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

SordNode **middleware_graph_get_nodes_of_quads(Graph *g, int *arraySize, int index)
{
    if (index < 0 || index > 2)
    {
        return NULL;
    }

    int capacity = 1; // Initial capacity of the array
    int count = 0;    // Number of elements currently in the array

    SordNode **nodes = malloc(capacity * sizeof(SordNode *));

    SordIter *iter = sord_begin(g->model);
    for (; !sord_iter_end(iter); sord_iter_next(iter))
    {
        SordQuad quad = {NULL, NULL, NULL, NULL};
        sord_iter_get(iter, quad);
        if (sord_node_equals(quad[3], g->context))
        {
            if (count >= capacity)
            {
                capacity += 1;
                nodes = realloc(nodes, capacity * sizeof(SordNode *));
            }
            nodes[count] = sord_node_copy(quad[index]);
            count++;
        }
    }
    sord_iter_free(iter);

    *arraySize = count; // Update the size variable with the actual number of elements
    return nodes;
}

SordNode2D middleware_graph_get_2D_nodes_of_quads(Graph *g, int *nodes1Size, int *nodes2Size, int index1, int index2)
{
    if ((index1 < 0 || index1 > 2 || index2 < 0 || index2 > 2) || (index1 == index2))
    {
        SordNode2D result = {NULL, NULL};
        return result;
    }

    int nodes1Capacity = 1; // Initial capacity of the subjects array
    int nodes1Count = 0;    // Number of subject elements currently in the array

    int nodes2Capacity = 1; // Initial capacity of the predicates array
    int nodes2Count = 0;    // Number of predicate elements currently in the array

    SordNode **nodes1 = malloc(nodes1Capacity * sizeof(SordNode *));
    SordNode **predicates = malloc(nodes2Capacity * sizeof(SordNode *));

    SordIter *iter = sord_begin(g->model);
    for (; !sord_iter_end(iter); sord_iter_next(iter))
    {
        SordQuad quad = {NULL, NULL, NULL, NULL};
        sord_iter_get(iter, quad);
        if (sord_node_equals(quad[3], g->context))
        {
            if (nodes1Count >= nodes1Capacity)
            {
                nodes1Capacity += 1;
                nodes1 = realloc(nodes1, nodes1Capacity * sizeof(SordNode *));
            }
            if (nodes2Count >= nodes2Capacity)
            {
                nodes2Capacity += 1;
                predicates = realloc(predicates, nodes2Capacity * sizeof(SordNode *));
            }

            nodes1[nodes1Count] = sord_node_copy(quad[index1]);
            predicates[nodes2Count] = sord_node_copy(quad[index2]);

            nodes1Count++;
            nodes2Count++;
        }
    }
    sord_iter_free(iter);

    *nodes1Size = nodes1Count;     // Update the size variable with the actual number of subject elements
    *nodes2Size = nodes2Count; // Update the size variable with the actual number of predicate elements

    SordNode2D result = {nodes1, predicates};
    return result;
}
