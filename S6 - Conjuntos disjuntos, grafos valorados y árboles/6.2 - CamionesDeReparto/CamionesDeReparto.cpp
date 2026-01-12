/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <stack>

#include "GrafoValorado.h"

/*@ <answer>
* El problema del reparto se plantea como un grafo no dirigido y
* valorado donde cada arista representa el valor de la anchura de
* las calles que separan los distintos nodos.
* 
* Por lo tanto, se entiende que el problema en su conjunto está en
* el orden O(K * (V + E)), siendo K el número de consultas que se
* hace del grafo, V el número de vértices totales que conforman el
* grafo y E el número de aristas.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool couldTravelToDestination(GrafoValorado<int>& grafo, const int& origen,
    const int& destino, const int& anchura, std::vector<bool>& visited) {
    std::stack<int> cola; cola.push(origen);

    while (!cola.empty()) {
        int v = cola.top(); cola.pop();
        visited[v] = true;
        for (auto& e : grafo.ady(v)) {
            int w = e.otro(v);
            if (e.valor() >= anchura && !visited[w]) cola.push(w);
        }
    }

    return visited[destino];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int V; std::cin >> V;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> grafo(V);
    int E; std::cin >> E;

    for (int i = 0; i < E; ++i) {
        int v, w, value; std::cin >> v >> w >> value;
        --v; --w;
        grafo.ponArista({ v, w, value });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int K; std::cin >> K;
    for (int j = 0; j < K; ++j) {
        std::vector<bool> visited(V, false);
        int o, d, size; std::cin >> o >> d >> size;
        --o; --d;
        // escribir la solución
        std::string sol = couldTravelToDestination(grafo, o, d, size, visited) ? "SI\n" : "NO\n";
        std::cout << sol;
    }

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
