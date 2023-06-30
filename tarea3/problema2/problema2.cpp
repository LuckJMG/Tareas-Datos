#include <iostream>
#include <string>
#include "commandHeap.hpp"

using namespace std;

int main() {
    commandHeap heap;
    string input;
    int created = 0;

    cin >> input;

    while (input != "TERMINATE") {
        if (input == "PUSHCOMMAND") {
            // Creación de nuevo comando
            command nuevo;
            cin >> nuevo.id >> nuevo.priority;
            getline(cin, nuevo.instruction);
            nuevo.instruction.erase(0, 1);

            // Añadir comando al heap
            heap.addCommand(nuevo);
            created++;

            // Output PUSHCOMMAND
            cout << heap.count() <<  " PENDING" << endl;
        }
        else if (input == "GET") {
            int N;
            cin >> N;

            // Strings de id e instrucciones
            string lista = to_string(N);
            string comandos = "";
            command comando;

            // Chequear que hayan comandos en el heap
            if (heap.count() == 0) {
                comandos = "0";
                cout << comandos << endl;
            }
            else {
                for (int i = 0; i < N; i++) {
                    if (heap.count() <= 0) {
                        // Caso en el que se acaben los comandos en el heap
                        if (i != N - 1) comandos = comandos + '\n';
                        continue;
                    }

                    // Obtener el comando de mayor prioridad y luego eliminarlo del heap
                    comando = heap.getCommand();
                    heap.removeCommand();

                    // Añadir id e instrucciones a sus respectivos strings
                    lista = lista + ' ' + comando.id;
                    if (i != N - 1) comandos = comandos + comando.instruction + '\n';
                    else comandos = comandos + comando.instruction;
                }

                // Output GET
                cout << lista << endl;
                cout << comandos << endl;
            }
        }

        cin >> input;
    }

    // Output TERMINATE
    cout << created - heap.count() << " SENT " << created << " CREATED" << endl;

    return 0;
}
