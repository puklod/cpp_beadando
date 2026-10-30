#include <iostream>
#include "aru.hpp"
#include "darab_aru.hpp"
#include "ledig.hpp"
#include "menu.hpp"

using namespace std;

int main()
{
    // A program csak egy menüelemet készít és azt el is indítja. Amikor a futtatás leáll, a program is megállhat.
    Menu foMenu;
    foMenu.futtat();
    return 0;
}
