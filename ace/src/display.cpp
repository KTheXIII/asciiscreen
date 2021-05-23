#include "display.h"
#include "info.h"

#include <stdexcept>
#include <array>
#include <locale>
#include <iostream>

#include "unicode.h"

namespace ace {

    display* display::s_instance = nullptr;
    display::version display::s_version = {
        .MAJOR = ACE_MAJOR_VERSION,
        .MINOR = ACE_MINOR_VERSION,
        .PATCH = ACE_PATCH_VERSION,
    };
    display& display::get_instance() {
        if (s_instance == nullptr)
            throw std::runtime_error("display has not been initialised!");
        return *s_instance;
    }

    display::display() {
        if (s_instance != nullptr) {
            throw std::runtime_error("display has is initialised!");
            return;
        }
        setlocale(LC_ALL, "");
        m_ncurses = initscr();
        cbreak();
        noecho();

        keypad(stdscr, true);
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
        std::cout << "\033[?1003h\n";
        mouseinterval(0);

        m_width = getmaxx(stdscr);
        m_height = getmaxy(stdscr);

        m_buffer = std::make_unique<sprite>(m_width, m_height);
    }
    display::~display() {
        // Clean up ncurses and restore the terminal
        std::cout << "\033[?1003l\n";
        endwin();
    }

    void display::set_input_timeout(const int32_t& time) {
        timeout(time);
        mouseinterval(time);
    }
    void display::show_cursor(const bool& enable) { curs_set(enable); }

    void display::poll_events() {
        int32_t c = getch();

        switch (c) {
            case ERR:
                break;
            case KEY_MOUSE:
                MEVENT mev;
                if (getmouse(&mev) == OK) {
                    m_mousex = mev.x;
                    m_mousey = mev.y;
                }
                break;
            case KEY_RESIZE:
                m_width = getmaxx(stdscr);
                m_height = getmaxy(stdscr);
                m_buffer = std::make_unique<sprite>(m_width, m_height);
                break;
            default:
                m_key = c;
                break;
        }
    }

    void display::clear() {
        for (int32_t i = 0; i < m_height; i++) {
            for (int32_t j = 0; j < m_width; j++) {
                m_buffer->set_data(j, i, L' ');
                m_buffer->set_color(j, i, 0);
            }
        }
    }
    void display::print(const int32_t& x, const int32_t& y,
                        const std::wstring& text) {
        int32_t row = y;
        int32_t col = x;
        for (int32_t i = 0; i < text.length(); i++) {
            m_buffer->set_data(col, row, text[i]);
            col++;
            if (text[i] == L'\n') {
                col = x;
                row++;
            }
        }
    }
    void display::draw(const int32_t& x, const int32_t& y,
                       const sprite& sprite) {
        const auto width = sprite.width();
        const auto height = sprite.height();

        for (int32_t i = 0; i < height; i++) {
            for (int32_t j = 0; j < width; j++) {
                m_buffer->set_data(j + x, i + y, sprite.data(j, i));
                m_buffer->set_color(j + x, i + y, sprite.color(j, i));
            }
        }
    }
    void display::show() {
        std::array<uint8_t, 4> codes;

        for (int32_t i = 0; i < m_height; i++) {
            for (int32_t j = 0; j < m_width; j++) {
                // TODO: Map color data to available color

                const auto data = m_buffer->data(j, i);
                unicodeToUTF8(data, codes);
                move(i, j);
                for (auto&& code : codes) {
                    if (code != 0x00) {
                        addch(code);
                    }
                }
            }
        }
    }

}  // namespace ace
