#include <iostream>
#include <string>
#include "aru.hpp"

using namespace std;

Aru::Aru(const string& nev, const string& gyarto, const string& arukod, int ar, int raktarkeszlet): mNev(nev), mGyarto(gyarto), mArukod(arukod), mAr(ar), mRaktarkeszlet(raktarkeszlet){
    // Ha az árukód valamelyik karaktere nem szám, hibát dobunk
    for(const char& karakter : arukod){
        if(!isdigit(karakter)){
            throw invalid_argument("Az arukod csak szamokat tartalmazhat. ");
        }
    }
}

// Getterek definiálása
string Aru::nev() const {return mNev;}
string Aru::gyarto() const {return mGyarto;}
string Aru::arukod() const {return mArukod;}
int Aru::ar() const {return mAr;}
int Aru::raktarkeszlet() const {return mRaktarkeszlet;}

// Két setter definiálása
void Aru::hozzaad(int mennyiseg) {mRaktarkeszlet += mennyiseg;}
void Aru::kivesz(int mennyiseg) {mRaktarkeszlet -= mennyiseg;}


string Aru::toString() const{
    return "Nev: " + mNev + ", Gyarto: " + mGyarto;
}
