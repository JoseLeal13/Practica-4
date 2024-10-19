#include "enrutador.h"

// Constructor de Enrutador
Enrutador::Enrutador(int id) : id(id) {}

// Método para agregar un vecino
void Enrutador::agregarVecino(int id_vecino, int costo) {
    vecinos.push_back(make_pair(id_vecino, costo));
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

        for (auto& vecino : enrutadores[id_actual].vecinos) {
            int id_vecino = vecino.first;
            int costo = vecino.second;

            if (dist[id_actual] + costo < dist[id_vecino]) {
                dist[id_vecino] = dist[id_actual] + costo;
                prev[id_vecino] = id_actual;
                pq.push(make_pair(dist[id_vecino], id_vecino));
            }
        }
    }

    // Imprimir la tabla de enrutamiento
    cout << "Distancias desde el enrutador " << id_inicio << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Enrutador " << i << ": " << dist[i] << " (Prev: " << prev[i] << ")\n";
    }
}
