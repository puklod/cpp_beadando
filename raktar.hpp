#ifndef _RAKTAR_HPP_
#define _RAKTAR_HPP_
#include <unordered_map>
#include <string>
#include "aru.hpp"

using namespace std;

class Raktar{
public:
    void hozzaad(string aruKod, Aru* aruReferencia);
    void torol(string aruKod);
    void kivesz(string aruKod, int mennyiseg);
    void feltolt(string aruKod, int mennyiseg);
    Aru* keres(string aruKod);
    string aruToString(string aruKod);
    void keszletNyomtatas();
private:
    unordered_map<string,Aru*> mRaktarKeszlet;
};

#endif // _RAKTAR_HPP_
