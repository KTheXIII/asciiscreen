#include <iostream>

#include <cmath>
#include <unistd.h>

#include "ace/display.h"
#include "ace/unicode.h"

// clang-format off
// https://www.asciiart.eu/animals/birds-water
constexpr auto PENGUIN_SMALL_SPRITE =
    L" __   "
    L"( o>  "
    L"///\\  "
    L"\\V_/_ ";

constexpr auto PENGUIN_SPRITE = 
    L"      __         "
    L"   -=(o '.       "
    L"      '.-.\\      "
    L"      /|  \\\\     "
    L"      '|  ||     "
    L"       _\\_):,_   ";
// clang-format on

auto main(int argc, char const* argv[]) -> int {
    ace::display display;
    display.set_input_timeout(0);
    display.show_cursor(false);

    ace::sprite sprite(6, 4, PENGUIN_SMALL_SPRITE);
    ace::sprite sprite1(17, 6, PENGUIN_SPRITE);

    bool isRunning = true;

    float x = 0;
    float y = 0;

    std::wstring version(L"ace: v");
    version += std::to_wstring(display.get_version().MAJOR) + L".";
    version += std::to_wstring(display.get_version().MINOR) + L".";
    version += std::to_wstring(display.get_version().PATCH);

    while (isRunning) {
        auto input = display.key();
        if (input == 'q') isRunning = false;

        x = display.width() / 2 - sprite.width() / 2;
        y = display.height() / 2 - sprite.height() / 2;

        display.poll_events();

        display.clear();
        display.draw(std::round(x), std::round(y), sprite);
        display.draw(0, 2, sprite1);
        display.print(0, 0, version);
        display.show();

        usleep(16666);
    }

    return 0;
}
