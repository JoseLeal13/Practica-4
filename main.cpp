#include "enrutador.h"

int main() {
    Red red;

    // Cargar la red desde un archivo
    red.cargarDesdeArchivo("C:\\Users\\Lenovo\\Documents\\Practica4\\topologia");
    // Ejecutar Dijkstra desde el enrutador 0

    // Probar el costo de enviar un paquete desde el enrutador 0 al enrutador 3
    int costo = red.calcularCosto(0, 3);
    cout << "Costo de enviar un paquete desde el enrutador 0 al enrutador 3: " << costo << endl;

    // Probar el camino más eficiente desde el enrutador 0 al enrutador 3
    vector<int> camino = red.determinarCamino(0, 3);
    cout << "Camino más eficiente desde el enrutador 0 al enrutador 3: ";
    if (camino.empty()) {
        cout << "No hay camino disponible." << endl;
    } else {
        for (int id : camino) {
            cout << id << " ";
        }
        cout << endl;
    }
}
