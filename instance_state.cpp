#include "include/instance_state.h"
#include "include/instance_creation.h"
#include "include/types.h"
#include "include/global_constants.h"
#include "include/global_instances.h"

void break_block(BlockData blocks[], int block_index, int& score, int& remaining_blocks, int multiplier) {
    // Break a block and update score and remaining blocks
    blocks[block_index].hit_points--;
    score += multiplier;
    if (blocks[block_index].hit_points == 0) {
        remaining_blocks--;
        play_sound_effect("sfx_break_block");
        if (game_data.blocks[block_index].power_up_kind != PowerUpKind::NO_POWERUP) {
            // Create a power-up drop if the block had a power-up
            PowerUpDropData new_power_up;
            new_power_up.x = game_data.blocks[block_index].x;
            new_power_up.y = game_data.blocks[block_index].y;
            new_power_up.kind = game_data.blocks[block_index].power_up_kind;
            game_data.current_power_ups.push_back(new_power_up);
        }
    } else if (blocks[block_index].kind == BlockKind::DOUBLE_HIT) {
        play_sound_effect("sfx_bounce_ball", 0.25f);
        blocks[block_index].block_bitmap = "block_double_hit_2";
    } else if (blocks[block_index].kind == BlockKind::HIDDEN) {
        play_sound_effect("sfx_bounce_ball", 0.25f);
        blocks[block_index].block_bitmap = "block_hidden_2";
    }
}

void check_ball_collision(int ball_index) {
    // Check for ball collisions with walls, blocks, and paddle
    BallData& ball = game_data.current_balls[ball_index];

    // Check collision with walls
    if (ball.x - BALL_RADIUS <= 0) {
        play_sound_effect("sfx_bounce_ball", 0.25f);
        ball.right = true;
    }
    if (ball.x + BALL_RADIUS >= screen_width()) {
        play_sound_effect("sfx_bounce_ball", 0.25f);
        ball.right = false;
    }
    if (ball.y - BALL_RADIUS <= 0) {
        play_sound_effect("sfx_bounce_ball", 0.25f);
        ball.up = false;
    }

    // Check collision with bottom of the screen
    if (ball.y + BALL_RADIUS >= screen_height() && !game_data.game_over) {
        game_data.current_balls.erase(game_data.current_balls.begin() + ball_index);
        if (game_data.current_balls.empty()) {
            game_data.game_won = false;
            game_data.game_over = true;
            game_data.exit_timer = TIME_ON_SCOREBOARD;
            game_data.current_power_ups.clear();
        }
    }

    // Check collision with paddle
    if ((PADDLE_Y <= ball.y + BALL_RADIUS && ball.y + BALL_RADIUS <= PADDLE_Y + BALL_SPEED) &&
        (ball.x + BALL_RADIUS >= game_data.paddle_x && ball.x - BALL_RADIUS <= game_data.paddle_x + PADDLE_LENGTH)) {
        play_sound_effect("sfx_bounce_ball", 0.25f);
        ball.up = true;
    }

    // Check collision with blocks
    for (int j = 0; j < game_data.blocks_in_level; j++) {
        if (game_data.blocks[j].hit_points > 0) {
            if (ball.x > game_data.blocks[j].x && ball.x < game_data.blocks[j].x + BLOCK_WIDTH) {
                if (game_data.blocks[j].y + BLOCK_HEIGHT - BALL_SPEED <= ball.y - BALL_RADIUS && ball.y - BALL_RADIUS <= game_data.blocks[j].y + BLOCK_HEIGHT) {
                    ball.up = false;
                    break_block(game_data.blocks.get(), j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
                if (game_data.blocks[j].y <= ball.y + BALL_RADIUS && ball.y + BALL_RADIUS <= game_data.blocks[j].y + BALL_SPEED) {
                    ball.up = true;
                    break_block(game_data.blocks.get(), j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
            }
            if (ball.y + BALL_RADIUS > game_data.blocks[j].y && ball.y - BALL_RADIUS < game_data.blocks[j].y + BLOCK_HEIGHT) {
                if (game_data.blocks[j].x + BLOCK_WIDTH <= ball.x - BALL_RADIUS - BALL_SPEED && ball.x - BALL_RADIUS <= game_data.blocks[j].x + BLOCK_WIDTH) {
                    ball.right = true;
                    break_block(game_data.blocks.get(), j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
                if (game_data.blocks[j].x <= ball.x + BALL_RADIUS && ball.x + BALL_RADIUS <= game_data.blocks[j].x + BALL_SPEED) {
                    ball.right = false;
                    break_block(game_data.blocks.get(), j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
            }
        }
    }
}


void update_ball_location(int ball_index) {
    BallData& ball = game_data.current_balls[ball_index];
    // Update ball position based on direction and speed
    if (!game_data.ball_is_held) {
        if (ball.up) {
            ball.y -= BALL_SPEED;
        } else {
            ball.y += BALL_SPEED;
        }
        if (ball.right) {
            ball.x += BALL_SPEED;
        } else {
            ball.x -= BALL_SPEED;
        }
    } else {
        // Hold the ball on the paddle
        ball.x = game_data.paddle_x + PADDLE_LENGTH / 2 - BALL_RADIUS;
        ball.y = PADDLE_Y - 25;
    }

// Release the ball when P1_B1 is pressed
    if (game_data.ball_is_held && key_down(P1_B1)) {
        game_data.ball_is_held = false;
    }
}

void update_power_up_drops(int power_up_index) {
    PowerUpDropData &power_up = game_data.current_power_ups[power_up_index];
    // Update power-up drop position
    power_up.y += BALL_SPEED / 2;

    // Remove power-up drop if it goes off the screen
    if (power_up.y + BALL_RADIUS >= screen_height()) {
        game_data.current_power_ups.erase(game_data.current_power_ups.begin() + power_up_index);
    }

    // Check collision with paddle
    if ((PADDLE_Y <= power_up.y + BALL_RADIUS && power_up.y + BALL_RADIUS <= PADDLE_Y + (BALL_SPEED / 2)) &&
        (power_up.x + BALL_RADIUS >= game_data.paddle_x &&
         power_up.x - BALL_RADIUS <= game_data.paddle_x + PADDLE_LENGTH)) {
        bool direction = static_cast<bool>(rnd(0, 2));
        play_sound_effect("sfx_powerup", 0.5f);

        // Apply power-up effect based on the power-up kind
        if (power_up.kind == PowerUpKind::MULTI_BALL) {
            game_data.current_balls.push_back(create_ball(power_up.x, PADDLE_Y + 10, true, direction));
        } else if (power_up.kind == PowerUpKind::SCORE_MULTIPLY) {
            game_data.multiplier_timer = MULTIPLIER_DURATION;
            if (game_data.score_multiplier < 5) {
                game_data.score_multiplier++;
            }
        }

        // Remove power-up drop after applying the effect
        game_data.current_power_ups.erase(game_data.current_power_ups.begin() + power_up_index);
    }
}

