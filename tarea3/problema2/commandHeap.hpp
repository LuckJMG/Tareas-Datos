#include <string>

#define SIZE 99999
#define MAX_INT 2147483647

using namespace std;

struct command {
    string id;
    int priority;
    string instruction;
};

class commandHeap {
private:
    command* heap;
    int cont;
public:
    commandHeap();
    ~commandHeap();
    int count();
    command getCommand();
    void addCommand(command comando);
    void removeCommand();
};

/*****
* commandHeap
******
* Constructor del TDA commandHeap, asigna la memoria del heap
* e inicializa el contador de elementos.
*****/
commandHeap::commandHeap() {
    heap = new command[SIZE];
    cont = 0;
}

/*****
* ~commandHeap
******
* Destructor del TDA commandHeap, borra el
* arreglo usado como heap.
*****/
commandHeap::~commandHeap() {
    delete[] heap;
}

/*****
* int count
******
* Devuelve la cantidad de comandos que hay en el heap.
******
* Returns:
* int, cantidad de comandos en el heap.
*****/
int commandHeap::count() {
    return cont;
}

/*****
* command commandHeap
******
* Devuelve el comando de mayor prioridad del heap.
******
* Returns:
* command, comando de mayor prioridad.
*****/
command commandHeap::getCommand() {
    return heap[1];
}

/*****
* void addCommand
******
* Añade un comando al heap, usando el método de flotar.
******
* Input:
* command comando : comando a añadir.
*****/
void commandHeap::addCommand(command comando) {
    // Añadir al final del heap
    cont++;
    int index = cont;
    heap[index] = comando;

    int parentIndex;
    command tmp;

    // Método de flotar
    while (index != 1) {
        parentIndex = index / 2;

        if (index == 0) return;

        // Intercambio
        if (heap[parentIndex].priority > comando.priority) {
            tmp = heap[parentIndex];
            heap[parentIndex] = comando;
            heap[index] = tmp;
            index = parentIndex;
        }
        else return;
    }
}

/*****
* void removeCommand
******
* Remueve el comando en la raíz del heap,
* usando el método de hundir.
*****/
void commandHeap::removeCommand() {
    // Caso solo un elemento en el heap
    if (cont == 1) {
        cont = 0;
        return;
    }

    // Eliminar la raíz del heap
    int index = 1;
    heap[1] = heap[cont];
    cont--;

    int value = heap[1].priority;
    int leftValue, rightValue;
    command tmp;

    // Método hundir
    while (index <= cont) {
        // Obtener prioridad del hijo de la izquierda
        if (index * 2 <= cont) leftValue = heap[index * 2].priority;
        else leftValue = MAX_INT;

        // Obtener prioridad del hijo de la derecha
        if ((index * 2) + 1 <= cont) rightValue = heap[(index * 2) + 1].priority;
        else rightValue = MAX_INT;

        // Parar si se llego a la posición deseada
        if (value <= leftValue && value <= rightValue) return;

        // Selección del nodo a intercambiar
        if (leftValue < rightValue) index *= 2;
        else index = (index * 2) + 1;

        // No salirse del largo del heap
        if (index > cont) return;

        // Intercambio
        tmp = heap[1];
        heap[1] = heap[index];
        heap[index] = tmp;
    }
}
