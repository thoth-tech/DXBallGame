#pragma once

#include "types.h"

/**
 * @brief Creates a block with the specified properties.
 * @param x The x-coordinate of the block.
 * @param y The y-coordinate of the block.
 * @param kind The kind of the block (single hit, double hit, hidden).
 * @param power_up The power-up associated with the block.
 * @return The created block.
 */
BlockData create_block(double x, double y, BlockKind kind, PowerUpKind power_up);

/**
 * @brief Creates a ball with the specified properties.
 * @param x The x-coordinate of the ball.
 * @param y The y-coordinate of the ball.
 * @param up Indicates if the ball is moving upwards.
 * @param right Indicates if the ball is moving to the right.
 * @return The created ball.
 */
BallData create_ball(double x, double y, bool up, bool right);
