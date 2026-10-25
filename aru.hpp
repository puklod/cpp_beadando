#ifndef _ARU_HPP_
#define _ARU_HPP_

#include <string>

using namespace std;

class Aru{
public:
    Aru(string nev, string gyarto, string arukod, int ar, int raktarKeszlet);
    virtual string toString();
    string arukod();
    int ar();
    int raktarKeszlet();

private:
    string mNev;
    string mGyarto;
    string mArukod;
    int mAr;
    int mRaktarKeszlet;
};

#endif // _ARU_HPP_
