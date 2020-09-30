#pragma once

enum class Direction
{
    NONE = 0,
    LEFT = 1,
    UP = 2,
    DOWN = 3,
    RIGHT = 4
};

enum class GameState
{
    BEFORE_FIRST_RUN = 0,
    GAME_RUNNING = 1,
    GAME_STOPPED = 2
};

enum class GameResult
{
    NO_RESULT_YET = 0,
    GAME_LOST = 1,
    GAME_WIN = 2
};
