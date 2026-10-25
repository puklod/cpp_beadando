#ifndef _DARAB_ARU_HPP_
#define _DARAB_ARU_HPP_

#include <string>
#include "aru.hpp"

class DarabAru : public Aru {
public:
    DarabAru(string nev, string gyarto, string arukod, int ar, int raktarKeszlet);
    string toString() override;
private:
    void setKod(string kod);
};

#endif // _DARAB_ARU_HPP_
