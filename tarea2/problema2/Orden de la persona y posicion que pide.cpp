#include <iostream>
#include <string>
#include <cstring>
#include "Class Bin.cpp"

using namespace std;

/*Variables Globales*/
string EncenderSTR = "ENCENDER";
string CuantosSTR = "CUANTOS_ENCENDER";
string PararSTR = "PARAR_PROGRAMA";

int Error = 0;
int EncenderINT = 1;
int CuantosINT = 2;
int PararINT = 3;

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
    if (arbol.find(pos) == false) {
        int count = 0;
        for (int i = 0; i <= pos; i++) {
            if (arbol.find(i) == true) {
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

/*****
* int nombre
******
* Funcion que analiza lo escrito por el ususrio con la accion que 
* quiere realizar, para asi retornar y tener claridez de la accion a realizar.
******
* Input:
* string orden : Es lo que escriba el usuario en la consola con la orden.
******
* Returns:
* int, retorna un entero para despues segun el numero que sea procedera a hacer la accion requerida.
*****/
int nombre(string orden){
    if (orden[0]==EncenderSTR[0]){
        for (int a=1;a<EncenderSTR.length();a++){
            if (orden[a]!=EncenderSTR[a]){
                return 0;
            }          
        }
        return 1;
    } 
    else if (orden[0]==CuantosSTR[0]){
        for (int a=1;a<CuantosSTR.length();a++){
            if (orden[a]!=CuantosSTR[a]){
                return 0;
            }
        }
        return 2;
    } 
    else if (orden[0]==PararSTR[0]){
        for (int a=1;a<PararSTR.length();a++){
            if (orden[a]!=PararSTR[a]){
                return 0;
            }
        }
        return 3;
    } 
}


int main (){
    bool termino = true;
    while (termino!=false){
        string pedir;
        cin >> pedir;
        int CompVar = nombre(pedir);
        if(CompVar==EncenderINT){
            int a;
            cin >> a;
            ENCENDER(a);
        }
        else if(CompVar==CuantosINT){
            int a;
            cin >> a;
            int dif = CUANTOS_ENCENDER(a);
            
        }
        else if(CompVar==PararINT){
            PARAR_PROGRAMA();
            termino = false;
        }
    }
}