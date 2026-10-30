#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include "raktar.hpp"
#include "aru.hpp"
#include "ledig.hpp"
#include "darab_aru.hpp"

using namespace std;

int Raktar::meret() const{
    return mRaktarKeszlet.size();
}

// Ezt korábban használatam, az éles programban nincs használva
string Raktar::aruToString(const string& aruKod) const{
    Aru* keresettAru = keres(aruKod);

    if(keresettAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    return (*keresettAru).toString();
}

Aru* Raktar::keres(const string& aruKod) const{
    auto it = mRaktarKeszlet.find(aruKod);

    // Ha a map végére értünk és nincs találat, akkor biztos nincs ilyen elem
    if(it == mRaktarKeszlet.end()){
        return nullptr;
    }

    // A map szerkezet string,árupointer.
    return it -> second;
}

list<string> Raktar::aruLista() const{
    list<string> aruLista;

    // Bejárjuk a map-et és beteszzük a visszatérõ listába a szöveges megfelelõket.
    // Talán mehetne a menü objektumba is, hogy ne kelljen mégegyszer bejárni a listát a kiíratáshoz.
    // Itt tûnik természetesebbnek.
    for(auto& kulcsErtek : mRaktarKeszlet){
        aruLista.push_back((*kulcsErtek.second).toString());
    }

    return aruLista;
}

void Raktar::hozzaad(const string& aruKod, Aru* aruPointer){
    mRaktarKeszlet.insert({aruKod,aruPointer});
}

void Raktar::torol(const string& aruKod){
    Aru* torlendoAru = keres(aruKod);
    if(torlendoAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    mRaktarKeszlet.erase(aruKod);

    delete torlendoAru;
}

void Raktar::kivesz(Aru* aru, int mennyiseg){
    if(aru == nullptr){
        throw runtime_error ("Nem letezo aru!");
    } else if((*aru).raktarkeszlet() < mennyiseg){ // Validáljuk, hogy ki lehet-e venni.
        throw runtime_error("Nincs elegendo keszlet, nem tortent valtozas.\n");
    }

    (*aru).kivesz(mennyiseg);
}


// Ezt a verziót végül nem használtam a gyakorlatban. Ha már megírtam korábban, meghagytam.
void Raktar::kivesz(const string& aruKod, int mennyiseg){
    Aru* aru = keres(aruKod);

    kivesz(aru,mennyiseg);
}

void Raktar::feltolt(Aru* aru, int mennyiseg){
    if(aru == nullptr){
        throw runtime_error ("Nem letezo aru!");
    } else if (INT_MAX - (*aru).raktarkeszlet() - mennyiseg < 0){ // Validálunk, hogy ne legyen túlcsordulás.
        throw runtime_error ("Ezzel a szammal tullepnenk a raktarkapacitast.");
    }

    (*aru).hozzaad(mennyiseg);
}

// Szintén nincs használva
void Raktar::feltolt(const string& aruKod, int mennyiseg){
    Aru* aru = keres(aruKod);

    feltolt(aru,mennyiseg);
}

void Raktar::fajlbaMentes(const string& fileNev){
    ofstream file(fileNev);
    // Ha nem létezik a fájl, kilépünk.
    if(!file.is_open()) return;

    // Egyszerûen végigmegyünk a map-en, és egy tetszõleges fájlba kiírjuk az adatokat.
    for(auto& kulcsErtek : mRaktarKeszlet){
        Aru* aru = (kulcsErtek.second);

        if(typeid(*aru) == typeid(Ledig)){
            file << "Ledig;";
        } else {
            file << "Darab;";
        }

        file << (*aru).nev() << ";" << (*aru).gyarto() << ";" << (*aru).arukod() << ";" << (*aru).ar() << ";" << (*aru).raktarkeszlet() << "\n";

    }
}

void Raktar::betoltesFajlbol(const string& fileNev){
    ifstream file(fileNev);
    if(!file.is_open()) return;

    string sor;

    // Elõször elkezdjük soronként olvasni a fájlt
    while(getline(file,sor)){
        vector<string> adatok;
        stringstream ss(sor);

        string adat;

        // A stringstream segítségével végigmegyünk a soron, a ;-nél tördeljük az adatokat
        while(getline(ss,adat,';')){
            // Minden adatot berakunk a vektorba
            adatok.push_back(adat);
        }

        Aru* aru;

        // Mivel tudjuk, hogy az elsõ adat mindig az árú kódja lesz, így az alapján el tudjuk dönteni, milyen objektumot kell létrehoznunk
        if(adatok[0] == "Ledig"){
            aru = new Ledig(adatok[1], adatok[2], adatok[3], stoi(adatok[4]), stoi(adatok[5]));
        } else{
            aru = new DarabAru(adatok[1], adatok[2], adatok[3], stoi(adatok[4]), stoi(adatok[5]));
        }

        // A létrehozott árukód,árupointer párost berakjuk a map-be
        mRaktarKeszlet.insert({(*aru).arukod(),aru});
    }
}

void Raktar::pucol(){
    // Végigmegyünk a map-en, és az összes tárolt pointerbõl töröljük az objektumokat
    for(auto& kulcsErtek : mRaktarKeszlet){
        delete (kulcsErtek.second);
    }

    // Végül a map-et is ürítjük
    mRaktarKeszlet.clear();
}

Raktar::~Raktar(){
    pucol();
}
