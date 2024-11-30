#pragma once

#include <Color.h>
#include <Size.h>


namespace Config
{
    // Window
    static char const* const WINDOW_TITLE = "TRPG";

    static bool const BORDERLESS = false;
    static bool const USE_CONFIG_WINDOW_SIZE = false;
    static Size const WINDOW_SIZE = Size(900, 600);

    // Debug
    static bool const DEBUG = false;

    static bool const SHOW_COLLIDERS = true && DEBUG;

    static Color const COLLIDERS_COLOR = Color::Red;
    static Color const VISIBLE_RECT_COLOR = Color::Blue;
}
