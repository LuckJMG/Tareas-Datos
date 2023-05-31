#include <iostream>
#include <list>

using namespace std;

struct tNodoArbolBin{
    int info;
    tNodoArbolBin* izq;
    tNodoArbolBin* der;
};

class tABB {
    tNodoArbolBin *raiz;
    int nElems;
};


int main(){
    tABB::tABB.insert(3);
    cout<<tABB::tABB.size()<<endl;
    return 0;
}