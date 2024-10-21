#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <fstream>

using namespace std;

class Enrutador {
public:
    int id;
    vector<int> vecinos; // IDs de los vecinos
    vector<int> costos;  // Costos asociados a cada vecino
    vector<int> tabla_ruteo; // Tabla de enrutamiento (costos a cada destino)

    Enrutador(int id);
    void agregarVecino(int id_vecino, int costo);
    void eliminarVecino(int id_vecino);
    void mostrarTablaRuteo() const;
};

class Red {
public:
    vector<Enrutador> enrutadores;

    void agregarEnrutador(int id);
    void eliminarEnrutador(int id);
    void agregarEnlace(int id1, int id2, int costo);
    void eliminarEnlace(int id1, int id2);
    void dijkstra(int id_inicio);
    void cargarDesdeArchivo(const string& nombre_archivo);
};

#endif // ENRUTADOR_H
