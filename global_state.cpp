#include "include/global_state.h"
#include "include/instance_creation.h"
#include "include/types.h"
#include "include/global_constants.h"
#include "include/global_instances.h"
#include "include/high_scores.h"
#include "include/level_creation.h"
#include "include/rendering.h"

void reset_game() {
    // Reset game state to initial values
    game_data.score = 0;
    game_data.game_over = false;
    game_data.game_won = false;
    game_data.current_level = 1;
    game_data.next_level = true;
    game_data.multiplier_timer = 0;
    game_data.score_multiplier = 1;
    game_data.extra_ball_timer = NEW_BALL_DELAY;
    game_data.initials_entered = false;
    initials_entry.character_1 = 0;
    initials_entry.character_2 = 0;
    initials_entry.current_character = &initials_entry.character_1;
    game_data.blocks = spawn_blocks_level_1();
    game_data.blocks_in_level = BLOCKS_IN_LEVEL_1;
    game_data.paddle_x = (screen_width() - PADDLE_LENGTH) / 2;
    game_data.current_balls.clear();
    game_data.current_balls.push_back(create_ball(50, 50, true, true));
    game_data.ball_is_held = true;
    clear_screen(COLOR_BLACK);
    draw_blocks();
    draw_bitmap("paddle", game_data.paddle_x, PADDLE_Y);
}

void start_level() {
    // Start a new level based on the current level number
    switch (game_data.current_level) {
        case 1:
            game_data.blocks = spawn_blocks_level_1();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL_1;
            break;
        case 2:
            game_data.blocks = spawn_blocks_level_2();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL_2;
            break;
        case 3:
            game_data.blocks = spawn_blocks_level_3();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL_3;
            break;
        case 4:
            game_data.blocks = spawn_blocks_level_4();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL_4;
            break;
        default:
            play_sound_effect("sfx_win");
            game_data.game_won = true;
            game_data.game_over = true;
            game_data.exit_timer = TIME_ON_SCOREBOARD;
            break;
    }
    game_data.score_multiplier = 1;
    game_data.multiplier_timer = 0;
    game_data.current_power_ups.clear();
    game_data.paddle_x = (screen_width() - PADDLE_LENGTH) / 2;
    game_data.next_level = false;
    game_data.current_balls.clear();
    game_data.current_balls.push_back(create_ball(50, 50, true, true));
    game_data.ball_is_held = true;
}

void end_game(bool successful) {
    // Display game over screen
    fill_rectangle(COLOR_LIGHT_GRAY, 200, 20, 400, 560);
    int position = calculate_high_score_position();

    if (!game_data.initials_entered && position != 10) {
        // Prompt for initials if high score achieved
        draw_text("Enter initials", COLOR_BLACK, font_named("default"), 30, 280, 100);
        draw_text(initials_entry.characters[initials_entry.character_1], COLOR_BLACK, font_named("default"), 50, 360, 180);
        draw_text(initials_entry.characters[initials_entry.character_2], COLOR_BLACK, font_named("default"), 50, 400, 180);
        if (initials_entry.current_character == &initials_entry.character_1) {
            fill_triangle(COLOR_BLACK, 374, 165, 364, 175, 384, 175);
            fill_triangle(COLOR_BLACK, 374, 240, 364, 230, 384, 230);
        } else {
            fill_triangle(COLOR_BLACK, 414, 165, 404, 175, 424, 175);
            fill_triangle(COLOR_BLACK, 414, 240, 404, 230, 424, 230);
        }
        draw_text("Press 1 to submit", COLOR_BLACK, font_named("default"), 30, 260, 280);

        // Handle initials entry
        if (key_typed(UP)) {
            game_data.exit_timer = TIME_ON_SCOREBOARD;
            if (*initials_entry.current_character == 26) {
                *initials_entry.current_character = 0;
            } else {
                *initials_entry.current_character = *initials_entry.current_character + 1;
            }
        } else if (key_typed(DOWN)) {
            game_data.exit_timer = TIME_ON_SCOREBOARD;
            if (*initials_entry.current_character == 0) {
                *initials_entry.current_character = 26;
            } else {
                *initials_entry.current_character = *initials_entry.current_character - 1;
            }
        } else if (key_typed(LEFT) || key_typed(RIGHT)) {
            game_data.exit_timer = TIME_ON_SCOREBOARD;
            if (initials_entry.current_character == &initials_entry.character_1) {
                initials_entry.current_character = &initials_entry.character_2;
            } else {
                initials_entry.current_character = &initials_entry.character_1;
            }
        }
        if (key_typed(P1_B1)) {
            game_data.exit_timer = TIME_ON_SCOREBOARD;
            game_data.initials_entered = true;
            update_high_scores();
        }
    } else {
        if (position == 10) {
            game_data.initials_entered = true;
        }
        if (successful) {
            draw_text("You Win!", COLOR_RED, font_named("default"), 20, 340, 30);
        } else {
            draw_text("Game Over", COLOR_RED, font_named("default"), 20, 340, 30);
        }

        // Display high scores
        for (int i = 0; i <= 9; i++) {
            fill_rectangle(COLOR_GRAY, 220, 70 + 45 * i, 360, 40);
            draw_text(std::to_string(i + 1) + ".", COLOR_WHITE, font_named("default"), 18, 230, 80 + 45 * i);
            draw_text(json_read_string(game_data.score_rows[i], "initials"), COLOR_WHITE, font_named("default"), 18, 260, 80 + 45 * i);
            draw_text("score: " + std::to_string(json_read_number_as_int(game_data.score_rows[i], "score")), COLOR_WHITE, font_named("default"), 18, 370, 80 + 45 * i);
        }
        draw_text("Press start to play again", COLOR_BLACK, font_named("default"), 18, 275, 530);
        draw_text("Press 2 to exit", COLOR_BLACK, font_named("default"), 18, 275, 550);
    }
}
