#include <stdlib.h>
#include "../lib/sord/sord.h"
#include "globals.h"

World *world = NULL;
void urdflib_globals_init0() {
    if (world != NULL) {
        return;
    }
    world = (World *)malloc(sizeof(World));
    world->world = sord_world_new();
}