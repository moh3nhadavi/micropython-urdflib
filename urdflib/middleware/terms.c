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

Literal *middleware_terms_literal_new(const char *str, URIRef *datatype, const char *lang)
{
    mp_print_str(&mp_plat_print, "middleware\n");
    Literal *literal = (Literal *)malloc(sizeof(Literal));
    mp_print_str(&mp_plat_print, "--middleware--\n");
    literal->node = sord_new_literal(world->world,datatype->node, (const uint8_t *)str, lang);
    // if (lang != NULL)
    // {
    //     literal->node = sord_new_literal(world->world, (const uint8_t *)str, (const uint8_t *)lang, NULL);
    // }
    // else if (datatype != NULL)
    // {
    //     literal->node = sord_new_literal(world->world, (const uint8_t *)str, NULL, (const uint8_t *)datatype);
    // }
    // else
    // {
    //     literal->node = sord_new_literal(world->world, (const uint8_t *)str, NULL, NULL);
    // }
    return literal;
}
