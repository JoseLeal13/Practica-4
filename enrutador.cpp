#include "enrutador.h"

// Constructor de Enrutador
Enrutador::Enrutador(int id) : id(id) {}

// Método para agregar un vecino
void Enrutador::agregarVecino(int id_vecino, int costo) {
    vecinos.push_back(id_vecino);
    costos.push_back(costo);
    if (tabla_ruteo.size() <= id_vecino) {
        tabla_ruteo.resize(id_vecino + 1, numeric_limits<int>::max());
    }
    tabla_ruteo[id_vecino] = costo;
}

// Método para eliminar un vecino
void Enrutador::eliminarVecino(int id_vecino) {
    auto it = find(vecinos.begin(), vecinos.end(), id_vecino);
    if (it != vecinos.end()) {
        int index = distance(vecinos.begin(), it);
        vecinos.erase(it);
        costos.erase(costos.begin() + index);
        tabla_ruteo[id_vecino] = numeric_limits<int>::max();
    } else {
        cerr << "Vecino " << id_vecino << " no encontrado." << endl;
    }
}

// Mostrar la tabla de enrutamiento
void Enrutador::mostrarTablaRuteo() const {
    cout << "Tabla de enrutamiento para el enrutador " << id << ":" << endl;

    // Imprimir encabezados de la tabla
    cout << "Destino   Costo" << endl;
    cout << "-----------------" << endl; // Línea separadora

    for (size_t i = 0; i < tabla_ruteo.size(); ++i) {
        cout << i << "        "
             << (tabla_ruteo[i] != numeric_limits<int>::max() ? to_string(tabla_ruteo[i]) : "Infinito")
             << endl;
    }
}

// Método para agregar un enrutador a la red
void Red::agregarEnrutador(int id) {
    enrutadores.emplace_back(id);
}

// Método para eliminar un enrutador de la red
void Red::eliminarEnrutador(int id) {
    if (id < 0 || id >= enrutadores.size()) {
        cerr << "ID de enrutador no válido." << endl;
        return;
    }

    for (auto& enrutador : enrutadores) {
        enrutador.eliminarVecino(id);
    }

    enrutadores.erase(enrutadores.begin () + id);
}

// Método para agregar un enlace entre enrutadores
void Red::agregarEnlace(int id1, int id2, int costo) {
    if (id1 < 0 || id1 >= enrutadores.size() || id2 < 0 || id2 >= enrutadores.size()) {
        cerr << "ID de enrutador no válido." << endl;
        return;
    }
    enrutadores[id1].agregarVecino(id2, costo);
    enrutadores[id2].agregarVecino(id1, costo);
}

// Método para eliminar un enlace entre enrutadores
void Red::eliminarEnlace(int id1, int id2) {
    if (id1 < 0 || id1 >= enrutadores.size() || id2 < 0 || id2 >= enrutadores.size()) {
        cerr << "ID de enrutador no válido." << endl;
        return;
    }
    enrutadores[id1].eliminarVecino(id2);
    enrutadores[id2].eliminarVecino(id1);
}

// Método para cargar la red desde un archivo
void Red::cargarDesdeArchivo(const string& nombre_archivo) {
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    int num_enrutadores, id1, id2, costo;
    archivo >> num_enrutadores;

    for (int i = 0; i < num_enrutadores; ++i) {
        agregarEnrutador(i);
    }

    while (archivo >> id1 >> id2 >> costo) {
        agregarEnlace(id1, id2, costo);
    }

    archivo.close();
}

// Método para calcular el costo de enviar un paquete
int Red::calcularCosto(int id_origen, int id_destino) {
    // Ejecutar Dijkstra para llenar la tabla de distancias
    dijkstra(id_origen);

    // Retornar el costo de enviar un paquete
    return enrutadores[id_destino].tabla_ruteo[id_origen];
}

// Método para determinar el camino más eficiente
vector<int> Red::determinarCamino(int id_origen, int id_destino) {
    dijkstra(id_origen); // Asegúrate de que se ejecute Dijkstra primero
    vector<int> camino;

    // Reconstruir el camino desde el destino hasta el origen usando el vector `prev` de la clase
    for (int at = id_destino; at != -1; at = prev[at]) {
        camino.push_back(at);
    }
    reverse(camino.begin(), camino.end()); // Invertir para obtener el orden correcto

    // Si el primer elemento no es el origen, significa que no hay camino
    if (camino.empty() || camino[0] != id_origen) {
        camino.clear(); // No hay camino
    }

    return camino;
}

// Modificar el algoritmo de Dijkstra para llenar el vector `prev`
void Red::dijkstra(int id_inicio) {
    int n = enrutadores.size();
    vector<int> dist(n, numeric_limits<int>::max());
    prev.assign(n, -1); // Utiliza el vector prev de la clase
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[id_inicio] = 0;
    pq.push(make_pair(0, id_inicio));

    while (!pq.empty()) {
        int id_actual = pq.top().second;
        pq.pop();

        for (size_t i = 0; i < enrutadores[id_actual].vecinos.size(); ++i) {
            int id_vecino = enrutadores[id_actual].vecinos[i];
            int costo = enrutadores[id_actual].costos[i];

            if (dist[id_actual] + costo < dist[id_vecino]) {
                dist[id_vecino] = dist[id_actual] + costo;
                prev[id_vecino] = id_actual; // Guardar el nodo anterior en el vector de la clase
                pq.push(make_pair(dist[id_vecino], id_vecino));

                // Actualizar la tabla de enrutamiento del enrutador vecino
                enrutadores[id_vecino].tabla_ruteo[id_inicio] = dist[id_vecino];
            }
        }
    }

    // Mostrar la tabla de enrutamiento para cada enrutador
    for (size_t i = 0; i < enrutadores.size(); ++i) {
        enrutadores[i].mostrarTablaRuteo();
    }
}
