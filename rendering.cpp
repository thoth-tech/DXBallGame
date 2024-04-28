#include "rendering.h"
#include "resources.h"
#include "game_types.h"
#include "game_data.h"
#include "splashkit.h"
#include <cmath>

void draw_blocks() {
    for (int i = 0; i < game_data.blocks_in_level; i++) {
        if (game_data.blocks[i].hitpoint > 0) {
            draw_bitmap(game_data.blocks[i].block_bitmap, game_data.blocks[i].x, game_data.blocks[i].y);
            if (!(game_data.blocks[i].kind == HIDDEN && game_data.blocks[i].hitpoint > 1)) {
                draw_bitmap(game_data.blocks[i].powerup_bitmap, game_data.blocks[i].x, game_data.blocks[i].y);
            }
        }
    }
}

void draw_game() {
    clear_screen(COLOR_BLACK);
    draw_blocks();
    for (int i = 0; i < game_data.current_balls.size(); i++) {
        draw_bitmap("ball", game_data.current_balls[i].x, game_data.current_balls[i].y);
    }
    if (game_data.ball_is_held) {
        draw_text("Press 1 to start", COLOR_WHITE, font_named("default"), 35, 230, (screen_height() / 2) + 50);
    }
    for (int i = 0; i < game_data.current_powerups.size(); i++) {
        draw_bitmap(get_powerup_bitmap(game_data.current_powerups[i].kind), game_data.current_powerups[i].x, game_data.current_powerups[i].y);
    }
    draw_bitmap("paddle", game_data.paddle_x, PADDLE_Y);
    draw_text("SCORE:" + std::to_string(game_data.score), COLOR_WHITE, font_named("default"), 35, 20, 20);

    if (game_data.score_multiplier > 1) {
        // gauge is moved 20px to the right for every power of 10 that the score has so that the score number and multiplier gauge never overlap
        draw_bitmap("gauge_empty_" + std::to_string(game_data.score_multiplier), 170 + (20*floor(log10(game_data.score))), 24, option_scale_bmp(1,1));
        bitmap filled_bitmap = bitmap_named("gauge_full_" + std::to_string(game_data.score_multiplier)); //Get bitmap with appropriate number
        rectangle bitmap_part = bitmap_bounding_rectangle(filled_bitmap); //Create bounding rectange for displaying part of the sprite's height
        bitmap_part.height = bitmap_height(filled_bitmap) * game_data.multiplierTimer/10.0; //Shrink foreground as the timer goes down
        bitmap_part.y = bitmap_height(filled_bitmap) - bitmap_part.height; //Move foreground down to line up with background
        draw_bitmap(filled_bitmap, 171 + (20*floor(log10(game_data.score))), 25 + (bitmap_height(filled_bitmap) - bitmap_part.height), option_scale_bmp(1,1,option_part_bmp(bitmap_part))); //draw foreground
    }
}

void show_title_screen() {
    clear_screen(COLOR_BLACK);
    draw_bitmap("title", 0, 0);
    if (key_typed(START)) {
        play_sound_effect("sfx_start_game");
        game_data.game_start = true;
    }
}

