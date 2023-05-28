#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

/*CONSTANTES*/
int const SERV_DESAYUNO = 0;
int const SERV_ALMUERZO = 1;
int const SERV_ONCE = 2;
int const SERV_CENA = 3;

/*STRUCT*/ /*Nos dira cuanto saldo tiene cada colaborador*/
struct SaldoCobrador {
    char rut[11];
    int saldo_desayuno;
    int saldo_almuerzo;
    int saldo_once;
    int saldo_cena;
};

/*****
* int serviciopers
******
* Solicita al usuario que ingrese el codigo del servicio que desea seleccionar
* (0 - Desayuno, 1 - Almuerzo, 2 - Once, 3 - Cena) y devuelve el valor ingresado.
******
* Returns:
* int: codigo del servicio.
*****/
int serviciopers() {
    int a;

    cout << "Ingrese el numero del servicio que desea:" << endl;
    cout << "0. SERVICIO DESAYUNO" << endl;
    cout << "1. SERVICIO ALMUERZO" << endl;
    cout << "2. SERVICIO ONCE" << endl;
    cout << "3. SERVICIO CENA" << endl;
    cin >> a;

    return a;
}

/*****
* string ServSTR
******
* Recibe el codigo de un servicio
* (0 - Desayuno, 1 - Almuerzo, 2 - Once, 3 - Cena)
* y devuelve el nombre del servicio
******
* Input:
* int servicio: codigo del servicio.
******
* Returns:
* string: nombre del servicio.
*****/
string ServSTR(int servicio) {
    string nombreS;

    if (servicio == SERV_DESAYUNO) {
        nombreS = "DESAYUNO";
    }
    else if (servicio == SERV_ALMUERZO) {
        nombreS = "ALMUERZO";
    }
    else if (servicio == SERV_ONCE) {
        nombreS = "ONCE";
    }
    else if (servicio == SERV_CENA) {
        nombreS = "CENA";
    }

    return nombreS;
}

/*****
* void agregar_archdia
******
* Esta función agrega una línea a un archivo de texto en formato ASCII
* que contiene el rut del cliente y el servicio que ha solicitado.
******
* Input:
* char *rut: rut del cliente.
* string s: servicio solicitado.
* string con: nombre del archivo en el que se va a agregar la información.
*****/
void agregar_archdia(char *rut, string s, string con) {
    string rutt = rut;
    fstream file;

    file.open(con, ios::app);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo ACSII" << endl;
        exit(1);
    }

    file << rutt + " " << s + "\n";
    file.close();
}

/*****
* bool rialret
******
* Verifica si el cliente tiene saldo para un servicio
* de acuerdo a los tickets gastados en otras ocasiones, devolviendo verdadero si puede y falso si no.
******
* Input:
* int c: cantidad de tickets gastados en otras ocasiones.
* int servicio: codigo del servicio.
* SaldoCobrador de: saldo del cliente.
******
* Returns:
* bool: verdadero si el cliente tiene saldo, falso si no.
*****/
bool rialret(int c, int servicio, SaldoCobrador de) {
    if (servicio == SERV_DESAYUNO) {
        if (c >= de.saldo_desayuno) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (servicio == SERV_ALMUERZO) {
        if (c >= de.saldo_almuerzo) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (servicio == SERV_ONCE) {
        if (c >= de.saldo_once) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (servicio == SERV_CENA) {
        if (c >= de.saldo_cena) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return 0;
    }
}

/*****
* int consum_archdia
******
* Cuenta cuántos tickets el cliente ha gastado anteriormente
* en un servicio específico.
******
* Input:
* string con: nombre del archivo de los registros.
* char* rut: rut del cliente.
* int servicio: codigo del servicio.
******
* Returns:
* int: cantidad de registros encontrados según el rut y el servicio.
*****/
int consum_archdia(string con, char *rut, int servicio) {
    int a = 0;
    string rutt = rut;
    string serv = ServSTR(servicio);
    string espacio = " ";
    string finals = rutt + espacio + serv;
    string vacio;
    ifstream fileACSII;

    fileACSII.open(con);
    if (!fileACSII.is_open()) {
        ofstream output(con);
    }

    while (!fileACSII.eof()) {
        getline(fileACSII, vacio);
        if (vacio == "") break;

        if (vacio == finals) {
            a++;
        }
    }

    return a;
}

/*****
* bool puedeConsumir
******
* Verifica si un cliente puede realizar un consumo de un servicio,
* comparando su saldo con los consumos de dias anteriores.
******
* Input:
* char* rut: rut del cliente.
* int servicio: codigo del servicio
* string consumos_dia: nombre del archivo de los registros.
******
* Returns:
* bool: Verdadero si el cleinte puede realizar el consumo, falso si no.
*****/
bool puedeConsumir(char *rut, int servicio, string consumos_dia) {
    string rutt = rut;
    SaldoCobrador pr; /*Creacion de struct vacio*/
    ifstream binario;
    int i; /*Creacion de variable entero para sacar valor de n*/

    binario.open("saldos.bin", ios::binary);
    if (!binario.is_open()) {
        cout << "Error al abrir el archivo BINARIO" << endl;
        exit(1);
    }

    binario.read((char *)&i, sizeof(int));
    for (int z = 0; z < i; z++) {
        binario.read((char *)&pr, sizeof(SaldoCobrador));
        string rut_tmp = pr.rut;

        if (rutt == rut_tmp) {
            int j = consum_archdia(consumos_dia, rut, servicio);
            bool retorno = rialret(j, servicio, pr);
            return retorno;
        }
    }

    return 0;
}

/*FUNCION MAIN*/
int main () {
    char rut[11] = "70193249-k";

    cout << puedeConsumir(rut, 0, "consumos.txt") << endl;
    cout << puedeConsumir(rut, 1, "consumos.txt") << endl;
    cout << puedeConsumir(rut, 2, "consumos.txt") << endl;
    cout << puedeConsumir(rut, 3, "consumos.txt") << endl;

    return 0;
}
