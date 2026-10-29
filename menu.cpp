#include <iostream>
#include <fstream>
#include "menu.hpp"
#include "ledig.hpp"
#include "darab_aru.hpp"
#include "raktar.hpp"

using namespace std;

void Menu::futtat(){
    char valasztas;
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
        cout << "q. Kilepes" << endl;

        if(letizikRaktarFajl("raktar.txt")){
            cout << "t. Korabbi raktar betoltese (jelenlegit felulirva)" << endl;
        }

        if(mRaktar.meret() > 0){
            cout << "m. Jelenlegi raktar kimentese faljba (korabbit felulirva)" << endl;
        }

        cout << "\nValasztas: ";
        getline(cin,input);

        if(input.length() > 1){
            cout << "Nincs ilyen opcio" << endl;
            continue;
        }

        valasztas = input[0];

        switch(valasztas){
        case '1':
            bevitel();
            break;
        case '2':
            kereses();
            break;
        case '3':
            cout << "Torlendo aru kodja: ";
            getline(cin,input);
            try{
                mRaktar.torol(input);
            } catch (const runtime_error& e){
                cout << string(e.what()) + "\n" << endl;
            }
            break;
        case '4':
            feltoltes();
            break;
        case '5':
            kivetel();
            break;
        case '6':
            if(mRaktar.meret() == 0){
                cout << "A raktar jelenleg ures. \n" << endl;
            } else{
                for(const string& aru: mRaktar.aruLista()){
                    cout << aru << endl;
                }
                cout << "\n" << endl;
            }
            break;
        case '7':
            cout << "\033[2J\033[1;1H";
            break;
        case 'q':
            mFutAProgram = false;
            break;
        case 't':
            mRaktar.pucol();
            mRaktar.betoltesFajlbol("raktar.txt");
            break;
        case 'm':
            mRaktar.fajlbaMentes("raktar.txt");
            break;
        default:
            cout << "Nincs ilyen opcio." << endl;
        }
    }
}

void Menu::bevitel(){
    string input,arukod,nev,gyarto;
    int ar, raktarKeszlet;
    bool megfeleloErtek = false;

    while(!megfeleloErtek){
        cout << "Arukod: ";
        getline(cin,input);
        try{
            if(!csakSzamString(input)){
                throw invalid_argument("Az arukod csak szamokat tartalmazhat. ");
            }
            if(!mRaktar.megfeleloKodhossz(input.length())){
                throw invalid_argument("Nem megfelelo kodhossz. ");
            }
            if(mRaktar.keres(input) != nullptr){
                throw invalid_argument("Ilyen kod mar letezik. ");
            }
            arukod = input;
            megfeleloErtek = true;
        } catch(invalid_argument& e){
            cout << e.what();

            cout << "Ujraprobalja?" << endl;
            cout << "i/n: ";
            getline(cin,input);
            if(input == "i"){
                continue;
            } else {
                return;
            }
        }
    }

    cout << "Aru neve: ";
    getline(cin,nev);
    cout << "Gyarto: ";
    getline(cin,gyarto);

    megfeleloErtek = false;
    while(!megfeleloErtek){

        if(arukod.length() == 10){
            cout << "Kilos ar (Ft.): ";
        } else {
            cout << "Darabar (Ft.): ";
        }

        try{
            getline(cin,input);
            if(!csakSzamString(input)){
                    throw invalid_argument("Az ar csak szamokat tartalmazhat. ");
            }
            ar = stoi(input);
            megfeleloErtek = true;
        } catch(const invalid_argument& e){
            cout << e.what() << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam." <<endl;
        }
    }

    megfeleloErtek = false;
    while(!megfeleloErtek){
        if(arukod.length() == 10){
            cout << "Kezdo arukeszlet(g): ";
        } else {
            cout << "Kezdo arumennyiseg(db.): ";
        }

        try{
            getline(cin,input);
            if(!csakSzamString(input)){
                throw invalid_argument("A raktarkeszlet csak szamokat tartalmazhat. ");
            }

            raktarKeszlet = stoi(input);
            megfeleloErtek = true;
        } catch(const invalid_argument& e){
            cout << e.what() << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam." <<endl;
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
    getline(cin,input);
    Aru* talaltAru = mRaktar.keres(input);
    if(talaltAru == nullptr){
        cout << "Nincs ilyen aru.\n" << endl;
    } else {
        cout << (*talaltAru).toString() + "\n" << endl;
    }
}

void Menu::feltoltes() {

    string input,aruKod;
    int mennyiseg;
    cout << "Feltoltendo arucikk kodja: ";
    getline(cin,aruKod);
    Aru* bekertAru = mRaktar.keres(aruKod);
    if(bekertAru == nullptr){
        cout << "Nincs ilyen aru. \n" << endl;
        return;
    }

    bool megfeleloInput = false;
    while(!megfeleloInput){
        try{
            cout << "Feltoltendo mennyiseg: ";
            getline(cin,input);
            if(!csakSzamString(input)){
                throw invalid_argument("A mennyiseg csak szamot tartalmazhat.");
            }
            mennyiseg = stoi(input);
            if(INT_MAX - mennyiseg - (*bekertAru).raktarKeszlet() < 0){
                throw invalid_argument ("Ezzel a szammal tullepnenk a raktarkapacitast.");
            }
            megfeleloInput = true;
        } catch(const invalid_argument& e){
            cout << e.what() << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam.\n" << endl;
        }
    }

    mRaktar.feltolt(bekertAru,mennyiseg);

    cout << "\n" << mennyiseg << " hozza lett adva a " << aruKod << " kodu termekhez." << endl;
    cout << "Az uj mennyiseg: " << (*bekertAru).raktarKeszlet() << ((typeid(*bekertAru) == typeid(DarabAru))?" db.":" g.") << "\n" <<  endl;
}

void Menu::kivetel() {
    string input,aruKod;
    int mennyiseg;
    cout << "Keresett arucikk kodja: ";
    getline(cin,aruKod);
    Aru* bekertAru = mRaktar.keres(aruKod);
    if(bekertAru == nullptr){
        cout << "Nincs ilyen aru. \n" << endl;
        return;
    }

    cout << "A jelenlegi mennyiseg: " << (*bekertAru).raktarKeszlet() << ((typeid(*bekertAru) == typeid(DarabAru))?" db.":" g.") << "\n" << endl;

    bool megfeleloInput = false;
    while(!megfeleloInput){
        try{
            cout << "Mennyit szeretnenk kivenni: ";
            getline(cin,input);
            if(!csakSzamString(input)){
                throw invalid_argument("A mennyiseg csak szamot tartalmazhat.");
            }
            mennyiseg = stoi(input);
            megfeleloInput = true;
        } catch(const invalid_argument& e){
                cout << e.what() << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam.\n" << endl;
        }
    }

    try{
        mRaktar.kivesz(bekertAru,mennyiseg);
        cout << "\n" << mennyiseg << " ki lett veve a " << aruKod << " kodu termekbol." << endl;
        cout << "Az uj mennyiseg: " << (*bekertAru).raktarKeszlet() << ((typeid(*bekertAru) == typeid(DarabAru))?" db.":" g.") << "\n" << endl;
    } catch(const runtime_error& e){
        cout << e.what() << endl;
    }
}

bool Menu::csakSzamString(const string& vizsgaltSzoveg){
    for(const char& karakter : vizsgaltSzoveg){
        if(!isdigit(karakter)){
            return false;
        }
    }

    return true;
}

bool Menu::letizikRaktarFajl(const string& fileNev){
    ifstream file(fileNev);

    return file.is_open();
}
