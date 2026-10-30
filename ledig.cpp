#include <iostream>
#include <string>
#include "ledig.hpp"

using namespace std;

Ledig::Ledig(const string& nev, const string& gyarto, const string& arukod, int ar, int raktarKeszlet) : Aru(nev,gyarto,arukod,ar,raktarKeszlet){
    // Ömlesztett árú csak 10 hosszú kódot tartalmazhat
    if(arukod.length() != 10){
        throw invalid_argument("A ledig termeknel kotelezo 10 hosszu kodot adni!");
    }
}

string Ledig::mertekegyseg() const {
    return "g.";
}

string Ledig::toString() const{
    double mennyisegKilo = Aru::raktarkeszlet()/1000.0;
    double ertekKilo = mennyisegKilo * Aru::ar();

    return Aru::toString() +
    ", Egysegar: " + to_string(Aru::ar()) + " Ft./kg" +
    ", Egyedi kod: " + Aru::arukod() +
    ", Raktarkeszlet: " + to_string(Aru::raktarkeszlet()) + "g" +
    " (" + to_string(mennyisegKilo) + "kg)" +
    ", Keszletertek: " + to_string(ertekKilo) + "Ft.";
}
