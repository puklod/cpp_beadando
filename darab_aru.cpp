#include <iostream>
#include <string>
#include "aru.hpp"
#include "darab_aru.hpp"

using namespace std;

DarabAru::DarabAru(const string& nev, const string& gyarto, const string& arukod, int ar, int raktarKeszlet) : Aru(nev, gyarto, arukod, ar, raktarKeszlet){
    // Darabárunak csak 8 vagy 13 hosszú kódja lehet
    if(arukod.length() != 8 && arukod.length() != 13){
        throw invalid_argument("Csak EAN8 vagy EAN13 vonalkod elfogadott");
    }
}

string DarabAru::mertekegyseg() const {
    return "db.";
}

string DarabAru::toString() const{
    return Aru::toString() +
    ", Darabar: " + to_string(Aru::ar()) +
    ", Vonalkod: " + Aru::arukod() +
    (Aru::arukod().length() == 8?" (EAN8)":" (EAN13)") + // Ha nyolc karatkert tartalmaz a kód, akkor EAN8, egyéb esetben EAN13
    ", Raktarkeszlet: " + to_string(Aru::raktarkeszlet()) + " db." +
    ", Keszletertek: " + to_string(Aru::raktarkeszlet() * Aru::ar()) + " Ft.";
}
