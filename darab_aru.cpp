#include <iostream>
#include <string>
#include "aru.hpp"
#include "darab_aru.hpp"

using namespace std;

DarabAru::DarabAru(string nev, string gyarto, string arukod, int ar, int raktarKeszlet) : Aru(nev, gyarto, arukod, ar, raktarKeszlet){
    if(arukod.length() != 8 && arukod.length() != 13){
        throw invalid_argument("Csak EAN8 vagy EAN13 vonalkod elfogadott");
    }
}

string DarabAru::toString(){
    return Aru::toString() +
    ", Darabar: " + to_string(Aru::ar()) +
    ", Vonalkod: " + Aru::arukod() +
    (Aru::arukod().length() == 8?" (EAN8)":" (EAN13)") +
    ", Raktarkeszlet: " + to_string(Aru::raktarKeszlet()) + " db.";
}
