#ifndef _ARU_HPP_
#define _ARU_HPP_

#include <string>

using namespace std;

class Aru{
public:
    // Getterek
    string nev() const;
    string gyarto() const;
    string arukod() const;
    int ar() const;
    int raktarkeszlet() const;
    // A sima árunak nincs mértékegysége, de a másik kettőnél kell tudni, mit írjanak ki
    virtual string mertekegyseg() const = 0;

    // Két setter a raktárkészlethez
    void hozzaad(int mennyiseg);
    void kivesz(int mennyiseg);


    virtual string toString() const;
    virtual ~Aru() = default;

protected:
    Aru(const string& nev, const string& gyarto, const string& aruKod, int ar, int raktarKeszlet);

private:
    string mNev;
    string mGyarto;
    string mArukod;
    int mAr;
    int mRaktarkeszlet;
};

#endif // _ARU_HPP_
