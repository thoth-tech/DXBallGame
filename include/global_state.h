#pragma once

/**
 * @brief Resets the game to its initial state.
 */
void reset_game();

/**
 * @brief Starts a new level.
 */
void start_level();

/**
 * @brief Ends the game.
 * @param successful Indicates if the game ended successfully (player won).
 */
void end_game(bool successful);
