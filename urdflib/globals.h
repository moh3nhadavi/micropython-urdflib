#ifndef GLOBALS_H
#define GLOBALS_H

#include "lib/urdflib-ext/sord/sord.h"

struct World;
typedef struct {
    SordWorld *world;
    SerdEnv *env;
} World;

extern World *world;

extern void urdflib_globals_init0();

#endif