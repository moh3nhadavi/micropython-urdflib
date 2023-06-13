#include "../lib/sord/sord.h"

typedef struct {
    SordModel *model;
} Model;

typedef struct {
    SordNode *node;
    Model *model;
} Graph;

Model *model_new();
Graph *graph_new(Model *model, const char *base_uri);
void middleware_graph_close(Graph *g);
size_t middleware_num_quads(Model *model);
bool middleware_graph_add_triple(Graph *g, const char *subject, const char *predicate, const char *object);
void middleware_graph_remove_triple(Graph *g, const char *subject, const char *predicate, const char *object);
void middleware_graph_get_subjects(Graph *g);



