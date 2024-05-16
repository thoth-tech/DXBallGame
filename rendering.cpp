#include "include/rendering.h"
#include "include/resources.h"
#include "include/types.h"
#include "splashkit.h"
#include <cmath>
#include "include/global_instances.h"
#include "include/instance_creation.h"

void draw_blocks() {
    // Iterate through all the blocks in the current level
    for (int i = 0; i < game_data.blocks_in_level; i++) {
        // Only draw blocks with remaining hit points
        if (game_data.blocks[i].hit_points > 0) {
            // Draw the block bitmap
            draw_bitmap(game_data.blocks[i].block_bitmap, game_data.blocks[i].x, game_data.blocks[i].y);

            // Draw the power-up bitmap if the block is not hidden or has only one hit point remaining
            if (!(game_data.blocks[i].kind == BlockKind::HIDDEN && game_data.blocks[i].hit_points > 1)) {
                draw_bitmap(game_data.blocks[i].power_up_bitmap, game_data.blocks[i].x, game_data.blocks[i].y);
            }
        }
    }
}

void draw_game() {
    // Clear the screen with black color
    clear_screen(COLOR_BLACK);

    // Draw the blocks
    draw_blocks();

    // Draw the balls
    for (const auto& ball : game_data.current_balls) {
        draw_bitmap("ball", ball.x, ball.y);
    }

    // Draw the "Press 1 to start" text if the ball is held
    if (game_data.ball_is_held) {
        draw_text("Press 1 to start", COLOR_WHITE, font_named("default"), 35, 230, (screen_height() / 2) + 50);
    }

    // Draw the power-up drops
    for (const auto& power_up : game_data.current_power_ups) {
        draw_bitmap(get_power_up_bitmap(power_up.kind), power_up.x, power_up.y);
    }

    // Draw the paddle
    draw_bitmap("paddle", game_data.paddle_x, PADDLE_Y);

    // Draw the score text
    draw_text("SCORE:" + std::to_string(game_data.score), COLOR_WHITE, font_named("default"), 35, 20, 20);

    // Draw the score multiplier gauge
    if (game_data.score_multiplier > 1) {
        // Calculate the gauge position based on the score digits
        int gauge_x = 170 + (20 * static_cast<int>(std::log10(game_data.score)));

        // Draw the empty gauge bitmap
        draw_bitmap("gauge_empty_" + std::to_string(game_data.score_multiplier), gauge_x, 24, option_scale_bmp(1, 1));

        // Get the filled gauge bitmap
        bitmap filled_bitmap = bitmap_named("gauge_full_" + std::to_string(game_data.score_multiplier));

        // Calculate the filled portion of the gauge based on the multiplier timer
        rectangle bitmap_part = bitmap_bounding_rectangle(filled_bitmap);
        bitmap_part.height = bitmap_height(filled_bitmap) * game_data.multiplier_timer / 10.0;
        bitmap_part.y = bitmap_height(filled_bitmap) - bitmap_part.height;

        // Draw the filled portion of the gauge
        draw_bitmap(filled_bitmap, gauge_x + 1, 25 + (bitmap_height(filled_bitmap) - bitmap_part.height), option_scale_bmp(1, 1, option_part_bmp(bitmap_part)));
    }
}

void show_title_screen() {
    // Clear the screen with black color
    clear_screen(COLOR_BLACK);

    // Draw the title bitmap
    draw_bitmap("title", 0, 0);

    // Check if the start key is pressed
    if (key_typed(START)) {
        play_sound_effect("sfx_start_game");
        game_data.game_start = true;
    }
}
