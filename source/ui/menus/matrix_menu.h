#pragma once

enum class MATRIX_MENU
{
    MIN_CHOICE   = 1,
    MAX_CHOICE   = 7,
    FILL         = 1,
    PRINT        = 2,
    SORT         = 3,
    SAVE_DATA    = 4,
    LOAD_DATA    = 5,
    SAVE_RESULTS = 6,
    QUIT         = 7,
};

enum class MATRIX_CREATE
{
    MIN_CHOICE = 1,
    MAX_CHOICE = 3,
    RANDOM     = 1,
    KEYBOARD   = 2,
    FROM_FILE  = 3,
};

enum class SORT_MENU
{
    MIN_CHOICE = 1,
    MAX_CHOICE = 7,
    ALL        = 1,
    BUBBLE     = 2,
    SELECTION  = 3,
    INSERT     = 4,
    SHELL      = 5,
    QUICK      = 6,
    BACK       = 7,
};

void MatrixMenu();
