#include <fstream>
#include <string>
#include "secuencia.hpp"

using namespace std;

int main() {
    ifstream entrada;
    entrada.open("secuencias-nucleotidos.txt", ios::in);

    int l;
    char* nucleotidos = new char[l + 1];
    int k;

    entrada >> l;
    entrada >> nucleotidos;
    entrada >> k;

    ofstream salida("secuencias-reconstruidas.txt");

    int m;
    string instruccion;
    int pos;
    char nucleotido;
    char* reconstruida;

    // Edita la base desde 0, k veces
    for (int i = 0; i < k; i++) {
        secuencia base(nucleotidos, l);
        entrada >> m;

        // Ejecuta los m argumentos dados
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

        reconstruida = base.getSecuencia();
        salida << reconstruida << endl;
        delete[] reconstruida;
    }

    delete[] nucleotidos;
    salida.close();
    entrada.close();

    return 0;
}
