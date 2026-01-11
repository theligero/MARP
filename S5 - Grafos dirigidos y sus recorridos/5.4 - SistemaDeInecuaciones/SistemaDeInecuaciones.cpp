/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>

#include "Digrafo.h"

/*@ <answer>
* El problema plantea la construcción de un grafo dirigido en el que
* la dirección se define como una relación del tipo V1 < V2. La clave
* a la hora de resolver este problema es buscar un grafo que no tenga
* ningún tipo de ciclo, pues eso implicaría una dependencia circular
* que no queremos que ocurra (a < b < c < ... < a).
* 
* Por lo tanto, a la hora de resolver este problema, se deberá hacer
* un recorrido total por el número de los distintos puntos que
* conforman el grafo más, posteriormente, todos los vértices que
* constituyen las direcciones. Esto implica que estamos ante un
* problema que tendrá un coste de complejidad O(V + A), siendo V el
* número de vértices que conforman el grafo y A el número de aristas
* que lo conforman.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

enum STATE_OF_VISIT { NOT_VISITED, CURRENTLY_VISITING, VISITED };

bool hasConsistentInequalities(const Digrafo& digrafo, 
    std::vector<STATE_OF_VISIT>& visited, std::vector<int>& topo, int v) {

    visited[v] = CURRENTLY_VISITING;
    for (auto& w : digrafo.ady(v)) {
        if (visited[w] == CURRENTLY_VISITING) return false;
        else if (visited[w] == NOT_VISITED) {
            if (!hasConsistentInequalities(digrafo, visited, topo, w)) return false;
        }
    }

    visited[v] = VISITED;
    topo.push_back(v);
    return true;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M; std::cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo digrafo(N);

    for (int i = 0; i < M; ++i) {
        int v, w; std::cin >> v >> w;
        --v; --w;
        digrafo.ponArista(v, w);
    }

    std::vector<STATE_OF_VISIT> visited(N, NOT_VISITED); // vector de nodos visitados
    std::vector<int> topo; // vector de valores de cada inecuación
    topo.reserve(N);

    bool ok = true;
    for (int i = 0; i < N && ok; ++i) {
        if (visited[i] == NOT_VISITED) {
            ok = hasConsistentInequalities(digrafo, visited, topo, i);
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    std::string sol = ok ? "SI" : "NO";

    // escribir la solución
    std::cout << sol;
    if (ok) {
        std::reverse(topo.begin(), topo.end());
        std::vector<int> values(N);
        for (int i = 0; i < N; ++i) {
            values[topo[i]] = i + 1;
        }
        for (auto& e : values) {
            std::cout << ' ' << e;
        }
    }
    std::cout << '\n';

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
