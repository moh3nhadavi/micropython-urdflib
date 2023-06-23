typedef struct 
{
    SordModel *model;
    SordNode *context;
} Graph;

typedef struct{
    SordModel *model;
} Dataset;

typedef struct {
    SordNode ** nodes1;
    SordNode ** nodes2;
} SordNode2D;

extern Graph *middleware_graph_graph_new(SordNode *graph);
extern Dataset *middleware_graph_dataset_new();

extern size_t middleware_graph_num_quads(Graph *g);
extern void middleware_graph_close(Graph *g);
extern bool middleware_graph_add(Graph *g, SordNode *subject, SordNode *predicate, SordNode *object);
extern void middleware_graph_remove(Graph *g, SordNode *subject, SordNode *predicate, SordNode *object);
extern SordNode ** middleware_graph_get_nodes_of_quads(Graph *g, int *arraySize, int index);
extern SordNode2D middleware_graph_get_2D_nodes_of_quads(Graph* g, int* nodes1Size, int* nodes2Size, int index1, int index2);