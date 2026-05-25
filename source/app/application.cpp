#include "application.h"
#include "ui/menus/main_menu.h"
#include "ui/console.h"

void application::Run()
{
    MainMenu();
    console::clear();
    console::output::print("Closing...", console::COLOR::GREEN);
}
