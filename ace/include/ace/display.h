#pragma once

#include <memory>
#include <cstdint>
#include <string>

#include <ncurses.h>

#include "sprite.h"

namespace ace {

    class display {
       public:
        struct version {
            int32_t MAJOR, MINOR, PATCH;
        };

       public:
        display();
        ~display();

        void set_input_timeout(const int32_t& time = 0);
        void show_cursor(const bool& enable);

        void poll_events();

        void clear();
        void print(const int32_t& x, const int32_t& y,
                   const std::wstring& text);
        void draw(const int32_t& x, const int32_t& y, const sprite& sprite);
        void show();

        int32_t key() { return m_key; }
        int32_t mousex() { return m_mousex; }
        int32_t mousey() { return m_mousey; }
        int32_t width() { return m_width; }
        int32_t height() { return m_height; }

        version& get_version() const { return s_version; }

        static display& get_instance();

       private:
        int32_t m_width, m_height;         // display props
        std::unique_ptr<sprite> m_buffer;  // display buffer
        int32_t m_key;                     // Input character
        int32_t m_mousex, m_mousey;        // Mouse location

       private:
        static display* s_instance;
        static version s_version;

       private:
        WINDOW* m_ncurses;
    };

}  // namespace ace
