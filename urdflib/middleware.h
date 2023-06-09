#include "../lib/sord/sord.h"

typedef struct {
    SordWorld *world;
    SordModel *model;
    SerdEnv *env;
} Model;

typedef struct {
    SordNode *node;
    Model *model;
} Graph;

Model *model_new();
Graph *graph_new(Model *model, const char *base_uri);


