#ifndef _ex19_h
#define _ex19_h
#include "object.h"
struct Monster{
    Object proto;
    int hit_points;
};
typedef struct Monster Monster ;
int Monster_attack(void *selef, int damage);
int Monster_init(void *selef);
struct Room{
    Object proto;
    Monster *bad_guy;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};
typedef struct Room Room ;
void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *selef);
struct Map{
    Object proto;
    Room *start;
    Room *location;
};
typedef struct Map Map ;
void *Map_move(void *self, Direction direction);
int Map_attack(void *selt, int damage);
int Map_init(void *self);
#endif