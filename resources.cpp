#include "include/resources.h"
#include "include/types.h"
#include "include/global_constants.h"
#include "include/global_instances.h"

void load_resources() {
    // Load the resource bundle
    load_resource_bundle("game_bundle", "bundle.txt");

    // Load individual bitmaps
    load_bitmap("ball", "ball.png");
    load_bitmap("paddle", "platform.png");
    load_bitmap("title", "title.png");

    // Load block bitmaps
    load_bitmap("block_single_hit", "5.png");
    load_bitmap("block_double_hit_1", "8.png");
    load_bitmap("block_double_hit_2", "9.png");
    load_bitmap("block_hidden_1", "transparent.png");
    load_bitmap("block_hidden_2", "3.png");

    // Load power-up block bitmaps
    load_bitmap("block_multi_ball", "multiball_block.png");
    load_bitmap("block_multiplier_2", "multiplier_block.png");
    load_bitmap("block_multiplier_3", "multiplier_3_block.png");
    load_bitmap("block_multiplier_4", "multiplier_4_block.png");
    load_bitmap("block_multiplier_5", "multiplier_5_block.png");

    // Load score multiplier gauge bitmaps
    load_bitmap("gauge_empty_2", "gauge_empty_2.png");
    load_bitmap("gauge_full_2", "gauge_full_2.png");
    load_bitmap("gauge_empty_3", "gauge_empty_3.png");
    load_bitmap("gauge_full_3", "gauge_full_3.png");
    load_bitmap("gauge_empty_4", "gauge_empty_4.png");
    load_bitmap("gauge_full_4", "gauge_full_4.png");
    load_bitmap("gauge_empty_5", "gauge_empty_5.png");
    load_bitmap("gauge_full_5", "gauge_full_5.png");

    // Load power-up drop bitmaps
    load_bitmap("dropped_multi_ball", "dropped_multiball.png");
    load_bitmap("dropped_multiplier_2", "dropped_multiplier.png");
    load_bitmap("dropped_multiplier_3", "dropped_multiplier_3.png");
    load_bitmap("dropped_multiplier_4", "dropped_multiplier_4.png");
    load_bitmap("dropped_multiplier_5", "dropped_multiplier_5.png");

    // Load sound effects
    load_sound_effect("sfx_break_block", "hurt_c_08-102842.wav");
    load_sound_effect("sfx_powerup", "video-game-powerup-38065.wav");
    load_sound_effect("sfx_bounce_ball", "stop-13692.wav");
    load_sound_effect("sfx_start_game", "message-incoming-132126.wav");
    load_sound_effect("sfx_win", "winsquare-6993.wav");
}

bitmap get_power_up_bitmap(PowerUpKind kind) {
    // Return the appropriate bitmap based on the power-up kind
    switch (kind) {
        case PowerUpKind::MULTI_BALL:
            return bitmap_named("dropped_multi_ball");
        case PowerUpKind::SCORE_MULTIPLY:
            return bitmap_named("dropped_multiplier_" + std::to_string(game_data.score_multiplier + 1));
        default:
            return bitmap_named("dropped_multi_ball");
    }
}
