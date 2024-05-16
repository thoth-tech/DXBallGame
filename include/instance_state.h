#pragma once

#include "types.h"

/**
 * @brief Breaks a block and updates the score and remaining blocks.
 * @param blocks The array of blocks.
 * @param block_index The index of the block to break.
 * @param score The player's score.
 * @param remaining_blocks The number of remaining blocks.
 * @param multiplier The score multiplier.
 */
void break_block(BlockData blocks[], int block_index, int& score, int& remaining_blocks, int multiplier);

/**
 * @brief Checks for ball collisions with blocks, walls, and the paddle.
 * @param ball_index The index of the ball to check.
 */
void check_ball_collision(int ball_index);

/**
 * @brief Updates the location of a ball.
 * @param ball_index The index of the ball to update.
 */
void update_ball_location(int ball_index);

/**
 * @brief Updates the location and state of power-up drops.
 * @param power_up_index The index of the power-up drop to update.
 */
void update_power_up_drops(int power_up_index);
