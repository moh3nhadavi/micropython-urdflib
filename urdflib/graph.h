#include "py/obj.h"
#include "middleware/graph.h"

typedef struct _graph_obj_t
{
    mp_obj_base_t base;
    Graph *graph;
} graph_obj_t;

const mp_obj_type_t urdflib_graph_type;

typedef struct _dataset_obj_t
{
    mp_obj_base_t base;
    Dataset *dataset;
} dataset_obj_t;

const mp_obj_type_t urdflib_dataset_type;

extern const mp_obj_type_t urdflib_graph_type;