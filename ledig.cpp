#include <iostream>
#include <string>
#include "ledig.hpp"

using namespace std;

Ledig::Ledig(string nev, string gyarto, string arukod, int ar, int raktarKeszlet) : Aru(nev,gyarto,arukod,ar,raktarKeszlet){
    if(arukod.length() != 10){
        throw invalid_argument("A ledig termeknel kotelezo 10 hosszu kodot adni!");
    }
}

string Ledig::toString(){
    return Aru::toString() +
    ", Egysegar: " + to_string(Aru::ar()) + " g" +
    ", Egyedi kod: " + Aru::arukod() +
    ", Raktarkeszlet: " + to_string(Aru::raktarKeszlet()) + " g" +
    " (" + std::to_string((Aru::raktarKeszlet()/1000.0)) + " kg)";
}
