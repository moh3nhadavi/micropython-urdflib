#include "../terms.h"

typedef struct {
    SordNode *node;
} URIRef;

typedef struct {
    SordNode *node;
} Literal;

typedef struct {
    SordNode *node;
} BNode;

BNode *middleware_terms_bnode_new(const char *str);