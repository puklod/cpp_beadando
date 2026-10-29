#include <iostream>
#include <string>
#include "aru.hpp"

using namespace std;

Aru::Aru(string nev, string gyarto, string arukod, int ar, int raktarKeszlet): mNev(nev), mGyarto(gyarto), mArukod(arukod), mAr(ar), mRaktarKeszlet(raktarKeszlet){
    for(const char& karakter : arukod){
        if(!isdigit(karakter)){
            throw invalid_argument("Az arukod csak szamokat tartalmazhat. ");
        }
    }
}

string Aru::nev() {return mNev;}
string Aru::gyarto() {return mGyarto;}
string Aru::aruKod() {return mArukod;}
int Aru::ar() {return mAr;}
int& Aru::raktarKeszlet() {return mRaktarKeszlet;}

string Aru::toString(){
    return "Nev: " + mNev + ", Gyarto: " + mGyarto;
}
