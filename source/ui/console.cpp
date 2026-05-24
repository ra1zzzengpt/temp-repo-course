#include "console.h"

std::string console::ansiColor(const RGB& color)
{
    return "\033[38;2;" +
        std::to_string(color.red)   + ";" +
        std::to_string(color.green) + ";" +
        std::to_string(color.blue)  + "m";
}

void console::clear()
{
    std::cout << "\x1B[3J\x1B[2J\x1B[H";
}

uint32_t console::input::SafeScanUint32_t(const std::string_view prompt)
{
    std::string input;
    uint32_t result{};
    bool success = false;

    while (!success)
    {
        output::print(prompt, COLOR::WHITE, "");
        std::getline(std::cin, input);
        if (input.empty()) continue;

        bool valid = true;
        for (const char c : input)
            if (!std::isdigit(static_cast<unsigned char>(c))) { valid = false; break; }

        if (!valid) { output::print("[Error]: digits only", COLOR::RED); continue; }

        try
        {
            const unsigned long temp = std::stoul(input);
            if (temp > UINT32_MAX) { output::print("[Error]: value too large", COLOR::RED); continue; }
            result = static_cast<uint32_t>(temp);
            success = true;
        }
        catch (...) { output::print("[Error]: invalid number", COLOR::RED); }
    }
    return result;
}
