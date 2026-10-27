#include <iostream>
#include "menu.hpp"
#include "ledig.hpp"
#include "darab_aru.hpp"
#include "raktar.hpp"

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
        case 2:
            cout << "Keresett aru kodja: ";
            cin >> input;
            cout << mRaktar.keres(input);
            break;
        case 6:
            mRaktar.keszletNyomtatas();
            break;
        case 7:
            mFutAProgram = false;
            break;
        }
    }
}

void Menu::bevitel(){
    string input,arukod,nev,gyarto;
    int kodHossz, ar, raktarKeszlet;
    bool megfeleloErtek = false;

    while(!megfeleloErtek){
        cout << "Arukod: ";
        cin >> arukod;
        try{
            if(!mRaktar.megfeleloKodhossz(arukod.length())){
                throw invalid_argument("Nem megfelelo kodhossz!\n");
            }
            if(mRaktar.keres(arukod) != nullptr){
                throw invalid_argument("Ilyen kod mar letezik!");
            }
            kodHossz = stoi(arukod);
            megfeleloErtek = true;
        } catch(invalid_argument& e){
            if(string(e.what()) == "stoi"){
                cout << "A kod csak szamokat tartalmazhat!\n";
            }else {
                cout << e.what();
            }

            cout << "Ujraprobalja?" << endl;
            cout << "i/n: ";
            cin.ignore();
            if(cin.get() == 'i'){
                continue;
            } else {
                system("cls");
                return;
            }
        }
    }


    cout << "Aru neve: ";
    cin.ignore();
    getline(cin,nev);
    cout << "Gyarto: ";
    getline(cin,gyarto);

    megfeleloErtek = false;
    while(!megfeleloErtek){

        if(kodHossz == 10){
            cout << "Kilos ar: ";
        } else {
            cout << "Darabar: ";
        }


        try{
            cin >> input;
            ar = stoi(input);
            megfeleloErtek = true;
        } catch(invalid_argument& e){
            cout << "Az ar csak szamot tartalmazhat!" << endl;
        }
    }

    megfeleloErtek = false;
    while(!megfeleloErtek){
        if(kodHossz == 10){
            cout << "Kezdo arukeszlet(g): ";
        } else {
            cout << "Kezdo arumennyiseg(db): ";
        }

        try{
            cin >> input;
            raktarKeszlet = stoi(input);
            megfeleloErtek = true;
        } catch(invalid_argument& e){
            cout << "Az ar csak szamot tartalmazhat!" << endl;
        }
    }

    Aru* aruCikk;
    if(kodHossz == 10){
        aruCikk = new Ledig(nev,gyarto,arukod,ar,raktarKeszlet);
    } else {
        aruCikk = new DarabAru(nev,gyarto,arukod,ar,raktarKeszlet);
    }

    mRaktar.hozzaad(arukod,aruCikk);
}
