#include "game_logic.h"

void reset_game() {
    game_data.score = 0;
    game_data.game_over = false;
    game_data.game_won = false;
    game_data.current_level = 1;
    game_data.next_level = true;
    game_data.multiplierTimer = 0;
    game_data.score_multiplier = 1;
    game_data.extraBallTimer = NEW_BALL_DELAY;
    game_data.initials_entered = false;
    initials_entry.character1 = 0;
    initials_entry.character2 = 0;
    initials_entry.current_character = &initials_entry.character1;
    game_data.blocks = spawn_blocks_level1();
    game_data.blocks_in_level = BLOCKS_IN_LEVEL1;
    game_data.paddle_x = (screen_width() - PADDLE_LENGTH) / 2;
    game_data.current_balls.clear();
    game_data.current_balls.push_back(create_ball(50, 50, true, true));
    game_data.ball_is_held = true;
    clear_screen(COLOR_BLACK);
    draw_blocks();
    draw_bitmap("paddle", game_data.paddle_x, PADDLE_Y);
}

void start_level() {
    switch (game_data.current_level) {
        case 1:
            game_data.blocks = spawn_blocks_level1();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL1;
            break;
        case 2:
            game_data.blocks = spawn_blocks_level2();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL2;
            break;
        case 3:
            game_data.blocks = spawn_blocks_level3();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL3;
            break;
        case 4:
            game_data.blocks = spawn_blocks_level4();
            game_data.blocks_in_level = BLOCKS_IN_LEVEL4;
            break;
        default:
            play_sound_effect("sfx_win");
            game_data.game_won = true;
            game_data.game_over = true;
            game_data.exitTimer = TIME_ON_SCOREBOARD;
            break;
    }
    game_data.score_multiplier = 1;
    game_data.multiplierTimer = 0;
    game_data.current_powerups.clear();
    game_data.paddle_x = (screen_width() - PADDLE_LENGTH) / 2;
    game_data.next_level = false;
    game_data.current_balls.clear();
    game_data.current_balls.push_back(create_ball(50, 50, true, true));
    game_data.ball_is_held = true;
}

void end_game(bool successful) {
    fill_rectangle(COLOR_LIGHT_GRAY, 200, 20, 400, 560);
    int position = high_score_position();
    if (!game_data.initials_entered && position != 10) {
        draw_text("Enter initials", COLOR_BLACK, font_named("default"), 30, 280, 100);
        draw_text(initials_entry.characters[initials_entry.character1], COLOR_BLACK, font_named("default"), 50, 360, 180);
        draw_text(initials_entry.characters[initials_entry.character2], COLOR_BLACK, font_named("default"), 50, 400, 180);
        if (initials_entry.current_character == &initials_entry.character1) {
            fill_triangle(COLOR_BLACK, 374, 165, 364, 175, 384, 175);
            fill_triangle(COLOR_BLACK, 374, 240, 364, 230, 384, 230);
        } else {
            fill_triangle(COLOR_BLACK, 414, 165, 404, 175, 424, 175);
            fill_triangle(COLOR_BLACK, 414, 240, 404, 230, 424, 230);
        }
        draw_text("Press 1 to submit", COLOR_BLACK, font_named("default"), 30, 260, 280);
        if (key_typed(UP)) {
            game_data.exitTimer = TIME_ON_SCOREBOARD;
            if (*initials_entry.current_character == 26) *initials_entry.current_character = 0;
            else *initials_entry.current_character = *initials_entry.current_character + 1;
        } else if (key_typed(DOWN)) {
            game_data.exitTimer = TIME_ON_SCOREBOARD;
            if (*initials_entry.current_character == 0) *initials_entry.current_character = 26;
            else *initials_entry.current_character = *initials_entry.current_character - 1;
        } else if (key_typed(LEFT) || key_typed(RIGHT)) {
            game_data.exitTimer = TIME_ON_SCOREBOARD;
            if (initials_entry.current_character == &initials_entry.character1) {
                initials_entry.current_character = &initials_entry.character2;
            } else {
                initials_entry.current_character = &initials_entry.character1;
            }
        }
        if (key_typed(P1_B1)) {
            game_data.exitTimer = TIME_ON_SCOREBOARD;
            game_data.initials_entered = true;
            update_scores();
        }
    } else {
        if (position == 10) game_data.initials_entered = true;
        if (successful) {
            draw_text("You Win!", COLOR_RED, font_named("default"), 20, 340, 30);
        } else {
            draw_text("Game Over", COLOR_RED, font_named("default"), 20, 340, 30);
        }
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

void break_block(block_data blocks[], int block_index, int &score, int &remaining_blocks, int multiplier)
{
    blocks[block_index].hitpoint--;
    score += multiplier;
    if(blocks[block_index].hitpoint == 0)
    {
        remaining_blocks--;
        play_sound_effect("sfx_break_block");
        if (game_data.blocks[block_index].powerup != NO_POWERUP) // if the ball collided with any side of a powerup block
        {
            //create powerup drop
            powerup_drop_data new_powerup;
            new_powerup.x = game_data.blocks[block_index].x;
            new_powerup.y = game_data.blocks[block_index].y;
            new_powerup.kind = game_data.blocks[block_index].powerup;

            game_data.current_powerups.push_back(new_powerup);
        }
    }
    else if (blocks[block_index].kind == DOUBLE_HIT)
    {
        play_sound_effect("sfx_bounce_ball", (float) 0.25);
        blocks[block_index].block_bitmap = "block_double_hit_2"; // Change color of bricks hit but not destroyed yet
    }
    else if (blocks[block_index].kind == HIDDEN)
    {
        play_sound_effect("sfx_bounce_ball", (float) 0.25);
        blocks[block_index].block_bitmap = "block_hidden_2";
    }
}

void check_ball_collision(int i) {
    if (game_data.current_balls[i].x - BALL_RADIUS <= 0) {
        play_sound_effect("sfx_bounce_ball", (float) 0.25);
        game_data.current_balls[i].right = true;
    }
    if (game_data.current_balls[i].x + BALL_RADIUS >= screen_width()) {
        play_sound_effect("sfx_bounce_ball", (float) 0.25);
        game_data.current_balls[i].right = false;
    }
    if (game_data.current_balls[i].y - BALL_RADIUS <= 0) {
        play_sound_effect("sfx_bounce_ball", (float) 0.25);
        game_data.current_balls[i].up = false;
    }
    if (game_data.current_balls[i].y + BALL_RADIUS >= screen_height() && !game_data.game_over) {
        // TODO: this is assigning the last element to the current element, then removing the last element
        // this is not the same as removing the current element (although it will kind of work)
        game_data.current_balls[i] = game_data.current_balls[game_data.current_balls.size() - 1];
        game_data.current_balls.pop_back();
        if (game_data.current_balls.size() == 0) {
            game_data.game_won = false;
            game_data.game_over = true;
            game_data.exitTimer = TIME_ON_SCOREBOARD;
            game_data.current_powerups.clear();
        }
    }
    if ((PADDLE_Y <= game_data.current_balls[i].y + BALL_RADIUS && game_data.current_balls[i].y + BALL_RADIUS <= PADDLE_Y + BALL_SPEED) && (game_data.current_balls[i].x + BALL_RADIUS >= game_data.paddle_x && game_data.current_balls[i].x - BALL_RADIUS <= game_data.paddle_x + PADDLE_LENGTH)) {
        play_sound_effect("sfx_bounce_ball", (float) 0.25);
        game_data.current_balls[i].up = true;
    }
    for (int j = 0; j < game_data.blocks_in_level; j++) {
        if (game_data.blocks[j].hitpoint > 0) {
            if (game_data.current_balls[i].x > game_data.blocks[j].x && game_data.current_balls[i].x < game_data.blocks[j].x + BLOCK_WIDTH) {
                if (game_data.blocks[j].y + BLOCK_HEIGHT - BALL_SPEED <= game_data.current_balls[i].y - BALL_RADIUS && game_data.current_balls[i].y - BALL_RADIUS <= game_data.blocks[j].y + BLOCK_HEIGHT) {
                    game_data.current_balls[i].up = false;
                    break_block(game_data.blocks, j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
                if (game_data.blocks[j].y <= game_data.current_balls[i].y + BALL_RADIUS && game_data.current_balls[i].y + BALL_RADIUS <= game_data.blocks[j].y + BALL_SPEED) {
                    game_data.current_balls[i].up = true;
                    break_block(game_data.blocks, j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
            }
            if (game_data.current_balls[i].y + BALL_RADIUS > game_data.blocks[j].y && game_data.current_balls[i].y - BALL_RADIUS < game_data.blocks[j].y + BLOCK_HEIGHT) {
                if (game_data.blocks[j].x + BLOCK_WIDTH <= game_data.current_balls[i].x - BALL_RADIUS - BALL_SPEED && game_data.current_balls[i].x - BALL_RADIUS <= game_data.blocks[j].x + BLOCK_WIDTH) {
                    game_data.current_balls[i].right = true;
                    break_block(game_data.blocks, j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
                if (game_data.blocks[j].x <= game_data.current_balls[i].x + BALL_RADIUS && game_data.current_balls[i].x + BALL_RADIUS <= game_data.blocks[j].x + BALL_SPEED) {
                    game_data.current_balls[i].right = false;
                    break_block(game_data.blocks, j, game_data.score, game_data.remaining_blocks, game_data.score_multiplier);
                }
            }
        }
    }
}

void update_ball_location(int i) {
    if (!game_data.ball_is_held) {
        if (game_data.current_balls[i].up) game_data.current_balls[i].y -= BALL_SPEED;
        else game_data.current_balls[i].y += BALL_SPEED;
        if (game_data.current_balls[i].right) game_data.current_balls[i].x += BALL_SPEED;
        else game_data.current_balls[i].x -= BALL_SPEED;
    } else {
        game_data.current_balls[i].x = game_data.paddle_x + PADDLE_LENGTH / 2 - BALL_RADIUS;
        game_data.current_balls[i].y = PADDLE_Y - 25;
    }
    if (game_data.ball_is_held && key_down(P1_B1)) game_data.ball_is_held = false;
}

void update_powerup_drops(int i) {
    game_data.current_powerups[i].y += BALL_SPEED / 2;
    if (game_data.current_powerups[i].y + BALL_RADIUS >= screen_height()) {
        game_data.current_powerups[i] = game_data.current_powerups[game_data.current_powerups.size() - 1];
        game_data.current_powerups.pop_back();
    }
    if ((PADDLE_Y <= game_data.current_powerups[i].y + BALL_RADIUS && game_data.current_powerups[i].y + BALL_RADIUS <= PADDLE_Y + (BALL_SPEED / 2)) && (game_data.current_powerups[i].x + BALL_RADIUS >= game_data.paddle_x && game_data.current_powerups[i].x - BALL_RADIUS <= game_data.paddle_x + PADDLE_LENGTH)) {
        bool direction = (bool)rnd(0, 2);
        play_sound_effect("sfx_powerup", (float) 0.5);
        if (game_data.current_powerups[i].kind == MULTI_BALL) game_data.current_balls.push_back(create_ball(game_data.current_powerups[i].x, PADDLE_Y + 10, true, direction));
        else if (game_data.current_powerups[i].kind == SCORE_MULTIPLY) {
            game_data.multiplierTimer = MULTIPLIER_DURATION;
            if (game_data.score_multiplier < 5) game_data.score_multiplier++;
        }
        game_data.current_powerups[i] = game_data.current_powerups[game_data.current_powerups.size() - 1];
        game_data.current_powerups.pop_back();
    }
}
