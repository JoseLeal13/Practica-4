#include "enrutador.h"

using namespace std;

void mostrarMenu() {
    cout << "----- Menú -----" << endl;
    cout << "1. Agregar Enrutador" << endl;
    cout << "2. Eliminar Enrutador" << endl;
    cout << "3. Añadir Enlace" << endl;
    cout << "4. Eliminar Enlace" << endl;
    cout << "5. Mostrar Caminos" << endl;
    cout << "0. Salir" << endl;
    cout << "Elija una opción: ";
}

int main() {
    Red red;
    int opcion;
    red.cargarDesdeArchivo("C:\\Users\\Lenovo\\Documents\\Practica4\\topologia");

    do {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            int id;
            cout << "Ingrese el ID del enrutador a agregar: ";
            cin >> id;
            red.agregarEnrutador(id);

            int idVecino, costo;
            cout << "Ingrese el ID del vecino: ";
            cin >> idVecino;
            cout << "Ingrese el costo del enlace: ";
            cin >> costo;
            red.agregarEnlace(id, idVecino, costo);

        } else if (opcion == 2) {
            int id;
            cout << "Ingrese el ID del enrutador a eliminar: ";
            cin >> id;
            red.eliminarEnrutador(id);

        } else if (opcion == 3) {
            int id1, id2, costo;
            cout << "Ingrese el ID del primer enrutador: ";
            cin >> id1;
            cout << "Ingrese el ID del segundo enrutador: ";
            cin >> id2;
            cout << "Ingrese el costo del enlace: ";
            cin >> costo;
            red.agregarEnlace(id1, id2, costo);

        } else if (opcion == 4) {
            int id1, id2;
            cout << "Ingrese el ID del primer enrutador: ";
            cin >> id1;
            cout << "Ingrese el ID del segundo enrutador: ";
            cin >> id2;
            red.eliminarEnlace(id1, id2);

        } else if (opcion == 5) {
            int idOrigen, idDestino;
            cout << "Ingrese el ID del enrutador de origen: ";
            cin >> idOrigen;
            cout << "Ingrese el ID del enrutador de destino: ";
            cin >> idDestino;

            // Mostrar la tabla de enrutamiento y el costo del camino
            int costo = red.calcularCosto(idOrigen, idDestino);
            vector<int> camino = red.determinarCamino(idOrigen, idDestino);

            cout << "Costo desde " << idOrigen << " a " << idDestino << ": "
                 << (costo != numeric_limits<int>::max() ? to_string(costo) : "Infinito") << endl;

            cout << "Camino más eficiente: ";
            for (int id : camino) {
                cout << id << " ";
            }
            cout << endl;

            cout << "Presione la barra espaciadora para continuar...";
            while (cin.get() != ' ');
            system("clear || cls");

        } else if (opcion == 0) {
            cout << "Saliendo del programa." << endl;
        } else {
            cout << "Opción no válida. Intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}
/*
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
*/
