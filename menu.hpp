#ifndef _MENU_HPP_
#define _MENU_HPP_
#include "raktar.hpp"

class Menu{
public:
    void futtat();
    void bevitel();
    void kereses();
    void feltoltes();
    void kivetel();
private:
    bool mFutAProgram = true;
    Raktar mRaktar;
};

#endif // _MENU_HPP_
