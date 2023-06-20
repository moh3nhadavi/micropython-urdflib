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
URIRef *middleware_terms_uriref_new(const char *str, const char *base);
Literal *middleware_terms_literal_new(const char *str, SordNode *datatype, const char *lang);
