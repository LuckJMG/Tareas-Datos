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
    char* getSecuencia();
};

/*****
* secuencia::secuencia
******
* Constructor del TDA secuencia, construye el genoma base
* a partir de un arreglo de caracteres con los nucleotidos,
* convirtiendolos en una lista enlazada, a traves de la función
* append.
******
* Input:
* char* nucleotidos : Arreglo de caracteres con los nucleotidos de la base.
* unsigned int largo : Largo del arreglo de nucleotidos.
*****/
secuencia::secuencia(char* nucleotidos, unsigned int largo) {
    head = tail = cur = NULL;
    size = 0;

    for (unsigned int i = 0; i < largo; i++) {
        append(nucleotidos[i]);
    }
}

/*****
* secuencia::~secuencia
******
* Destructor del TDA secuencia, va borrando
* cada nodo de la secuencia hasta que no quede ninguno.
*****/
secuencia::~secuencia() {
    for (unsigned int i = 0; i < size; i++) {
        cur = head;
        head = head->next;
        delete cur;
    }
}

/*****
* void secuencia::insertar
******
* Inserta el nucleotido indicado en la posición dada de la secuencia.
******
* Input:
* unsigned int position : Posición de la inserción.
* char nucleotido : Nucleotido a insertar.
*****/
void secuencia::insertar(unsigned int position, char nucleotido) {
    // Posición fuera de limites
    if (position >= size || position < 0) return;

    size++;
    // Caso añadir al inicio
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

/*****
* void secuencia::intercambiar
******
* Intercambia el nucleotido de la secuencia en la posición dada por el nuevo entregado.
******
* Input:
* unsigned int position : Posición de la secuencia a intercambiar.
* char nucleotido: nuevo nucleotido a intercambiar.
*****/
void secuencia::intercambiar(unsigned int position, char nucleotido) {
    // Posicion fuera de limites
    if (position >= size || position < 0) return;

    cur = head;
    for (unsigned int i = 0; i < position; i++) cur = cur->next;

    cur->nucleotido = nucleotido;
}

/*****
* void secuencia::borrar
******
* Borra un nucleotido de la secuencia en la posicion dada.
******
* Input:
* unsigned int position : Posición del nucleotido a borrar.
* .......
*****/
void secuencia::borrar(unsigned int position) {
    // Posicion fuera de limites
    if (position >= size || position < 0) return;

    cur = head;

    // Caso inicio de la lista
    if (position == 0) {
        cur = head;
        head = head->next;
        delete cur;
        cur = head;
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

/*****
* void secuencia::append
******
* Añade el nucleotido dado al final de la secuencia.
******
* Input:
* char nucleotido : El nucleotido a añadir.
*****/
void secuencia::append(char nucleotido) {
    size++;

    // Caso lista vacia
    if (size == 1) {
        head = new node;
        head->nucleotido = nucleotido;
        tail = cur = head;
        return;
    }

    tail->next = new node;
    tail = tail->next;
    tail->nucleotido = nucleotido;
}

/*****
* char* secuencia::getSecuencia
******
* Genera un arreglo de caracteres que contiene la secuencia
* actualmente guardada en la TDA, para despues entregarla.
******
* Returns:
* char*, Arreglo de caracteres que contiene la secuencia guardada en la TDA.
*****/
char* secuencia::getSecuencia() {
    char* charSecuencia = new char[size + 1];

    cur = head;
    for (unsigned int i = 0; i < size; i++) {
        charSecuencia[i] = cur->nucleotido;
        cur = cur->next;
    }

    charSecuencia[size] = '\0';

    return charSecuencia;
}
