#include "enrutador.h"

int main() {
    Red red;

    // Cargar la red desde un archivo
    red.cargarDesdeArchivo("topologia.txt");

    // Ejecutar Dijkstra desde el enrutador 0
    red.dijkstra(0);

    // Agregar un nuevo enrutador
    red.agregarEnrutador(3);
    red.agregarEnlace(0, 3, 20);

    // Eliminar un enrutador
    red.eliminarEnrutador(1);

    // Ejecutar Dijkstra nuevamente
    red.dijkstra(0);

    return 0;
}
