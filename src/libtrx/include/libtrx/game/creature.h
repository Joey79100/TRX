#pragma once

#include "collision.h"
#include "items.h"
#include "math.h"
#include "pathing.h"

#include <stdint.h>

#define UNIT_SHADOW 256

typedef struct {
    int16_t zone_num;
#if TR_VERSION == 1
    int16_t enemy_zone;
#else
    int16_t enemy_zone_num;
#endif
    int32_t distance;
    int32_t ahead;
    int32_t bite;
    int16_t angle;
    int16_t enemy_facing;
} AI_INFO;

typedef struct {
#if TR_VERSION == 1
    int32_t x;
    int32_t y;
    int32_t z;
#else
    XYZ_32 pos;
#endif
    int32_t mesh_num;
} BITE;

typedef enum {
    MOOD_BORED = 0,
    MOOD_ATTACK = 1,
    MOOD_ESCAPE = 2,
    MOOD_STALK = 3,
} MOOD_TYPE;

typedef struct {
    int16_t head_rotation;
    int16_t neck_rotation;
    int16_t maximum_turn;
    int16_t flags;
    int16_t item_num;
    MOOD_TYPE mood;
    LOT_INFO lot;
    XYZ_32 target;
#if TR_VERSION == 2
    ITEM *enemy;
#endif
} CREATURE;

#define CREATURE_STALK_DIST (3 * WALL_L) // = 3072
#define CREATURE_ESCAPE_DIST (5 * WALL_L) // = 5120
#define CREATURE_TARGET_DIST (4 * WALL_L) // = 4096

bool Creature_IsHostile(const ITEM *item);
extern void Creature_Initialise(int16_t item_num);
extern void Creature_Collision(
    int16_t item_num, ITEM *lara_item, COLL_INFO *coll);
extern bool Creature_Animate(int16_t item_num, int16_t angle, int16_t tilt);
extern void Creature_AIInfo(ITEM *item, AI_INFO *info);
extern void Creature_Mood(const ITEM *item, const AI_INFO *info, bool violent);
extern void Creature_Tilt(ITEM *item, int16_t angle);
extern void Creature_Head(ITEM *item, int16_t required);
extern int16_t Creature_Turn(ITEM *item, int16_t max_turn);
extern int16_t Creature_Effect(
    const ITEM *item, const BITE *bite,
    int16_t (*spawn)(
        int32_t x, int32_t y, int32_t z, int16_t speed, int16_t y_rot,
        int16_t room_num));
