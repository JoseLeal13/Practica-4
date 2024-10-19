#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <utility>

using namespace std;

class Enrutador {
public:
    int id;
    vector<pair<int, int>> vecinos; // (id_vecino, costo)

    Enrutador(int id);
    void agregarVecino(int id_vecino, int costo);
};

class Red {
public:
    vector<Enrutador> enrutadores;

    void agregarEnrutador(int id);
    void agregarEnlace(int id1, int id2, int costo);
    void dijkstra(int id_inicio);
};

#endif // ENRUTADOR_H
