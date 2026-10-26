#include <iostream>
#include <string>
#include "aru.hpp"

using namespace std;

Aru::Aru(string nev, string gyarto, string arukod, int ar, int raktarKeszlet): mNev(nev), mGyarto(gyarto), mArukod(arukod), mAr(ar), mRaktarKeszlet(raktarKeszlet){
try{
    stoi(arukod);
} catch (const invalid_argument& e){
    cout << ("Az arukod csak szamot tartalmazhat!") << endl;
}
}

string Aru::aruKod() {return mArukod;}
int Aru::ar() {return mAr;}
int& Aru::raktarKeszlet() {return mRaktarKeszlet;}

string Aru::toString(){
    return "Nev: " + mNev + ", Gyarto: " + mGyarto;
}
