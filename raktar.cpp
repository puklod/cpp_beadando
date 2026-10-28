#include <iostream>
#include <list>
#include <set>
#include <string>
#include "raktar.hpp"
#include "aru.hpp"
#include "ledig.hpp"
#include "darab_aru.hpp"

using namespace std;

void Raktar::hozzaad(const string& aruKod, Aru* aruReferencia){
    mRaktarKeszlet.insert({aruKod,aruReferencia});
}

void Raktar::torol(const string& aruKod){
    Aru* torlendoAru = keres(aruKod);
    if(torlendoAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    mRaktarKeszlet.erase(aruKod);

    delete torlendoAru;
}

Aru* Raktar::keres(const string& aruKod){
    auto it = mRaktarKeszlet.find(aruKod);
    if(it == mRaktarKeszlet.end()){
        return nullptr;
    }
    return it -> second;
}

void Raktar::kivesz(Aru* aru, int mennyiseg){
    if((*aru).raktarKeszlet() < mennyiseg){
        throw runtime_error("Nincs elegendo keszlet.");
    }

    (*aru).raktarKeszlet() -= mennyiseg;
}

void Raktar::kivesz(const string& aruKod, int mennyiseg){
    Aru* hasznaltAru = keres(aruKod);

    if(hasznaltAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    } else if((*hasznaltAru).raktarKeszlet() < mennyiseg){
        throw runtime_error("Nincs elegendo keszlet.");
    } else{
       (*hasznaltAru).raktarKeszlet() -= mennyiseg;
    }
}

void Raktar::feltolt(Aru* aru, int mennyiseg){
    (*aru).raktarKeszlet() += mennyiseg;
}

void Raktar::feltolt(const string& aruKod, int mennyiseg){
    Aru* hasznaltAru = keres(aruKod);

    if(hasznaltAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    (*hasznaltAru).raktarKeszlet() += mennyiseg;
}

string Raktar::aruToString(const string& aruKod){
    Aru* keresettAru = keres(aruKod);

    if(keresettAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    return (*keresettAru).toString();
}

list<string> Raktar::aruLista(){
    list<string> aruLista;
    for(auto& kulcsErtek : mRaktarKeszlet){
        aruLista.push_back((*kulcsErtek.second).toString());
    }

    return aruLista;
}

bool Raktar::megfeleloKodhossz(size_t hossz){
    set<int> elfogadottHosszok = {8,10,13};

    return elfogadottHosszok.count(hossz);
}

int Raktar::meret(){
    return mRaktarKeszlet.size();
}
