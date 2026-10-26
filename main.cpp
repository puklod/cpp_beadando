#include <iostream>
#include "aru.hpp"
#include "darab_aru.hpp"
#include "ledig.hpp"
#include "menu.hpp"

using namespace std;

int main()
{
    Raktar raktar;
    for(int i =0; i < 9; i++){
    Ledig* aru = new Ledig("egy","nincs","1234567890",400,20);
    Ledig& adat = *aru;
    cout << &adat << endl;
    }


    Ledig* talatAru = dynamic_cast<Ledig*>(raktar.keres("1234567890"));

    cout << &(*talatAru) << endl;


    /*
    Menu foMenu;
    foMenu.futtat();
    */
    return 0;
}
