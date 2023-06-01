#include <iostream>

using namespace std;

class tABB {
    tNodoArbolBin *raiz;
    int nElems;
};

struct tNodoArbolBin{
    int info;
    tNodoArbolBin* izq;
    tNodoArbolBin* der;
};