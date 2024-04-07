#include "level_data.h"
#include "game_data.h"

block_data * spawn_blocks_level1()
{
    game_data.remaining_blocks = BLOCKS_IN_LEVEL1; // Number of blocks remaining
    static block_data blocks[BLOCKS_IN_LEVEL1]; // Array containing blocks to be destroyed
    block_data block;
    int index = 0;

    for (int i = 0; i < 8; i++)
    {
        block = create_block(160 + i * BLOCK_WIDTH, 240, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
    }
    for (int i = 0; i < 6; i++)
    {
        block = create_block(220 + i * BLOCK_WIDTH, 260, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
        block = create_block(220 + i * BLOCK_WIDTH, 220, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
    }
    for (int i = 0; i < 4; i++)
    {
        block = create_block(280 + i * BLOCK_WIDTH, 280, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
        block = create_block(280 + i * BLOCK_WIDTH, 200, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
    }
    for (int i = 0; i < 2; i++)
    {
        block = create_block(340 + i * BLOCK_WIDTH, 300, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
        block = create_block(340 + i * BLOCK_WIDTH, 180, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
    }

    for (int i = 0; i < 12; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL1;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = MULTI_BALL;
        blocks[index].powerup_bitmap = "block_multi_ball";
    }
    for (int i = 0; i < 5; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL1;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = SCORE_MULTIPLY;
        blocks[index].powerup_bitmap = "block_multiplier_2";
    }

    return blocks;
}
block_data * spawn_blocks_level2()
{
    static block_data blocks[BLOCKS_IN_LEVEL2];
    game_data.remaining_blocks = BLOCKS_IN_LEVEL2;
    int index = 0;
    block_data block;

    for (int i = 0; i < 7; i++)
    {
        block = create_block(40 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
        block = create_block(100 + i * BLOCK_WIDTH, 300 - i  * BLOCK_HEIGHT, DOUBLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
        block = create_block(280 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
        block = create_block(340 + i * BLOCK_WIDTH, 300 - i  * BLOCK_HEIGHT, DOUBLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
    }
    for (int i = 0; i < 3; i++)
    {
        block = create_block(520 + i * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, SINGLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
        block = create_block(580 + i * BLOCK_WIDTH, 300 - i  * BLOCK_HEIGHT, DOUBLE_HIT, NO_POWERUP);
        blocks[index] = block;
        index++;
    }
    block = create_block(700, 240, SINGLE_HIT, NO_POWERUP);
    blocks[index] = block;

    for (int i = 0; i < 18; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL2;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = MULTI_BALL;
        blocks[index].powerup_bitmap = "block_multi_ball";
    }
    for (int i = 0; i < 8; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL2;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = SCORE_MULTIPLY;
        blocks[index].powerup_bitmap = "block_multiplier_2";
    }

    return blocks;
}
block_data * spawn_blocks_level3()
{
    static block_data blocks[BLOCKS_IN_LEVEL3];
    game_data.remaining_blocks = BLOCKS_IN_LEVEL3;
    int index = 0;
    block_data block;

    for(int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            block = create_block(160 + j * BLOCK_WIDTH, 260 - i * BLOCK_HEIGHT, SINGLE_HIT, NO_POWERUP);
            blocks[index] = block;
            index++;
        }
    }
    for (int i = 0; i < 12; i++)
    {
        block = create_block(40 + i * BLOCK_WIDTH, 320, HIDDEN, NO_POWERUP);
        blocks[index] = block;
        index++;
    }

    for (int i = 0; i < 20; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL3;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = MULTI_BALL;
        blocks[index].powerup_bitmap = "block_multi_ball";
    }
    for (int i = 0; i < 9; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL3;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = SCORE_MULTIPLY;
        blocks[index].powerup_bitmap = "block_multiplier_2";
    }

    return blocks;
}
block_data * spawn_blocks_level4()
{
    static block_data blocks[BLOCKS_IN_LEVEL4];
    game_data.remaining_blocks = BLOCKS_IN_LEVEL4;
    block_data block;
    int index = 0;
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            block = create_block(40 + j * BLOCK_WIDTH, 300 - i * BLOCK_HEIGHT, static_cast<block_kind>(rand() % 3), NO_POWERUP);
            blocks[index] = block;
            index++;
        }
    }

    for (int i = 0; i < 50; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL4;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = MULTI_BALL;
        blocks[index].powerup_bitmap = "block_multi_ball";
    }
    for (int i = 0; i < 30; i++)
    {
        do
        {
            index = rand() % BLOCKS_IN_LEVEL4;
        } while (blocks[index].powerup != NO_POWERUP);
        blocks[index].powerup = SCORE_MULTIPLY;
        blocks[index].powerup_bitmap = "block_multiplier_2";
    }

    return blocks;
}
