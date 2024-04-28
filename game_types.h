#pragma once

#include <string>
#include "splashkit.h"

const int BLOCKS_IN_LEVEL1 = 32;
const int BLOCKS_IN_LEVEL2 = 35;
const int BLOCKS_IN_LEVEL3 = 44;
const int BLOCKS_IN_LEVEL4 = 120;

const double BLOCK_WIDTH = 60;
const double BLOCK_HEIGHT = 20;
const double BALL_RADIUS = 8;
const double BALL_SPEED = 4;
const double PADDLE_SPEED = 8;
const double PADDLE_Y = 550;
const double PADDLE_HEIGHT = 5;
const double PADDLE_LENGTH = 100;
const double MULTIPLIER_DURATION = 10;
const double NEW_BALL_DELAY = 5;
const double TIME_ON_SCOREBOARD = 120;
const double TIME_ON_TITLE = 600;

const key_code UP = UP_KEY;
const key_code DOWN = DOWN_KEY;
const key_code LEFT = LEFT_KEY;
const key_code RIGHT = RIGHT_KEY;
const key_code START = SPACE_KEY;
const key_code P1_B1 = Z_KEY;
const key_code P1_B2 = X_KEY;

enum block_kind {
    SINGLE_HIT,
    DOUBLE_HIT,
    HIDDEN // Bricks hidden from the player before being hit, then take one more hit to be destroyed
};

enum powerups {
    NO_POWERUP,
    MULTI_BALL,
    SCORE_MULTIPLY
};

struct block_data {
    double x;
    double y;
    block_kind kind;
    powerups powerup;
    int hitpoint;
    std::string block_bitmap;
    std::string powerup_bitmap;
};

struct ball_data {
    double x;
    double y;
    bool up;
    bool right;
};

struct powerup_drop_data {
    double x;
    double y;
    powerups kind;
};
