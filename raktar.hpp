#ifndef _RAKTAR_HPP_
#define _RAKTAR_HPP_
#include <unordered_map>
#include <string>
#include <list>
#include "aru.hpp"

using namespace std;

class Raktar{
public:
    void hozzaad(const string& aruKod, Aru* aruReferencia);
    void torol(const string& aruKod);
    void kivesz(Aru* aru, int mennyiseg);
    void kivesz(const string& aruKod, int mennyiseg);
    void feltolt(Aru* aru, int mennyiseg);
    void feltolt(const string& aruKod, int mennyiseg);
    Aru* keres(const string& aruKod);
    string aruToString(const string& aruKod);
    list<string> aruLista();
    bool megfeleloKodhossz(size_t hossz);
    int meret();
private:
    unordered_map<string,Aru*> mRaktarKeszlet;
};

#endif // _RAKTAR_HPP_
