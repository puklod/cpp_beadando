#include <iostream>
#include "menu.hpp"

using namespace std;

void Menu::futtat(){
    string input;
    while(mFutAProgram){
        cout << "Mit szeretne csinalni?" << endl;
        cout << "1. Aru bevitel" << endl;
        cout << "2. Aru kereses" << endl;
        cout << "3. Aru torles" << endl;
        cout << "4. Keszletfeltoltes" << endl;
        cout << "5. Kivetel a raktarbol" << endl;
        cout << "6. Arukeszlet kilistazasa" << endl;
        cout << "7. Kilepes" << endl;
        cout << "Valasztas: ";
        cin >> input;

        try{
            stoi(input);
        }catch(const invalid_argument& e){
            cout << "\nCsak szamot lehet megadni! \n" << endl;
            continue;
        }

        int inputAsInt = stoi(input);

        switch(inputAsInt){
        case 1:
            bevitel();
            break;
        case 7:
            mFutAProgram = false;
            break;
        }
    }
}

void Menu::bevitel(){
    string nev, gyarto, arukod;
    int ar, raktarKeszlet ;

    cout << "Aru neve: ";
    cin.ignore();
    getline(cin,nev);
    cout << "Gyarto: ";
    getline(cin,gyarto);
}
