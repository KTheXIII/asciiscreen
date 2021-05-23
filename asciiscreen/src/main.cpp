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

constexpr auto JOYSTICK_SPRITE = 
    L"     __\n" 
    L"    (  )\n" 
    L"     ||\n"
    L"     ||\n"
    L" ___|  |__.._\n" 
    L"/____________\\\n"
    L"\\____________/~~~.\n";

constexpr auto DOLPHIN_SPRITE =
L"                              _.\n"
L"                             / (\n"
L"                            /  |\n"
L"                           /   |\n"
L"            ,.____________/    (______,                   .__ \n"
L"       ,_--'                           \"----._.          / /  \n"
L"     ,\"                                        \"---____ /  ;  \n"
L" ___/._-                                               `--'_ \n"
L"(___   9                                 ,._____.         / \\  \n"
L" `---`,     |   \\               ,___.---'        `-------',  `-,\n"
L"       `--__\\    |________.----'                          \\___/\n"
L"             \\   |\n"
L"              \\  |\n"
L"               \\_;\n";
// clang-format on

auto main(int argc, char const* argv[]) -> int {
    ace::display display;
    display.set_input_timeout(0);
    display.show_cursor(false);

    ace::sprite sprite(6, 4, PENGUIN_SMALL_SPRITE);
    ace::sprite sprite1(17, 6, PENGUIN_SPRITE);
    ace::sprite spritejoystick(JOYSTICK_SPRITE);
    ace::sprite dolphin(DOLPHIN_SPRITE);

    bool isRunning = true;

    float x = 0;
    float y = 0;

    std::wstring version(L"ace: v");
    version += std::to_wstring(display.get_version().MAJOR) + L".";
    version += std::to_wstring(display.get_version().MINOR) + L".";
    version += std::to_wstring(display.get_version().PATCH);

    std::wstring sprite_info = std::to_wstring(spritejoystick.width());
    sprite_info += L",";
    sprite_info += std::to_wstring(spritejoystick.height());

    while (isRunning) {
        auto input = display.key();
        if (input == 'q') isRunning = false;

        x = display.width() / 2 - sprite.width() / 2;
        y = display.height() / 2 - sprite.height() / 2;

        display.poll_events();

        display.clear();
        display.draw(std::round(x), std::round(y), sprite);
        display.draw(0, 2, sprite1);
        display.draw(10, 10, spritejoystick);
        display.draw(50, 5, dolphin);
        display.print(0, 0, version);
        display.print(0, 1, sprite_info);
        display.show();

        usleep(16666);
    }

    return 0;
}
