#include <iostream>
#include <string>
#include "hashingCerrado.hpp"

using namespace std;

typedef string tipoClave;

/*****
* bool OPERACION
******
* Busca el usuario en la ranura, si lo encuentra revisa que la clave este correcta.
******
* Input:
* hashingCerrado* hash : TDA hashingCerrado al cual hacerle las operaciones
* string operacion: stringing con la operacion entregada
* string usuario : Nombre de usuario ingresado
* tipoClave k : Clave del usuario ingresada
******
* Returns:
* bool : Retorna true si el usuario se encuentra en la ranura y la clave es correcta, si no retorna false.
*****/
bool OPERACION (hashingCerrado* hash, string operacion, string usuario, tipoClave k){
    if (operacion=="REGISTRAR"){
        bool Resultado;
        Resultado = hash->crear_nuevo_usuario(usuario,k);
        return Resultado;
    }
    if (operacion == "INICIAR_SESION"){
        bool Resultado;
        Resultado = hash->iniciar_sesion(usuario,k);
        return Resultado;
    }
    if (operacion=="ACTUALIZAR"){
        bool Resultado;
        Resultado = hash->cambiar_clave(usuario,k);
        return Resultado;
    }

    return false;
}

int main(){
    hashingCerrado hash;
    bool FINALIZAR = true;

    while (FINALIZAR == true){
        string operacion;
        cin >> operacion;

        if (operacion=="FINALIZAR"){
            return 0;
        }

        string usuario;
        tipoClave clave;
        cin >> usuario >> clave;

        OPERACION(&hash, operacion, usuario, clave);
    }
}
