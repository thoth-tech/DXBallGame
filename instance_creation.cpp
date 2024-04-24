#include "include/instance_creation.h"
#include "include/types.h"

BlockData create_block(double x, double y, BlockKind kind, PowerUpKind power_up) {
    BlockData block;
    block.x = x;
    block.y = y;
    block.kind = kind;

    // Set the block properties based on the block kind
    switch (kind) {
        case BlockKind::SINGLE_HIT:
            block.hit_points = 1;
            block.block_bitmap = "block_single_hit";
            break;
        case BlockKind::DOUBLE_HIT:
            block.hit_points = 2;
            block.block_bitmap = "block_double_hit_1";
            break;
        case BlockKind::HIDDEN:
            block.hit_points = 2;
            block.block_bitmap = "block_hidden_1";
            break;
    }

    // Set the power-up bitmap based on the power-up kind
    switch (power_up) {
        case PowerUpKind::NO_POWERUP:
            block.power_up_bitmap = "block_hidden_1";
            break;
        case PowerUpKind::MULTI_BALL:
            block.power_up_bitmap = "block_multi_ball";
            break;
        case PowerUpKind::SCORE_MULTIPLY:
            block.power_up_bitmap = "block_multiplier_2";
            break;
        default:
            block.power_up_bitmap = "block_multi_ball";
            break;
    }

    block.power_up_kind = power_up;
    return block;
}

BallData create_ball(double x, double y, bool up, bool right) {
    BallData ball;
    ball.x = x;
    ball.y = y;
    ball.up = up;
    ball.right = right;
    return ball;
}
