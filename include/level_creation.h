#pragma once

#include "types.h"

/**
 * @brief Spawns blocks for level 1.
 * @return A unique pointer to an array of BlockData representing the blocks for level 1.
 */
std::unique_ptr<BlockData[]> spawn_blocks_level_1();

/**
 * @brief Spawns blocks for level 2.
 * @return A unique pointer to an array of BlockData representing the blocks for level 2.
 */
std::unique_ptr<BlockData[]> spawn_blocks_level_2();

/**
 * @brief Spawns blocks for level 3.
 * @return A unique pointer to an array of BlockData representing the blocks for level 3.
 */
std::unique_ptr<BlockData[]> spawn_blocks_level_3();

/**
 * @brief Spawns blocks for level 4.
 * @return A unique pointer to an array of BlockData representing the blocks for level 4.
 */
std::unique_ptr<BlockData[]> spawn_blocks_level_4();
