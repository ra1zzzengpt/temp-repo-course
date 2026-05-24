#include "main_menu.h"
#include "matrix_menu.h"
#include "ui/console.h"
#include "tests/tests.h"
#include <string>

void MainMenu()
{
    console::clear();
    bool running = true;
    while (running)
    {
        console::output::print("\n╔══════════════════════════════╗");
        console::output::print("║     SORTING VISUALIZER       ║");
        console::output::print("╠══════════════════════════════╣");
        console::output::print("║  1. Matrix Operations        ║");
        console::output::print("║  2. Run Tests                ║");
        console::output::print("║  3. Exit                     ║");
        console::output::print("╚══════════════════════════════╝");

        switch (console::input::SafeScanUint32_t("Enter your choice: "))
        {
            case static_cast<uint32_t>(MAIN_MENU::MATRIX):
                MatrixMenu();
                break;
            case static_cast<uint32_t>(MAIN_MENU::TESTS):
                console::clear();
                console::output::print("Running tests...", console::COLOR::YELLOW);
                tests::RunAll();
                console::output::print("\nPress Enter to continue...", console::COLOR::WHITE, "");
                { std::string s; std::getline(std::cin, s); }
                console::clear();
                break;
            case static_cast<uint32_t>(MAIN_MENU::EXIT):
                running = false;
                console::clear();
                break;
            default:
                console::clear();
                console::output::print("[Error]: enter 1-3", console::COLOR::RED);
                break;
        }
    }
}
