#include "Enrutador.h"

// Constructor de Enrutador
Enrutador::Enrutador(int id) : id(id) {}

// Método para agregar un vecino
void Enrutador::agregarVecino(int id_vecino, int costo) {
    vecinos.push_back(id_vecino);
    costos.push_back(costo);
    // Actualizar la tabla de enrutamiento
    if (tabla_ruteo.size() <= id_vecino) {
        tabla_ruteo.resize(id_vecino + 1, numeric_limits<int>::max());
    }
    tabla_ruteo[id_vecino] = costo; // Agregar a la tabla de enrutamiento
}

// Método para eliminar un vecino
void Enrutador::eliminarVecino(int id_vecino) {
    auto it = find(vecinos.begin(), vecinos.end(), id_vecino);
    if (it != vecinos.end()) {
        int index = distance(vecinos.begin(), it);
        vecinos.erase(it);
        costos.erase(costos.begin() + index);
        tabla_ruteo[id_vecino] = numeric_limits<int>::max(); // Resetear costo en la tabla de enrutamiento
    } else {
        cerr << "Vecino " << id_vecino << " no encontrado." << endl;
    }
}

// Mostrar la tabla de enrutamiento
void Enrutador::mostrarTablaRuteo() const{
    cout << "Tabla de enrutamiento para el enrutador " << id << ":" << endl;
    for (size_t i = 0; i < tabla_ruteo.size(); ++i) {
        if (tabla_ruteo[i] != numeric_limits<int>::max()) {
            cout << "Destino: " << i << ", Costo: " << tabla_ruteo[i] << endl;
        }
    }
}

// Método para agregar un enrutador a la red
void Red::agregarEnrutador(int id) {
    enrutadores.emplace_back(id);
}

// Método para agregar un enlace entre enrutadores
void Red::agregarEnlace(int id1, int id2, int costo) {
    enrutadores[id1].agregarVecino(id2, costo);
    enrutadores[id2].agregarVecino(id1, costo); // Asumimos que es una red no dirigida
}

// Método para ejecutar el algoritmo de Dijkstra
void Red::dijkstra(int id_inicio) {
    int n = enrutadores.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> prev(n, -1);
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
                prev[id_vecino] = id_actual;
                pq.push(make_pair(dist[id_vecino], id_vecino));
                // Actualizar la tabla de enrutamiento
                enrutadores[id_actual].tabla_ruteo[id_vecino] = dist[id_vecino];
            }
        }
    }

    // Mostrar la tabla de enrutamiento para cada enrutador
    for (const auto& enrutador : enrutadores) {
        enrutador.mostrarTablaRuteo();
    }
}
