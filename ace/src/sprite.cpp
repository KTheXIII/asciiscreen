#include "sprite.h"

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

    sprite::sprite(const int32_t& width, const int32_t& height,
                   const char* rawsprite)
        : sprite(width, height) {
        for (int32_t i = 0; i < m_height; i++) {
            for (int32_t j = 0; j < m_width; j++) {
                set_data(j, i, rawsprite[i * m_width + j]);
            }
        }
    }

    sprite::sprite(const wchar_t* rawsprite) {
        // TODO: Calculate sprite width and height from text
    }

    sprite::sprite(const char* rawsprite) {
        // TODO: Calculate sprite width and height from text
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
