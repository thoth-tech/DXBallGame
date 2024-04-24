#include "splashkit.h"
#include "include/types.h"
#include "include/global_constants.h"
#include "include/global_state.h"
#include "include/instance_creation.h"
#include "include/instance_state.h"
#include "include/rendering.h"
#include "include/resources.h"

GameData game_data;
InitialsEntryData initials_entry = {
        {"-", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}
};

int main() {
    // Open the game window and toggle the border
    open_window("DX Ball Game", 800, 600);
    window_toggle_border("DX Ball Game");

    // Load game resources
    load_resources();

    // Load high scores from JSON file
    game_data.scores = json_from_file("scores.json");
    for (int i = 0; i < 10; i++) {
        game_data.score_rows[i] = json_read_object(game_data.scores, "row" + std::to_string(i));
    }

    bool game_closed = false;

    // Main game loop
    while (!game_closed) {
        // Process user input events
        process_events();

        // Check if the escape key is pressed to close the game
        if (key_down(ESCAPE_KEY)) {
            game_closed = true;
        }

        // Update the exit timer and handle game over state
        if (game_data.exit_timer > 0) {
            game_data.exit_timer -= (1.0 / 60.0);
        } else if (game_data.game_start && game_data.game_over) {
            game_data.game_start = false;
            game_data.exit_timer = TIME_ON_TITLE;
            reset_game();
        } else if (!game_data.game_start) {
            game_closed = true;
        }

        // Show the title screen if the game hasn't started
        if (!game_data.game_start) {
            show_title_screen();
        } else {
            // Update the score multiplier timer
            if (game_data.multiplier_timer > 0) {
                game_data.multiplier_timer -= (1.0 / 60.0);
            } else if (game_data.multiplier_timer < 0) {
                game_data.multiplier_timer = 0;
            } else {
                game_data.score_multiplier = 1;
            }

            // Spawn new balls if the extra ball timer has expired and the game is not over
            if (!game_data.ball_is_held) {
                if (game_data.extra_ball_timer > 0) {
                    game_data.extra_ball_timer -= (1.0 / 60.0);
                } else if (!game_data.game_over) {
                    int random_x = rnd(0 + BALL_RADIUS, 800 - BALL_RADIUS);
                    bool direction = static_cast<bool>(rnd(0, 2));
                    game_data.current_balls.push_back(create_ball(random_x, 0 + BALL_RADIUS, false, direction));
                    game_data.extra_ball_timer = NEW_BALL_DELAY;
                }
            }

            // Start a new level if the next level flag is set
            if (game_data.next_level) {
                start_level();
            }

            // Update the paddle position based on user input
            if (key_down(LEFT) && game_data.paddle_x > 10) {
                game_data.paddle_x -= PADDLE_SPEED;
            }
            if (key_down(RIGHT) && game_data.paddle_x < screen_width() - PADDLE_LENGTH - 10) {
                game_data.paddle_x += PADDLE_SPEED;
            }

            // Update ball positions and check for collisions
            for (int i = 0; i < game_data.current_balls.size(); i++) {
                check_ball_collision(i);
                update_ball_location(i);
            }

            // Update power-up drop positions
            for (int i = 0; i < game_data.current_power_ups.size(); i++) {
                update_power_up_drops(i);
            }

            // Render the game graphics
            draw_game();

            // Check if the level is complete and advance to the next level
            if (game_data.remaining_blocks == 0 && game_data.current_level <= 4) {
                game_data.next_level = true;
                game_data.current_level++;
            }

            // Handle game over state
            if (game_data.game_over) {
                end_game(game_data.game_won);

                // Check if initials have been entered and handle user input
                if (game_data.initials_entered) {
                    if (key_typed(START)) {
                        reset_game();
                    }
                    if (key_typed(P1_B2)) {
                        game_data.game_start = false;
                        game_data.exit_timer = TIME_ON_TITLE;
                        reset_game();
                    }
                }
            }
        }
        // Debug cheats (not available in production build)
        if (key_typed(NUM_7_KEY)) {
            game_data.exit_timer = 1;
        }
        if (key_typed(NUM_8_KEY)) {
            game_data.game_won = false;
            game_data.game_over = true;
            game_data.exit_timer = TIME_ON_SCOREBOARD;
            game_data.current_balls.clear();
            game_data.current_power_ups.clear();
        }
        if (key_typed(NUM_9_KEY)) {
            game_data.next_level = true;
            game_data.current_level++;
        }
        if (key_typed(NUM_0_KEY)) {
            game_data.multiplier_timer = MULTIPLIER_DURATION;
            if (game_data.score_multiplier < 5) {
                game_data.score_multiplier++;
            }
        }

        // Refresh the screen at 60 frames per second
        refresh_screen(60);
    }

    return 0;
}
