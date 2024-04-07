#include "utilities.h"

int high_score_position() {
    for (int i = 0; i < 10; i++) {
        if (json_read_number_as_int(game_data.score_rows[i], "score") < game_data.score) {
            return i;
        }
    }
    return 10;
}

void update_scores() {
    int position = high_score_position();
    for (int i = 9; i > position; i--) {
        json_set_number(game_data.score_rows[i], "score", json_read_number_as_int(game_data.score_rows[i - 1], "score"));
        json_set_string(game_data.score_rows[i], "initials", json_read_string(game_data.score_rows[i - 1], "initials"));
    }
    json_set_number(game_data.score_rows[position], "score", game_data.score);
    string initials = initials_entry.characters[initials_entry.character1] + initials_entry.characters[initials_entry.character2];
    json_set_string(game_data.score_rows[position], "initials", initials);
    for (int i = 0; i < 10; i++) {
        json_set_object(game_data.scores, "row" + std::to_string(i), game_data.score_rows[i]);
    }
    json_to_file(game_data.scores, "scores.json");
}

block_data create_block(double x, double y, block_kind kind, powerups powerup) {
    block_data block;
    block.x = x;
    block.y = y;
    block.kind = kind;
    switch (kind) {
        case SINGLE_HIT:
            block.hitpoint = 1;
            block.block_bitmap = "block_single_hit";
            break;
        case DOUBLE_HIT:
            block.hitpoint = 2;
            block.block_bitmap = "block_double_hit_1";
            break;
        case HIDDEN:
            block.hitpoint = 2;
            block.block_bitmap = "block_hidden_1";
            break;
    }
    switch (powerup) {
        case NO_POWERUP:
            block.powerup_bitmap = "block_hidden_1";
            break;
        case MULTI_BALL:
            block.powerup_bitmap = "block_multi_ball";
            break;
        case SCORE_MULTIPLY:
            block.powerup_bitmap = "block_multiplier_2";
            break;
        default:
            block.powerup_bitmap = "block_multi_ball";
            break;
    }
    block.powerup = powerup;
    return block;
}

ball_data create_ball(double x, double y, bool up, bool right) {
    ball_data ball;
    ball.x = x;
    ball.y = y;
    ball.up = up;
    ball.right = right;
    return ball;
}
