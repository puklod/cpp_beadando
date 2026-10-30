#ifndef _MENU_HPP_
#define _MENU_HPP_
#include "raktar.hpp"

class Menu{
public:
    // Mûködéshez szükséges funkciók
    void futtat();
    void bevitel();
    void kereses();
    void feltoltes();
    void kivetel();

    // Validáló függvények
    bool csakSzamString(const string& vizsgaltSzoveg);
    bool megfeleloKodhossz(size_t hossz);
    bool letizikRaktarFajl(const string& fileNev);

private:
    // Ez mehetett volna a futtat függvénybe is, itt most valamiért jobban tetszik
    bool mFutAProgram = true;

    // Minden menü saját raktárobjektummal dolgozik
    Raktar mRaktar;
};

#endif // _MENU_HPP_
