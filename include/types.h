#pragma once

#include <string>
#include <array>
#include <memory>
#include <vector>
#include <json.h>
#include "splashkit/splashkit.h"
#include "global_constants.h"

enum class BlockKind {
    SINGLE_HIT,
    DOUBLE_HIT,
    HIDDEN // Bricks hidden from the player before being hit, then take one more hit to be destroyed
};

enum class PowerUpKind {
    NO_POWERUP,
    MULTI_BALL,
    SCORE_MULTIPLY
};

/**
 * @brief Represents a block in the game.
 */
struct BlockData {
    double x;                   ///< The x-coordinate of the block.
    double y;                   ///< The y-coordinate of the block.
    BlockKind kind;             ///< The kind of the block (single hit, double hit, hidden).
    PowerUpKind power_up_kind;  ///< The power-up associated with the block.
    int hit_points;             ///< The number of hits required to destroy the block.
    std::string block_bitmap;   ///< The bitmap used to render the block.
    std::string power_up_bitmap;///< The bitmap used to render the power-up.
};

/**
 * @brief Represents a ball in the game.
 */
struct BallData {
    double x;       ///< The x-coordinate of the ball.
    double y;       ///< The y-coordinate of the ball.
    bool up;        ///< Indicates if the ball is moving upwards.
    bool right;     ///< Indicates if the ball is moving to the right.
};

/**
 * @brief Represents a power-up drop in the game.
 */
struct PowerUpDropData {
    double x;           ///< The x-coordinate of the power-up drop.
    double y;           ///< The y-coordinate of the power-up drop.
    PowerUpKind kind;   ///< The kind of the power-up.
};

/**
 * @brief Represents the game data.
 */
struct GameData {
    std::unique_ptr<BlockData[]> blocks;              ///< The blocks in the current level.
    std::vector<PowerUpDropData> current_power_ups;   ///< The current power-up drops.
    std::vector<BallData> current_balls;              ///< The current balls in play.
    int remaining_blocks;                             ///< The number of remaining blocks in the level.
    int blocks_in_level;                              ///< The total number of blocks in the level.
    int score = 0;                                    ///< The player's score.
    bool game_start = false;                          ///< Indicates if the game has started.
    bool game_over = false;                           ///< Indicates if the game is over.
    bool game_won = false;                            ///< Indicates if the player has won the game.
    int current_level = 1;                            ///< The current level.
    bool next_level = true;                           ///< Indicates if the player should proceed to the next level.
    double multiplier_timer = 0;                      ///< The timer for the score multiplier power-up.
    double extra_ball_timer = 0;                      ///< The timer for spawning extra balls.
    double exit_timer = TIME_ON_TITLE;                ///< The timer for exiting the game.
    int score_multiplier = 1;                         ///< The current score multiplier.
    double paddle_x;                                  ///< The x-coordinate of the paddle.
    bool ball_is_held;                                ///< Indicates if the ball is being held by the paddle.
    json scores;                                      ///< The high scores data.
    json score_rows[10];                              ///< The individual score rows.
    bool initials_entered = false;                    ///< Indicates if the player's initials have been entered.
};

/**
 * @brief Represents the high score initials entry data.
 */
struct InitialsEntryData {
    std::array<std::string, 27> characters;    ///< The available characters for initials.
    int character_1 = 0;                       ///< The index of the first character.
    int character_2 = 0;                       ///< The index of the second character.
    int* current_character = &character_1;     ///< A pointer to the current character being edited.
};
