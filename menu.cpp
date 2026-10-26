#include <iostream>
#include "menu.hpp"

using namespace std;

void Menu::futtat(){
    string input;
    while(mFutAProgram){
        cout << "Mit szeretne csinalni?" << endl;
        cout << "1. Darabaru bevitele" << endl;
        cout << "2. Omlesztett aru bevitele" << endl;
        cout << "3. Kilepes" << endl;
        cout << "Valasztas: ";
        cin >> input;

        try{
        stoi(input);
        }catch(const invalid_argument& e){
            cout << "Csak szamot lehet megadni!" << endl;
        }

        if(stoi(input) == 3){
            mFutAProgram = false;
        }
    }
}
