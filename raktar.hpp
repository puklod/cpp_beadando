#ifndef _RAKTAR_HPP_
#define _RAKTAR_HPP_
#include <list>
#include <memory>
#include <string>
#include "aru.hpp"

using namespace std;

class Raktar{
public:
    void hozzaad(Aru* aru);
    void kivesz(string aruKod, int mennyiseg);
    Aru* keres(string aruKod);
private:
    list<Aru*> mAruLista;
};

#endif // _RAKTAR_HPP_
