#ifndef _LEDIG_HPP_
#define _LEDIG_HPP_

#include "aru.hpp"

using namespace std;

class Ledig : public Aru{
public:
    Ledig(const string& nev, const string& gyarto, const string& aruKod, int ar, int raktarKeszlet);
    string mertekegyseg() const override;
    string toString() const override;
};
#endif // _LEDIG_HPP_
