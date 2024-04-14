#include "splashkit.h"
#include "game_types.h"
#include "game_data.h"
#include "game_logic.h"
#include "rendering.h"
#include "resources.h"
#include "utilities.h"

game_data_struct game_data;
initials_entry_struct initials_entry = {
        {"-", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}
};

int main() {
    open_window("DX Ball Game", 800, 600);
    window_toggle_border("DX Ball Game");

    load_resources();

    game_data.scores = json_from_file("scores.json");
    for (int i = 0; i < 10; i++) {
        game_data.score_rows[i] = json_read_object(game_data.scores, "row" + std::to_string(i));
    }

    bool game_closed = false;

    while (!game_closed) {
        process_events();

        if (key_down(ESCAPE_KEY)) game_closed = true;
        if (game_data.exitTimer > 0) {
            game_data.exitTimer -= (1.0 / 60.0);
        } else if (game_data.game_start && game_data.game_over) {
            game_data.game_start = false;
            game_data.exitTimer = TIME_ON_TITLE;
            reset_game();
        } else if (!game_data.game_start) {
            game_closed = true;
        }

        if (!game_data.game_start) {
            show_title_screen();
        } else {
            if (game_data.multiplierTimer > 0) game_data.multiplierTimer -= (1.0 / 60.0);
            else if (game_data.multiplierTimer < 0) game_data.multiplierTimer = 0;
            else game_data.score_multiplier = 1;

            if (!game_data.ball_is_held) {
                if (game_data.extraBallTimer > 0) game_data.extraBallTimer -= (1.0 / 60.0);
                else if (!game_data.game_over) {
                    int randomX = rnd(0 + BALL_RADIUS, 800 - BALL_RADIUS);
                    bool direction = (bool)rnd(0, 2);
                    game_data.current_balls.push_back(create_ball(randomX, 0 + BALL_RADIUS, false, direction));
                    game_data.extraBallTimer = NEW_BALL_DELAY;
                }
            }

            if (game_data.next_level) {
                start_level();
            }

            if (key_down(LEFT) && game_data.paddle_x > 10) game_data.paddle_x -= PADDLE_SPEED;
            if (key_down(RIGHT) && game_data.paddle_x < screen_width() - PADDLE_LENGTH - 10) game_data.paddle_x += PADDLE_SPEED;

            for (int i = 0; i < game_data.current_balls.size(); i++) {
                check_ball_collision(i);
                update_ball_location(i);
            }

            for (int i = 0; i < game_data.current_powerups.size(); i++) {
                update_powerup_drops(i);
            }

            draw_game();

            if (game_data.remaining_blocks == 0 && game_data.current_level <= 4) {
                game_data.next_level = true;
                game_data.current_level++;
            }

            if (game_data.game_over) {
                end_game(game_data.game_won);

                if (game_data.initials_entered) {
                    if (key_typed(START)) reset_game();
                    if (key_typed(P1_B2)) {
                        game_data.game_start = false;
                        game_data.exitTimer = TIME_ON_TITLE;
                        reset_game();
                    }
                }
            }
        }
        // debug cheats should be mapped to keys that are not usable with the arcade machine keyboard emulator
        // Set exit timer to 1 second so timer can be tested without waiting
        // TODO: These should not be available in any production build and should be at the very least gated behind a debug flag
        if (key_typed(NUM_7_KEY)) game_data.exitTimer = 1;
        if (key_typed(NUM_8_KEY)) {
            game_data.game_won = false;
            game_data.game_over = true;
            game_data.exitTimer = TIME_ON_SCOREBOARD;
            game_data.current_balls.clear();
            game_data.current_powerups.clear();
        }

        if (key_typed(NUM_9_KEY)) { game_data.next_level = true; game_data.current_level++; }

        if (key_typed(NUM_0_KEY)) {
            game_data.multiplierTimer = MULTIPLIER_DURATION;
            if (game_data.score_multiplier < 5) game_data.score_multiplier++;
        }

        refresh_screen(60);
    }

    return 0;
}
