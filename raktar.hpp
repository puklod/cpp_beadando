#ifndef _RAKTAR_HPP_
#define _RAKTAR_HPP_
#include <unordered_map>
#include <string>
#include <list>
#include "aru.hpp"

using namespace std;

class Raktar{
public:
    // Getterek
    int meret() const;
    Aru* keres(const string& aruKod) const;
    string aruToString(const string& aruKod) const;
    list<string> aruLista() const;

    // Setterek
    void hozzaad(const string& aruKod, Aru* aruReferencia);
    void torol(const string& aruKod);
    void kivesz(Aru* aru, int mennyiseg);
    void kivesz(const string& aruKod, int mennyiseg);
    void feltolt(Aru* aru, int mennyiseg);
    void feltolt(const string& aruKod, int mennyiseg);

    // Két funkció a mentéshez és betöltéshez
    void fajlbaMentes(const string& fileNev);
    void betoltesFajlbol(const string& fileNev);

    // A pucol eredetileg destruktor logika volt, de végül érdemesebb volt kiemelni
    void pucol();
    ~Raktar();
private:
    unordered_map<string,Aru*> mRaktarKeszlet;
};

#endif // _RAKTAR_HPP_
