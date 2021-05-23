/**
 * @file    unicode.h
 * @author  Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief   Unicode decoder
 * @version 0.1
 * @date 2021-05-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <array>
#include <cstdint>

namespace ace {

    constexpr auto UTF8_BYTE_SIZE = 4;
    void unicodeToUTF8(const uint32_t& code,
                       std::array<uint8_t, UTF8_BYTE_SIZE>& codes);

}  // namespace ace
