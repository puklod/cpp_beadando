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
    double mennyisegKilo = Aru::raktarKeszlet()/1000.0;
    double ertekKilo = mennyisegKilo * Aru::ar();

    return Aru::toString() +
    ", Egysegar: " + to_string(Aru::ar()) + " Ft./kg" +
    ", Egyedi kod: " + Aru::aruKod() +
    ", Raktarkeszlet: " + to_string(Aru::raktarKeszlet()) + "g" +
    " (" + to_string(mennyisegKilo) + "kg)" +
    ", Keszletertek: " + to_string(ertekKilo) + "Ft.";
}
