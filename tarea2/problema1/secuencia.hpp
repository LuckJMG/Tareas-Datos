#include <stddef.h>
#include <iostream>

using namespace std;

struct node {
    char nucleotido;
    node* next = NULL;
};


class secuencia {
private:
    unsigned int size;
    node* head;
    node* cur;
    node* tail;
public:
    secuencia(char* nucleotidos,unsigned int largo);
    ~secuencia();
    void insertar(unsigned int position, char nucleotido);
    void intercambiar(unsigned int position, char nucleotido);
    void borrar(unsigned int position);
    void append(char nucleotido);
    char* getSecuencia(unsigned int &largo);
};

secuencia::secuencia(char* nucleotidos,unsigned int largo) {
    head = tail = NULL;
    size = 0;
    for (unsigned int i = 0; i < largo; i++) {
        append(nucleotidos[i]);
    }
}

secuencia::~secuencia() {
    for (unsigned int i = 0; i < size; i++)
    {
        cur = head;
        head = head->next;
        delete cur;
    }
}

void secuencia::insertar(unsigned int position, char nucleotido) {
    // Posicion fuera de limites
    if (position >= size || position < 0) return;

    size++;
    // Caso anadir al inicio
    if (position == 0) {
        cur = head;
        head = new node;
        head->nucleotido = nucleotido;
        head->next = cur;
        return;
    }

    cur = head;
    for (unsigned int i = 0; i < position; i++) cur = cur->next;

    node* tmp = cur->next;
    cur->next = new node;
    cur->next->nucleotido = nucleotido;
    cur->next->next = tmp;
}

void secuencia::intercambiar(unsigned int position, char nucleotido) {
    // Posicion fuera de limites
    if (position >= size || position < 0) return;

    cur = head;
    for (unsigned int i = 0; i < position; i++) cur = cur->next;

    cur->nucleotido = nucleotido;
}

void secuencia::borrar(unsigned int position) {
    // Posicion fuera de limites
    if (position >= size || position < 0) return;

    cur = head;

    // Caso inicio de la lista
    if (position == 0) {
        cur = head;
        head = head->next;
        delete cur;
        return;
    }

    for (unsigned int i = 0; i < position - 1; i++) cur = cur->next;

    // Caso final de la lista
    if (position == size - 1) {
        delete cur->next;
        cur->next = NULL;
        tail = cur;
        return;
    }

    node* tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;

    size--;
}

void secuencia::append(char nucleotido) {
    size++;

    // Caso lista vacia
    if (size == 1) {
        head = new node;
        head->nucleotido = nucleotido;
        tail = head;
        return;
    }

    tail->next = new node;
    tail = tail->next;
    tail->nucleotido = nucleotido;
}

char* secuencia::getSecuencia(unsigned int &largo) {
    char* charSecuencia = new char[size];

    cur = head;
    for (unsigned int i = 0; i < size; i++) {
        charSecuencia[i] = cur->nucleotido;
        cur = cur->next;
    }

    largo = size;
    return charSecuencia;
}
