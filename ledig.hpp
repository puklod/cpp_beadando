#ifndef _LEDIG_HPP_
#define _LEDIG_HPP_

#include "aru.hpp"

using namespace std;

class Ledig : public Aru{
public:
    Ledig(string nev, string gyarto, string aruKod, int ar, int raktarKeszlet);
    string toString() override;
};
#endif // _LEDIG_HPP_
