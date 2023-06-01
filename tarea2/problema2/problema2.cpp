#include <iostream>
#include <string>
#include "arbol.hpp"

using namespace std;

/*Creacion arbol*/
tABB arbol;

/*****
* void ENCENDER
******
* Enciende el poste de luz en la posición indicada,
* agregandolo al arbol binario, si ya está encendido
* no hace nada.
******
* Input:
* int pos : Posición del poste a encender.
*****/
void ENCENDER (int pos){
    if (arbol.find(pos) == false) {
        arbol.insert(pos);
    }
}

/*****
* int CUANTOS_ENCENDER
******
* Determina cuantos postes quedan por encender entre
* la posición del poste dado y el poste de menor posición
* más cercano. Si en la posición dada no hay un poste encendido
* devuelve los postes que faltan por encender entre la posición
* 0 y la dada.
******
* Input:
* int pos : Entero con la posicion del poste.
******
* Returns:
* int, Cantidad de postes a encender.
*****/
int CUANTOS_ENCENDER (int pos){
    if (arbol.find(arbol.lower_bound(pos)) == false) {
        int count = 0;
        for (int i = 0; i <= pos; i++) {
            if (arbol.find(i) == false) {
                count++;
            }
        }
        return count;
    }
    else {
        int lower = arbol.lower_bound(pos);
        return pos - lower;
    }
}

/*****
* void PARAR_PROGRAMA
******
* Muestra por pantalla el total de postes encendidos y
* termina el programa
*****/
void PARAR_PROGRAMA (){
    int total = arbol.OnCount();
    cout<<total<<endl;
}

int main (){
    bool termino = true;
    while (termino!=false){
        string pedir;
        cin >> pedir;
        if(pedir == "ENCENDER"){
            int a;
            cin >> a;
            ENCENDER(a);
        }
        else if(pedir == "CUANTOS_ENCENDER"){
            int a;
            cin >> a;
            int dif = CUANTOS_ENCENDER(a);
            cout << dif << endl;
        }
        else if(pedir == "PARAR_PROGRAMA"){
            PARAR_PROGRAMA();
            termino = false;
        }
    }
}
