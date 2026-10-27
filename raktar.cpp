#include <iostream>
#include <list>
#include <set>
#include <string>
#include "raktar.hpp"
#include "aru.hpp"
#include "ledig.hpp"
#include "darab_aru.hpp"

using namespace std;

void Raktar::hozzaad(string aruKod, Aru* aruReferencia){

    mRaktarKeszlet.insert({aruKod,aruReferencia});

    cout << (*aruReferencia).toString() + " hozzadva.";
}

void Raktar::torol(string aruKod){
    Aru* torlendoAru = keres(aruKod);
    if(torlendoAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    mRaktarKeszlet.erase(aruKod);

    delete torlendoAru;
}

Aru* Raktar::keres(string aruKod){
    return mRaktarKeszlet[aruKod];
}

void Raktar::kivesz(string aruKod, int mennyiseg){
    Aru* hasznaltAru = keres(aruKod);

    if(hasznaltAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    } else if((*hasznaltAru).raktarKeszlet() < mennyiseg){
        throw runtime_error("Nincs elegendo keszlet");
    } else{
       (*hasznaltAru).raktarKeszlet() -= mennyiseg;
    }
}

void Raktar::feltolt(string aruKod, int mennyiseg){
    Aru* hasznaltAru = keres(aruKod);

    if(hasznaltAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    (*hasznaltAru).raktarKeszlet() += mennyiseg;
}

string Raktar::aruToString(string aruKod){
    Aru* keresettAru = keres(aruKod);

    if(keresettAru == nullptr){
      throw runtime_error("Nem letezik ilyen aru!");
    }

    return (*keresettAru).toString();
}

void Raktar::keszletNyomtatas(){
    for(auto& kulcsErtek : mRaktarKeszlet){
        cout << aruToString(kulcsErtek.first) << endl;
    }
}

bool Raktar::megfeleloKodhossz(size_t hossz){
    set<int> elfogadottHosszok = {8,10,13};

    return elfogadottHosszok.count(hossz);
}
