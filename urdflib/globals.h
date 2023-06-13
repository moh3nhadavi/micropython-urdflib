#ifndef GLOBALS_H
#define GLOBALS_H

#include "../lib/sord/sord.h"

struct World;
typedef struct {
    SordWorld *world;
    SerdEnv *env;
} World;

World *world;

extern void urdflib_globals_init0();

#endif