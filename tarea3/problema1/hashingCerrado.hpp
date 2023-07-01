#include <iostream>
#include <string>
#include <cstring>

#define Vacia ""
#define M 32

using namespace std;

typedef string tipoClave;
typedef string tipoInfo;

struct ranura {
    tipoClave clave = "";
    tipoInfo info = "";
};

class hashingCerrado {
private:
    ranura* HT;
    int tamanio;
    int contador;
public:
    hashingCerrado();
    ~hashingCerrado();
    bool iniciar_sesion(string usuario, string clave);
    bool crear_nuevo_usuario(string usuario, string clave);
    bool cambiar_clave(string usuario, string nueva_clave);
    int h(tipoClave k);
    int p(int i);
    int hashInsert(ranura HT[], tipoClave k, tipoInfo I);
    void resize();
};

/*****
* hashingCerrado
******
* Constructor del TDA hashingCerrado, inicializa el array vació.
*****/
hashingCerrado::hashingCerrado() {
    tamanio = M;
    HT = new ranura[tamanio];

    for (int i = 0; i < tamanio; i++) {
        ranura vacia;
        HT[i] = vacia;
    }

    contador = 0;
}

/*****
* ~hashingCerrado
******
* Destructor del TDA hashingCerrado, elimina el array principal.
*****/
hashingCerrado::~hashingCerrado() {
    delete[] HT;
}

/*****
* bool iniciar_sesion
******
* Busca el usuario en la ranura, si lo encuentra revisa que la clave este correcta.
******
* Input:
* str usuario : Nombre de usuario ingresado
* tipoClave k : Clave del usuario ingrasada
******
* Returns:
* bool : Retorna true si el usuario se encuentra en la ranura y
*        la clave es correcta, si no retorna false.
*****/
bool hashingCerrado::iniciar_sesion(string usuario, string clave){
    for (int i = 0; i < tamanio; i++){
        if (HT[i].info==usuario){
            if(HT[i].clave==clave){
                cout<<"Sesion iniciada con exito"<<endl;
                return true;
            }
            else {
                cout<<"La clave ingresada no coincide"<<endl;
                return false;
            }
        }
    }
    cout<<"El usuario no se encuentra registrado"<<endl;
    return false;
}

/*****
* bool crear_nuevo_usuario
******
* Ingresa un nuevo usuario en la ranura, asegurándose que no este ya registrado
* y que la contraseña cumpla los requisitos
******
* Input:
* str usuario : Nombre de usuario para registrar en la ranura
* str clave : Clave del usuario a ingresar en la ranura
******
* Returns:
* bool : Retorna falso si ya estaba registrado el usuario o la clave no
*        cumplía con los requisitos y retorna verdadero si se
*        pudo registrar el usuario junto a su clave
*****/
bool hashingCerrado::crear_nuevo_usuario(string usuario, string clave){
    int i;

    for(i=0; i < tamanio; i++){
        if(HT[i].info == usuario){
            cout<<"El usuario ya se encuentra registrado"<<endl;
            return false;
        }
    }

    if(clave.length() < 8){
        cout<<"La clave debe tener al menos 8 caracteres"<<endl;
        return false;
    }

    hashInsert(HT, clave, usuario);
    cout<<"Usuario registrado con exito"<<endl;
    return true;
}

/*****
* bool cambiar_clave
******
* Cambia la clave de un usuario en la ranura
******
* Input:
* str usuario : Nombre de usuario ingresado
* str nueva_clave : Clave nueva a asignar al usuario
******
* Returns:
* bool : Retorna False si no esta el usuario en la ranura o la clave no cumple
*        con los requisitos y retorna verdadero si la clave pudo ser actualizada
*****/
bool hashingCerrado::cambiar_clave(string usuario, string nueva_clave){
    int i;
    for (i=0;tamanio!=i;i++){
        if (HT[i].info==usuario){
            if (nueva_clave.length() >= 8){
                HT[i].clave=nueva_clave;
                cout<<"Clave actualizada con exito"<<endl;
                return true;
            }
            else {
                cout<<"La clave debe tener al menos 8 caracteres"<<endl;
                return false;
            }
        }
    }
    cout<<"El usuario no se encuentra registrado"<<endl;
    return false;
}

/*****
* int h
******
* Función de hashing que hashea las claves devolviendo el largo de la clave más 1.
******
* Input:
* tipoClave k : Clave a hashear
******
* Returns:
* int, Hash de la clave
*****/
int hashingCerrado::h(tipoClave k){
    int a = k.length();
    return a + 1;
}

/*****
* int p
******
* Función de resolución de colisiones de hashing, mediante una formula
* cuadrática con números primos.
******
* Input:
* int i : Cantidad de colisiones del hashing
******
* Returns:
* int, Desplazamiento de la posición
*****/
int hashingCerrado::p(int i){
    return i*i*7 + i*47 + 5;
}

/*****
* int hashInsert
******
* Inserta el elemento entregado en el array, si es que no existe.
******
* Input:
* ranura HT[] : Arreglo de hashing
* tipoClave k : Clave a añadir
* tipoInfo I : Información asociada a la clave
******
* Returns:
* int, 1 si es una inserción exitosa, 0 si ya existe el elemento a insertar.
*****/
int hashingCerrado::hashInsert(ranura HT[], tipoClave k, tipoInfo I) {
    int inicio;
    int pos = inicio = h(k);
    for (int i = 1; HT[pos].clave != Vacia; i++){
        pos= (inicio + p(i)) % tamanio;
    }
    if (HT[pos].clave==k) {
        return 0;
    }
    else {
        HT[pos].clave = k;
        HT[pos].info = I;
        contador++;
        float factor = contador * 1.0 / tamanio;

        if (factor > 0.7) {
            resize();
        }

        return 1;
    }
}

/*****
* void resize
******
* Agranda la capacidad del arreglo en caso de que el factor de carga del arreglo
* sea mayor a 0.7.
*****/
void hashingCerrado::resize() {
    ranura* tmp = new ranura[tamanio*2];

    for (int i = 0; i < tamanio * 2; i++) {
        ranura vacia;
        tmp[i] = vacia;
    }

    tamanio = tamanio * 2;
    contador = 0;
    for (int i = 0; i < tamanio / 2; i++) {
        if (HT[i].clave != Vacia) hashInsert(tmp, HT[i].clave, HT[i].info);
    }

    delete[] HT;
    HT = tmp;
}
