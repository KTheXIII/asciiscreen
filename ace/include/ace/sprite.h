/**
 * @file    sprite.h
 * @author  Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief   Container for text sprites. Creates rectangular sprite from text or
 *          manually.
 * @version 0.1
 * @date    2021-05-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <cstdint>

namespace ace {

    class sprite {
       public:
        sprite(const int32_t& width, const int32_t& height);
        sprite(const int32_t& width, const int32_t& height,
               const wchar_t* rawsprite);
        sprite(const int32_t& width, const int32_t& height,
               const char* rawsprite);
        sprite(const wchar_t* rawsprite);
        sprite(const char* rawsprite);
        ~sprite();

        int32_t width() const { return m_width; }
        int32_t height() const { return m_height; }

        uint32_t data(const int32_t& x, int32_t& y) const;
        uint32_t color(const int32_t& x, int32_t& y) const;
        void set_data(const int32_t& x, const int32_t& y, const uint32_t& data);
        void set_color(const int32_t& x, const int32_t& y,
                       const uint32_t& color);

       private:
        int32_t m_width, m_height;
        uint32_t* m_buffer;
        uint32_t* m_color;
    };

}  // namespace ace
