#include <iostream>
#include <list>
#include <string>
#include "raktar.hpp"
#include "aru.hpp"

using namespace std;

void Raktar::hozzaad(Aru* aru){

    mAruLista.push_back(aru);
}

Aru* Raktar::keres(string aruKod){
    Aru* keresettAru;
    for(Aru* aru: mAruLista){
        if((*aru).arukod() == aruKod){
            keresettAru = aru;
        }
    }

    return keresettAru;
}
