typedef struct 
{
    SordModel *model;
    SordNode *context;
} Graph;

typedef struct{
    SordModel *model;
} Dataset;

extern Graph *middleware_graph_graph_new(SordNode *graph);
extern Dataset *middleware_graph_dataset_new();