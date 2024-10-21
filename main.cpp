#include "enrutador.h"

int main() {
    Red red;

    for (int i = 0; i < 4; i++) {
        red.agregarEnrutador(i);
    }

    // Agregar enlaces (id1, id2, costo)
    red.agregarEnlace(0, 1, 1);
    red.agregarEnlace(0, 2, 4);
    red.agregarEnlace(1, 2, 2);
    red.agregarEnlace(1, 3, 5);
    red.agregarEnlace(2, 3, 1);

    // Ejecutar Dijkstra desde el enrutador 0
    red.dijkstra(0);

    return 0;
}
