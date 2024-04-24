#include "include/level_creation.h"
#include "include/instance_creation.h"
#include "include/types.h"
#include "include/global_constants.h"
#include "include/global_instances.h"

std::unique_ptr<BlockData[]> spawn_blocks_level_1() {
    game_data.remaining_blocks = BLOCKS_IN_LEVEL_1;
    auto blocks = std::make_unique<BlockData[]>(BLOCKS_IN_LEVEL_1);
    int index = 0;

    // Spawn blocks for level 1
    for (int i = 0; i < 8; i++) {
        blocks[index++] = create_block(160 + i * BLOCK_WIDTH, 240, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
    }
    for (int i = 0; i < 6; i++) {
        blocks[index++] = create_block(220 + i * BLOCK_WIDTH, 260, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
        blocks[index++] = create_block(220 + i * BLOCK_WIDTH, 220, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
    }
    for (int i = 0; i < 4; i++) {
        blocks[index++] = create_block(280 + i * BLOCK_WIDTH, 280, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
        blocks[index++] = create_block(280 + i * BLOCK_WIDTH, 200, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
    }
    for (int i = 0; i < 2; i++) {
        blocks[index++] = create_block(340 + i * BLOCK_WIDTH, 300, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
        blocks[index++] = create_block(340 + i * BLOCK_WIDTH, 180, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
    }

    // Randomly assign multi-ball power-ups to blocks
    for (int i = 0; i < 12; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_1;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::MULTI_BALL;
        blocks[random_index].power_up_bitmap = "block_multi_ball";
    }

    // Randomly assign score multiplier power-ups to blocks
    for (int i = 0; i < 5; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_1;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::SCORE_MULTIPLY;
        blocks[random_index].power_up_bitmap = "block_multiplier_2";
    }

    return blocks;
}

std::unique_ptr<BlockData[]> spawn_blocks_level_2() {
    game_data.remaining_blocks = BLOCKS_IN_LEVEL_2;
    auto blocks = std::make_unique<BlockData[]>(BLOCKS_IN_LEVEL_2);
    int index = 0;

    // Spawn blocks for level 2
    for (int i = 0; i < 7; i++) {
        blocks[index++] = create_block(40 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
        blocks[index++] = create_block(100 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, BlockKind::DOUBLE_HIT, PowerUpKind::NO_POWERUP);
        blocks[index++] = create_block(280 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
        blocks[index++] = create_block(340 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, BlockKind::DOUBLE_HIT, PowerUpKind::NO_POWERUP);
    }
    for (int i = 0; i < 3; i++) {
        blocks[index++] = create_block(520 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
        blocks[index++] = create_block(580 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, BlockKind::DOUBLE_HIT, PowerUpKind::NO_POWERUP);
    }
    blocks[index++] = create_block(700, 240, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);

    // Randomly assign multi-ball power-ups to blocks
    for (int i = 0; i < 18; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_2;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::MULTI_BALL;
        blocks[random_index].power_up_bitmap = "block_multi_ball";
    }

    // Randomly assign score multiplier power-ups to blocks
    for (int i = 0; i < 8; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_2;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::SCORE_MULTIPLY;
        blocks[random_index].power_up_bitmap = "block_multiplier_2";
    }

    return blocks;
}

std::unique_ptr<BlockData[]> spawn_blocks_level_3() {
    game_data.remaining_blocks = BLOCKS_IN_LEVEL_3;
    auto blocks = std::make_unique<BlockData[]>(BLOCKS_IN_LEVEL_3);
    int index = 0;

    // Spawn blocks for level 3
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            blocks[index++] = create_block(160 + j * BLOCK_WIDTH, 260 - i * BLOCK_HEIGHT, BlockKind::SINGLE_HIT, PowerUpKind::NO_POWERUP);
        }
    }
    for (int i = 0; i < 12; i++) {
        blocks[index++] = create_block(40 + i * BLOCK_WIDTH, 320, BlockKind::HIDDEN, PowerUpKind::NO_POWERUP);
    }

    // Randomly assign multi-ball power-ups to blocks
    for (int i = 0; i < 20; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_3;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::MULTI_BALL;
        blocks[random_index].power_up_bitmap = "block_multi_ball";
    }

    // Randomly assign score multiplier power-ups to blocks
    for (int i = 0; i < 9; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_3;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::SCORE_MULTIPLY;
        blocks[random_index].power_up_bitmap = "block_multiplier_2";
    }

    return blocks;
}

std::unique_ptr<BlockData[]> spawn_blocks_level_4() {
    game_data.remaining_blocks = BLOCKS_IN_LEVEL_4;
    auto blocks = std::make_unique<BlockData[]>(BLOCKS_IN_LEVEL_4);
    int index = 0;

    // Spawn blocks for level 4
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            blocks[index++] = create_block(40 + j * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, static_cast<BlockKind>(rand() % 3), PowerUpKind::NO_POWERUP);
        }
    }

    // Randomly assign multi-ball power-ups to blocks
    for (int i = 0; i < 50; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_4;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::MULTI_BALL;
        blocks[random_index].power_up_bitmap = "block_multi_ball";
    }

    // Randomly assign score multiplier power-ups to blocks
    for (int i = 0; i < 30; i++) {
        int random_index;
        do {
            random_index = rand() % BLOCKS_IN_LEVEL_4;
        } while (blocks[random_index].power_up_kind != PowerUpKind::NO_POWERUP);
        blocks[random_index].power_up_kind = PowerUpKind::SCORE_MULTIPLY;
        blocks[random_index].power_up_bitmap = "block_multiplier_2";
    }

    return blocks;
}
