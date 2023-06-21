#include <stdlib.h>
#include "../../lib/sord/sord.h"
#include "../globals.h"
#include "terms.h"

BNode *middleware_terms_bnode_new(const char *str)
{
    BNode *bnode = (BNode *)malloc(sizeof(BNode));
    bnode->node = sord_new_blank(world->world, (const uint8_t *)str);
    return bnode;
}

URIRef *middleware_terms_uriref_new(const char *str, const char *base_uri)
{
    URIRef *uri_ref = (URIRef *)malloc(sizeof(URIRef));
    if (base_uri != NULL)
    {
        uri_ref->node = sord_new_relative_uri(world->world, (const uint8_t *)str, (const uint8_t *)base_uri);
    }
    else
    {
        uri_ref->node = sord_new_uri(world->world, (const uint8_t *)str);
    }
    return uri_ref;
}

Literal *middleware_terms_literal_new(const char *str, SordNode *datatype, const char *lang)
{
    Literal *literal = (Literal *)malloc(sizeof(Literal));
    literal->node = sord_new_literal(world->world, datatype, (const uint8_t *)str, lang);
    return literal;
}

URIRef *middleware_terms_literal_datatype(Literal *literal)
{
    URIRef *uri_ref = (URIRef *)malloc(sizeof(URIRef));
    uri_ref->node = sord_node_get_datatype(literal->node);
    return uri_ref;
}

bool middleware_terms_literal_has_language(Literal *literal)
{
    return (sord_node_get_language(literal->node) != NULL) ? true : false;
}

char *middleware_terms_literal_language(Literal *literal)
{
    return (char *)sord_node_get_language(literal->node);
}

char *middleware_terms_literal_value(Literal *literal)
{
    return (char *)sord_node_get_string(literal->node);
}
