#include "sprite.h"

#include <cwchar>

namespace ace {

    sprite::sprite(const int32_t& width, const int32_t& height)
        : m_width(width), m_height(height) {
        m_buffer = new uint32_t[m_width * m_height];
        m_color = new uint32_t[m_width * m_height];
    }

    sprite::sprite(const int32_t& width, const int32_t& height,
                   const wchar_t* rawsprite)
        : sprite(width, height) {
        for (int32_t i = 0; i < m_height; i++) {
            for (int32_t j = 0; j < m_width; j++) {
                set_data(j, i, rawsprite[i * m_width + j]);
            }
        }
    }

    sprite::sprite(const wchar_t* rawsprite) {
        const int32_t length = wcslen(rawsprite);
        int32_t row = 0;
        int32_t col = 0;
        int32_t max_col = 0;

        for (int32_t i = 0; i < length; i++) {
            col++;
            if (rawsprite[i] == L'\n') {
                if (col > max_col) max_col = col;
                col = 0;
                row++;
            }
        }
        m_width = max_col;
        m_height = row;
        row = col = 0;

        m_buffer = new uint32_t[m_width * m_height];
        m_color = new uint32_t[m_width * m_height];

        for (int32_t i = 0; i < length; i++) {
            set_data(col, row, rawsprite[i]);
            col++;
            if (rawsprite[i] == L'\n') {
                col = 0;
                row++;
            }
        }
    }

    sprite::~sprite() {
        delete[] m_buffer;
        delete[] m_color;
    }

    uint32_t sprite::data(const int32_t& x, int32_t& y) const {
        if (x > -1 && x < m_width && y > -1 && y < m_height)
            return m_buffer[y * m_width + x];
        else
            return 0;
    }
    uint32_t sprite::color(const int32_t& x, int32_t& y) const {
        if (x > -1 && x < m_width && y > -1 && y < m_height)
            return m_color[y * m_width + x];
        else
            return 0xFF00FF;
    }
    void sprite::set_data(const int32_t& x, const int32_t& y,
                          const uint32_t& data) {
        if (x > -1 && x < m_width && y > -1 && y < m_height)
            m_buffer[y * m_width + x] = data;
    }
    void sprite::set_color(const int32_t& x, const int32_t& y,
                           const uint32_t& color) {
        if (x > -1 && x < m_width && y > -1 && y < m_height)
            m_color[y * m_width + x] = color;
    }

}  // namespace ace
