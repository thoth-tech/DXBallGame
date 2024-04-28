#pragma once

#include "game_types.h"
#include "game_data.h"
#include "level_data.h"
#include "resources.h"
#include "rendering.h"
#include <splashkit.h>

void reset_game();
void start_level();
void end_game(bool successful);
void break_block(block_data blocks[], int block_index, int &score, int &remaining_blocks, int multiplier);
void check_ball_collision(int i);
void update_ball_location(int i);
void update_powerup_drops(int i);
