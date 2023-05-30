#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "secuencia.hpp"

using namespace std;

int main() {
    ifstream entrada;
    entrada.open("secuencias-nucleotidos.txt", ios::in);

    int l;
    entrada >> l;

    char* nucleotidos = new char[l];
    entrada >> nucleotidos;

    int k;
    entrada >> k;

    int m;
    string instruccion;

    int pos;
    char nucleotido;

    char* reconstruida;
    unsigned int largo;

    ofstream salida("secuencias-reconstruidas.txt");
    for (int i = 0; i < k; i++) {
        secuencia base(nucleotidos, l);
        entrada >> m;

        for (int i = 0; i < m; i++) {
            entrada >> instruccion;
            entrada >> pos;
            if (instruccion == "INSERTAR") {
                entrada >> nucleotido;
                base.insertar(pos, nucleotido);
            }
            else if (instruccion == "BORRAR") {
                base.borrar(pos);
            }
            else if (instruccion == "INTERCAMBIAR") {
                entrada >> nucleotido;
                base.intercambiar(pos, nucleotido);
            }
        }

        reconstruida = base.getSecuencia(largo);
        salida << reconstruida << "\n";
        delete[] reconstruida;
    }

    delete[] nucleotidos;
    salida.close();
    entrada.close();

    return 0;
}
