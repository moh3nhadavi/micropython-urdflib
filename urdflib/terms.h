#include "py/obj.h"
#include "middleware/terms.h"

typedef struct _bnode_obj_t
{
    mp_obj_base_t base;
    BNode *bnode;
} bnode_obj_t;

const mp_obj_type_t urdflib_bnode_type;

typedef struct _uriref_obj_t
{
    mp_obj_base_t base;
    URIRef *uri_ref;
} uriref_obj_t;

const mp_obj_type_t urdflib_uriref_type;

typedef struct _literal_obj_t
{
    mp_obj_base_t base;
    Literal *literal;
} literal_obj_t;

const mp_obj_type_t urdflib_literal_type;


extern const mp_obj_type_t urdflib_bnode_type;
extern const mp_obj_type_t urdflib_uriref_type;
extern const mp_obj_type_t urdflib_literal_type;

char *_generateRandomString(int length);