#pragma once
#include <string>


namespace Snake
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;
    const std::string ASSET_FOLDER = "assets/";
    const std::string RECORDS_TABLE_FILE = "save/save.txt";

    const int BLOCK_SIZE = 40;
    const int ROW = WINDOW_WIDTH / BLOCK_SIZE;
    const int COL = WINDOW_HEIGHT / BLOCK_SIZE;

    const float SNAKE_SPEED = 14.f;
    const int SNAKE_START_SEGMENTS_COUNT = 3;
    const int SNAKE_SEGMENTS_ADD = 1;

    const int MAX_MENU_RECORD_VISIBLE = 10;
    const int MAX_GAMEOVER_RECORD_VISIBLE = 5;

    const float TIME_PAUSE_TO_PLAY = 3.f;
    const float TIME_PER_PLAY = 3.f;

    const int WIN_MULTIPLIER = 30;

    const int SNAKE_SPEED_SIMPLE = 1;
    const int SNAKE_SPEED_HARDER_SIMPLE = 2;
    const int SNAKE_SPEED_MEDIUM = 3;
    const int SNAKE_SPEED_EASIER_HARD = 4;
    const int SNAKE_SPEED_HARD = 5;

    const int EXTRA_POINTS_SIMPLE = 2;
    const int EXTRA_POINTS_HARDER_SIMPLE = 4;
    const int EXTRA_POINTS_MEDIUM = 6;
    const int EXTRA_POINTS_EASIER_HARD = 8;
    const int EXTRA_POINTS_HARD = 10;

    const float APPLE_MOD_SPAWN_INTERVAL = 5.f;
    const float APPLE_MOD_TIMER_INTERVAL = 10.f;
    const float LARGE_APPLE_SCORE_BONUS_MULTIPLIER = 3.f;
    const float POISONED_APPLE_TIMER_EFFECT = 3.f;
    const int POISONED_APPLE_DEBUFF_SPEED = 2;
    const float REVERSE_APPLE_TIMER_EFFECT = 3.f;

    const float PORTAL_SPAWN_INTERVAL = 10.0f;
    const float PORTAL_LIFE_TIME_DURATION = 6.0f;
}