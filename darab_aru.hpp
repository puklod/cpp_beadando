#ifndef _DARAB_ARU_HPP_
#define _DARAB_ARU_HPP_

#include <string>
#include "aru.hpp"

class DarabAru : public Aru {
public:
    DarabAru(const string& nev, const string& gyarto, const string& aruKod, int ar, int raktarKeszlet);
    string mertekegyseg() const override;
    string toString() const override;
private:
    void setKod(string kod);
};

#endif // _DARAB_ARU_HPP_
