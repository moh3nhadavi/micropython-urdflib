#include <stdlib.h>
#include "../../lib/sord/sord.h"
#include "../globals.h"
#include "terms.h"
// #include "../terms.h"

BNode *middleware_terms_bnode_new(const char *str)
{
    BNode *bnode = (BNode *)malloc(sizeof(BNode));
    bnode->node = sord_new_blank(world->world, (const uint8_t *)str);
    return bnode;
}
