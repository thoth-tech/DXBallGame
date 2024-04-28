#pragma once

#include "splashkit.h"
#include "game_types.h"
#include "game_data.h"
#include <json.h>
#include <string>

int high_score_position();
void update_scores();
block_data create_block(double x, double y, block_kind kind, powerups powerup);
ball_data create_ball(double x, double y, bool up, bool right);
