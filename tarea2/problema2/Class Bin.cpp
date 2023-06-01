typedef int tElem;

struct tNodoArbolBin{
    int info = 0;
    tNodoArbolBin* izq = NULL;
    tNodoArbolBin* der = NULL;
};

class tABB {
private:
    tNodoArbolBin *raiz;
    int nElems;
    int encendidos;
public:
    tABB();
    ~tABB();
    bool find(tElem x);
    void insert(tElem x);
    int lower_bound(tElem x);
    int OnCount();
};

/*****
* tABB::tABB
******
* Constructor del TDA tABB, Arbol Binario de Busqueda.
*****/
tABB::tABB() {
    raiz = NULL;
    nElems = 0;
}

/*****
* tABB::~tABB
******
* Destructor del TDA tABB, elimina todos los nodos antes 
* de borrar la variable.
*****/
tABB::~tABB() {
    clear(raiz);
    raiz = NULL;
    nElems = 0;
}

/*****
* void clear
******
* Ayuda al destructor a limpiar los nodos del TDA tABB.
******
* Input:
* tNodoArbolBin *nodo : Nodo al que borrar y borrar sus hijos.
*****/
void clear(tNodoArbolBin* nodo) {
    if (nodo == NULL) return;
    clear(nodo->izq);
    clear(nodo->der);
    delete nodo;
}

/*****
* bool tABB::find
******
* Intenta encontrar el elemento dado en el TDA, al encontrarlo
* devuelve true, si no lo encuentra devuelve false.
******
* Input:
* tElem x : Elemento a encontrar.
******
* Returns:
* bool, Si encuentra el elemento devuelve true, en caso contrario false.
*****/
bool tABB::find(tElem x) {
    return findHelp(raiz, x);
}

/*****
* bool findHelp
******
* Función de ayuda de tABB::find, la cual busca el elemento 
* dado en el nodo entregado y sus hijos.
******
* Input:
* tNodoArbolBin* nodo : Nodo actual de la busqueda.
* tElem x : Elemento a encontrar en el arbol.
******
* Returns:
* bool, Si encuentra el elemento devuelve true, en caso contrario false.
*****/
bool findHelp(tNodoArbolBin* nodo, tElem x) {
    if (nodo == NULL) return false;
    if (nodo->info == x) return true; 

    if (x < nodo->info) return findHelp(nodo->izq, x);
    else return findHelp(nodo->der, x);
}

/*****
* void tABB::insert
******
* Inserta el elemnto dado en el arbol binario.
******
* Input:
* tElem x : Elemnto a añadir al arbol.
*****/
void tABB::insert(tElem x) {
    insertHelp(raiz, x);
    nElems++;
}

/*****
* void insertHelp
******
* Función de ayuda para tABB::insert, el cual busca el nodo a insertar
* el elemento dado, en el nodo dado y sus hijos.
******
* Input:
* tNodoArbolBin* nodo : nodo actual en la busqueda.
* tElem x : Elemento a insertar en el arbol.
*****/
void insertHelp(tNodoArbolBin *nodo, tElem x) {
    if (nodo == NULL) { // Caso arbol vacio
        nodo = new tNodoArbolBin;
        nodo->info = x;
    }
    else if (x >= nodo->info) {
        if (nodo->der == NULL) {
            nodo->der = new tNodoArbolBin;
            nodo->der->info = x;
        }
        else insertHelp(nodo->der, x);
    }
    else {
        if (nodo->izq == NULL) {
            nodo->izq = new tNodoArbolBin;
            nodo->izq->info = x;
        }
        else insertHelp(nodo->izq, x);
    }
}

/*****
* int tABB::lower_bound
******
* Busca el primer valor que sea menor o igual a x en el arbol.
******
* Input:
* tElem x : Elemento al que se le busca el limite inferior.
******
* Returns:
* int, Limite inferior en el arbol del elemento x.
*****/
int tABB::lower_bound(tElem x){
    for (int i = x; i >= 0; i--) {
        if (find(i)) {
            return i;
        }
    }
    return x;
}

/*****
* int tABB::OnCount
******
* Retorna la cantidad total de postes encendidos.
******
* Returns:
* int, Cantidad de postes encendidas.
*****/
int tABB::OnCount(){
    return encendidos;
}


