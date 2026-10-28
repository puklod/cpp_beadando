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
        cout << "3. Aru torlese a raktarbol" << endl;
        cout << "4. Keszletfeltoltes" << endl;
        cout << "5. Keszletkivetel a raktarbol" << endl;
        cout << "6. Arukeszlet kilistazasa" << endl;
        cout << "7. Konzol torlese" << endl;
        cout << "8. Kilepes" << endl;
        cout << "\nValasztas: ";
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
            kereses();
            break;
        case 3:
            cout << "Torlendo aru kodja: ";
            cin >> input;
            try{
                mRaktar.torol(input);
            } catch (const runtime_error& e){
                cout << string(e.what()) + "\n" << endl;
            }
        case 4:
            feltoltes();
            break;
        case 5:
            kivetel();
            break;
        case 6:
            if(mRaktar.meret() == 0){
                cout << "A raktar jelenleg ures. \n" << endl;
            } else{
                for(const string& aru: mRaktar.aruLista()){
                    cout << aru << endl;
                }
            }
            break;
        case 7:
            cout << "\033[2J\033[1;1H";
            break;
        case 8:
            mFutAProgram = false;
            break;
        }
    }
}

void Menu::bevitel(){
    string input,arukod,nev,gyarto;
    int ar, raktarKeszlet;
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
            stoll(arukod);
            megfeleloErtek = true;
        } catch(invalid_argument& e){
            if(string(e.what()) == "stoll"){
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

        if(arukod.length() == 10){
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
        if(arukod.length() == 10){
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
    if(arukod.length() == 10){
        aruCikk = new Ledig(nev,gyarto,arukod,ar,raktarKeszlet);
    } else {
        aruCikk = new DarabAru(nev,gyarto,arukod,ar,raktarKeszlet);
    }

    mRaktar.hozzaad(arukod,aruCikk);

    cout << (*aruCikk).toString() + " hozzadva.\n" << endl;
}

void Menu::kereses(){
    string input;

    cout << "Keresett aru kodja: ";
    cin >> input;
    Aru* talaltAru = mRaktar.keres(input);
    if(talaltAru == nullptr){
        cout << "Nincs ilyen aru.\n" << endl;
    } else {
        cout << (*talaltAru).toString() + "\n" << endl;
    }
}

void Menu::feltoltes() {

    string aruKod, mennyiseg;
    cout << "Feltoltendo arucikk kodja: ";
    cin >> aruKod;
    Aru* bekertAru = mRaktar.keres(aruKod);
    if(bekertAru == nullptr){
        cout << "Nincs ilyen aru. \n" << endl;
        return;
    }

    bool megfeleloInput = false;
    while(!megfeleloInput){
        try{
            cout << "Feltoltendo mennyiseg: ";
            cin >> mennyiseg;
            stoi(mennyiseg);
            megfeleloInput = true;
        } catch(const invalid_argument& e){
            cout << "A mennyiseg csak szamot tartalmazhat." << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam!";
        }
    }

    mRaktar.feltolt(bekertAru,stoi(mennyiseg));

    cout << "\n" << mennyiseg << " hozza lett adva a " << aruKod << " kodu termekhez." << endl;
    cout << "Az uj mennyiseg: " << (*bekertAru).raktarKeszlet() << ((typeid(*bekertAru) == typeid(DarabAru))?" db.\n":" g.\n") <<  endl;
}

void Menu::kivetel() {
    string aruKod, mennyiseg;
    cout << "Keresett arucikk kodja: ";
    cin >> aruKod;
    Aru* bekertAru = mRaktar.keres(aruKod);
    if(bekertAru == nullptr){
        cout << "Nincs ilyen aru. \n" << endl;
        return;
    }

    cout << "A jelenlegi mennyiseg: " << (*bekertAru).raktarKeszlet() << ((typeid(*bekertAru) == typeid(DarabAru))?" db.\n":" g.\n") << endl;

    bool megfeleloInput = false;
    while(!megfeleloInput){
        try{
            cout << "Mennyit szeretnenk kivenni: ";
            cin >> mennyiseg;
            stoi(mennyiseg);
            megfeleloInput = true;
        } catch(const invalid_argument& e){
            cout << "A mennyiseg csak szamot tartalmazhat." << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam!";
        }
    }

    try{
        mRaktar.kivesz(bekertAru,stoi(mennyiseg));
    } catch(const runtime_error& e){
        cout << e.what() << endl;
    }

    cout << "\n" << mennyiseg << " ki lett veve a " << aruKod << " kodu termekbol." << endl;
    cout << "Az uj mennyiseg: " << (*bekertAru).raktarKeszlet() << ((typeid(*bekertAru) == typeid(DarabAru))?" db.":" g.\n") << endl;
}
