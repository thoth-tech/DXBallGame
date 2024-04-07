#pragma once

#include "game_types.h"
#include <vector>
#include <json.h>

struct game_data_struct {
    block_data *blocks;
    std::vector<powerup_drop_data> current_powerups;
    std::vector<ball_data> current_balls;
    int remaining_blocks;
    int blocks_in_level;
    int score = 0;
    bool game_start = false;
    bool game_over = false;
    bool game_won = false;
    int current_level = 1;
    bool next_level = true;
    double multiplierTimer = 0;
    double extraBallTimer = 0;
    double exitTimer = TIME_ON_TITLE;
    int score_multiplier = 1;
    double paddle_x;
    bool ball_is_held;
    json scores;
    json score_rows[10];
    bool initials_entered = false;
};

extern game_data_struct game_data;

struct initials_entry_struct {
    std::string characters[27];
    int character1 = 0;
    int character2 = 0;
    int *current_character = &character1;
};

extern initials_entry_struct initials_entry;

