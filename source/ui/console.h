#pragma once
#include <iostream>
#include <cstdint>
#include <string>

namespace console
{
    struct RGB { uint8_t red, green, blue; };

    std::string ansiColor(const RGB& color);
    inline std::string ansiReset() { return "\033[0m"; }

    namespace COLOR
    {
        inline constexpr RGB WHITE  {255, 255, 255};
        inline constexpr RGB RED    {255,   0,   0};
        inline constexpr RGB GREEN  {  0, 255,   0};
        inline constexpr RGB YELLOW {255, 255,   0};
    }

    void clear();

    namespace output
    {
        template <typename T, typename N = std::string_view>
        void print(const T& value, const RGB& color = COLOR::WHITE, const N& sep = "\n")
        {
            std::cout << ansiColor(color) << value << ansiReset() << sep;
        }
    }

    namespace input
    {
        uint32_t SafeScanUint32_t(std::string_view prompt);
    }
}
