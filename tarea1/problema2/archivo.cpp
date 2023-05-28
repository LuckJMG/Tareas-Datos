#include <iostream>
#include <string>

using namespace std;

int p; // Cantidad de personas

struct Persona {
    string nombre;
    char fecha[11];
    int tamanio_tarjeta;
    int* tarjeta;
    bool quiere_intercambiar;
};

/*****
* int* comprarTarjeta
******
* Genera una tarjeta a traves del nombre de la persona y el dia actual
******
* Input:
* string nombre : nombre de la persona
* int dia : dia actual
* int &m : referencia a una variable a la que se le asignara el tamaño de la tarjeta
******
* Returns:
* int*, La tarjeta en forma de arreglo de números
*****/
int* comprarTarjeta(string nombre, int dia, int &m) {
    m = nombre.length();
    int* tarjeta = new int[m];

    for (int i = 0; i < m; i++) {
        tarjeta[i] = nombre[i] % dia;
    }

    return tarjeta;
}

/*****
* void intercambiarTarjeta
******
* Intercambia las tarjetas entre 2 personas.
******
* Input:
* Persona* p1 : primera persona a intercambiar tarjetas
* Persona* p2 : segunda persona a intercambiar tarjetas
*****/
void intercambiarTarjeta(Persona* p1, Persona* p2) {
    if (!(p1->quiere_intercambiar && p2->quiere_intercambiar)) {
        return;
    }

    for (int i = 0; i < p1->tamanio_tarjeta; i++) {
        for (int j = 0; j < p2->tamanio_tarjeta; j++) {
            if (p1->tarjeta[i] == p2->tarjeta[j]) {
                // Cambiar tarjetas
                int *tmp_tarjeta = p1->tarjeta;
                p1->tarjeta = p2->tarjeta;
                p2->tarjeta = tmp_tarjeta;

                // Cambiar tamaños respectivos
                int tmp_tamanio = p1->tamanio_tarjeta;
                p1->tamanio_tarjeta = p2->tamanio_tarjeta;
                p2->tamanio_tarjeta = tmp_tamanio;

                return;
            }
        }
    }
}

/*****
* int puntaje
******
* Calcula el puntaje de una persona según su tarjeta y su fecha de nacimiento
******
* Input:
* Persona* p1: persona a la que se le calculara el puntaje
******
* Returns:
* int, el puntaje calculado
*****/
int puntaje(Persona* p1) {
    int puntaje = 0;
    int largo = p1->tamanio_tarjeta;

    for (int i = 0; i < largo; i++) {
        puntaje += p1->tarjeta[i] * p1->fecha[i % 10];
    }

    return puntaje;
}

/*****
* Persona* unDia
******
* Genera las tarjetas de todas las personas inscritas,
* se realizan los intercambios deseados,
* y se calcula el ganador del dia.
******
* Input:
* Persona* personas: arreglo con las personas inscritas
* int dia: el dia actual
******
* Returns:
* Persona*: devuelve el puntero a la persona ganadora del dia
*****/
Persona* unDia(Persona* personas, int dia) {
    // Compra de tarjetas
    for (int i = 0; i < p; i++) {
        delete[] personas[i].tarjeta;
        personas[i].tarjeta = comprarTarjeta(personas[i].nombre, dia, personas[i].tamanio_tarjeta);
    }

    // Intercambios
    for (int i = 0; i < p; i++) {
        for (int j = i + 1; j < p; j++) {
            intercambiarTarjeta(&personas[i], &personas[j]);
        }
    }

    // Mayor puntaje del dia
    int mayorPuntaje = -1;
    int puntaje_persona;
    Persona* ganador;

    for (int i = 0; i < p; i++) {
        puntaje_persona = puntaje(&personas[i]);
        if (puntaje_persona <= mayorPuntaje)
            continue;

        mayorPuntaje = puntaje_persona;
        ganador = &personas[i];
    }

    return ganador;
}

/*****
* void variosDias
******
* Muestra en pantalla el ganador de cada dia.
******
* Input:
* Persona* personas: arreglo con las personas inscritas
* int cant_dias: cantidad de dias a calcular el ganador
*****/
void variosDias(Persona* personas, int cant_dias) {
    Persona* ganador;

    for (int i = 1; i <= cant_dias; i++) {
        ganador = unDia(personas, i);
        cout << ganador->nombre << " " << ganador->fecha << " " << puntaje(ganador) << endl;
    }
}

int main(){
    cin >> p;

    Persona* personas = new Persona[p];
    for(int i=0; i<p; i++){
        cin >> personas[i].nombre >> personas[i].fecha >> personas[i].quiere_intercambiar;
    }

    int dias;
    cin >> dias;
    variosDias(personas, dias);
    delete[] personas;
    return 0;
}
