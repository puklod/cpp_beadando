#include <iostream>
#include <fstream>
#include <set>
#include "menu.hpp"
#include "ledig.hpp"
#include "darab_aru.hpp"
#include "raktar.hpp"

using namespace std;

void Menu::futtat(){
    char valasztas;
    string input;
    while(mFutAProgram){
        // Kiírjuk a választási lehetõségeket
        cout << "Mit szeretne csinalni?" << endl;
        cout << "1. Aru bevitel" << endl;
        cout << "2. Aru kereses" << endl;
        cout << "3. Aru torlese a raktarbol" << endl;
        cout << "4. Keszletfeltoltes" << endl;
        cout << "5. Keszletkivetel a raktarbol" << endl;
        cout << "6. Arukeszlet kilistazasa" << endl;
        cout << "7. Konzol torlese" << endl;
        cout << "q. Kilepes" << endl;

        // Két opcionális lehetõség következik
        // Ha már van kimentett raktár, betölthetjük
        if(letizikRaktarFajl("raktar.txt")){
            cout << "t. Korabbi raktar betoltese (jelenlegit felulirva)" << endl;
        }

        // Ha raktunk elemet a jelenlegi raktárba, a raktár menthetõ fájlba
        if(mRaktar.meret() > 0){
            cout << "m. Jelenlegi raktar kimentese faljba (korabbit felulirva)" << endl;
        }

        cout << "\nValasztas: ";

        // Volt olyan része a kódnak, ahol a cin nem volt kézenfekvõ, így végül mindenhol getline-t használok
        getline(cin,input);

        // Mivel a választható opciók miatt nem volt szép a csak számos megoldás, bekerültek betû opciók is
        // A beérkezõ választ char típusban tárolom, így tudom validálni, hogy ne legyen átadva rossz edermény
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
            // Mivel a fõ logika a Raktar törlési logikáját használja, így ezt nem szerveztem ki külön Menü funkciónak
            // Bekérjük a törlendõ elemet, meghívjuk a törlést.
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
            // Csak egy sima ciklussal bejárjuk a raktár egyik getterét.
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
            /* Ez a kódsor törli a konzolt. Elõször a system meghívását használtam, de jobban utánanézve,
            az windows specifikus hívás lett volna. Ez ha jól olvastam, univerzális. A mûködése ha jól értem annyi,
            hogy a kurzort elviszi a konzol bal felsõ sarkába. */
            cout << "\033[2J\033[1;1H";
            break;
        case 'q':
            // A program leállításához elég csak a menü privát változóját false-ra állítani, ezzel megtörve a ciklust
            mFutAProgram = false;
            break;
        case 't':
            try{
            // Betöltés elõtt kiürítjük a jelenlegi raktárat, hogy ne legyen összeakadás
            mRaktar.pucol();
            mRaktar.betoltesFajlbol("raktar.txt");
            } catch (const exception& e){
                cout << e.what() << endl;
            }
            break;
        case 'm':
            try{
            mRaktar.fajlbaMentes("raktar.txt");
            } catch (const exception& e){
                cout << e.what() << endl;
            }
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

    // Hogy kényelmesebb legyen a használat, addig kérjük be az adatokat, amíg nem lesz megfelelõ a bemenet.
    while(!megfeleloErtek){
        cout << "Arukod: ";
        getline(cin,input);
        try{
            // Három féle validáció
            if(!csakSzamString(input)){
                throw invalid_argument("Az arukod csak szamokat tartalmazhat. ");
            }
            if(!megfeleloKodhossz(input.length())){
                throw invalid_argument("Nem megfelelo kodhossz. ");
            }
            if(mRaktar.keres(input) != nullptr){
                throw invalid_argument("Ilyen kod mar letezik. ");
            }

            // Ha nincs baj a bemenettel, kimenthetjük a változóba
            arukod = input;

            // kiléphetünk a ciklusból
            megfeleloErtek = true;
        } catch(invalid_argument& e){
            cout << e.what();

            // Ennél az egy bemenetnél beraktam egy újrapróbálási lehetõséget
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

    // A következõ két értéknek nincs megkötése
    cout << "Aru neve: ";
    getline(cin,nev);
    cout << "Gyarto: ";
    getline(cin,gyarto);

    // Újabb validációs ciklus
    megfeleloErtek = false;
    while(!megfeleloErtek){

        // Mivel nem kértem be elõre a típust, a kód alapján dõl el, mit kell kiírni
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
            // csak intekkel operálunk, ezért intre konvertálunk
            ar = stoi(input);
            megfeleloErtek = true;
        } catch(const invalid_argument& e){
            cout << e.what() << endl;
        } catch(const out_of_range& e){
            // Ezt a hibát elméletben csak a stoi dobhatja, ezért itt nem az alapértelmezett hibaüzenet jelenik meg.
            cout << "Tul nagy szam." <<endl;
        }
    }

    // Újabb validációs ciklus
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

    // Ha bekértem volna elõre a típust, nem kéne pointerekkel dolgoznom. Mivel ezt nem tettem, így mindenhol Árupointerekkel dolgozom.
    Aru* aruCikk;

    // Kód alapján eldöntjük, milyen típust kell létrehoznunk
    if(arukod.length() == 10){
        aruCikk = new Ledig(nev,gyarto,arukod,ar,raktarKeszlet);
    } else {
        aruCikk = new DarabAru(nev,gyarto,arukod,ar,raktarKeszlet);
    }

    // A korábbi validációknak köszönhetõen, itt már csak jó érték kerülhet a raktárba
    mRaktar.hozzaad(arukod,aruCikk);

    // Visszajelzés, mi került a raktárba
    cout << (*aruCikk).toString() + " hozzadva.\n" << endl;
}

// A raktár keresõfüggvényét használjuk. Utólag megnézve, ez sem olyan bonyolult, hogy feltétlenül ki kellett volna szerveznem.
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

    // Kód alapján megkeressük az árut. Ha nincs találat, kilépünk.
    cout << "Feltoltendo arucikk kodja: ";
    getline(cin,aruKod);
    Aru* bekertAru = mRaktar.keres(aruKod);
    if(bekertAru == nullptr){
        cout << "Nincs ilyen aru. \n" << endl;
        return;
    }

    // Inputvalidációs blokk
    bool megfeleloInput = false;
    while(!megfeleloInput){
        try{
            cout << "Feltoltendo mennyiseg: ";
            getline(cin,input);
            if(!csakSzamString(input)){
                throw invalid_argument("A mennyiseg csak szamot tartalmazhat.");
            }

            mennyiseg = stoi(input);

            // Idáig eljutva megpróbáhatjuk feltölteni a raktárat.
            mRaktar.feltolt(bekertAru,mennyiseg);
            megfeleloInput = true;
        } catch(const invalid_argument& e){
            cout << e.what() << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam.\n" << endl;
        } catch(const runtime_error& e){
            cout << e.what() << endl;
        }
    }

    // Visszajelzés a felhasználónak
    cout << "\n" << mennyiseg << " hozza lett adva a " << aruKod << " kodu termekhez." << endl;
    // A pointerek használata miatt csak típusellenõrzéssel tudjuk eldönteni, mi legyen a mértékegység. Darabárunak darab, ömlesztettnek gramm.
    cout << "Az uj mennyiseg: " << (*bekertAru).raktarkeszlet() << (*bekertAru).mertekegyseg() << "\n" <<  endl;
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

    // Egyszerûbb, ha a felhasználó látja, mekkora készletbõl választhat
    cout << "A jelenlegi mennyiseg: " << (*bekertAru).raktarkeszlet() << (*bekertAru).mertekegyseg() << "\n" << endl;

    // Validációs ciklus
    bool megfeleloInput = false;
    while(!megfeleloInput){
        try{
            cout << "Mennyit szeretnenk kivenni: ";
            getline(cin,input);
            if(!csakSzamString(input)){
                throw invalid_argument("A mennyiseg csak szamot tartalmazhat.");
            }
            mennyiseg = stoi(input);

            // Idáig eljutva megpróbálhatjuk apasztani a raktárat.
            mRaktar.kivesz(bekertAru,mennyiseg);
            megfeleloInput = true;
        } catch(const invalid_argument& e){
                cout << e.what() << endl;
        } catch(const out_of_range& e){
            cout << "Tul nagy szam.\n" << endl;
        } catch(const runtime_error& e){
            cout << e.what() << endl;
        }
    }

    // Visszajelzés a felhasználónak
    cout << "\n" << mennyiseg << " ki lett veve a " << aruKod << " kodu termekbol." << endl;
    cout << "Az uj mennyiseg: " << (*bekertAru).raktarkeszlet() << (*bekertAru).mertekegyseg() << "\n" << endl;
}

// Egyszerű segédfüggvény, ami ellenõrzi, hogy van-e betû az átadott szövegben. A logika ugyanaz, mint az árú konstruktorában.
bool Menu::csakSzamString(const string& vizsgaltSzoveg){
    for(const char& karakter : vizsgaltSzoveg){
        if(!isdigit(karakter)){
            return false;
        }
    }

    return true;
}


// Egyszerű segédfüggvény, eredetileg a raktárban volt. Utólag úgy látom, jobb helyen van itt.
bool Menu::megfeleloKodhossz(size_t hossz){
    set<int> elfogadottHosszok = {8,10,13};

    return elfogadottHosszok.count(hossz);
}

// Egyszerû segédfüggvény. Elméletileg mehetett volna a futtató logikába is, valmiért természetesebbnek tûnit kiszervezve.
bool Menu::letizikRaktarFajl(const string& fileNev){
    ifstream file(fileNev);

    return file.is_open();
}
