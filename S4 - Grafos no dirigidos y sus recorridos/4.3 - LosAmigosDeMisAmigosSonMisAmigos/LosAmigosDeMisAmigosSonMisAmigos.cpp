/*@ <authors>
 * MARP32 - Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <climits>

#include "Grafo.h"

/*@ <answer>
* El problema se plantea como un grafo de amistades, donde entendemos las personas
* vértices y las amistades como las aristas que conectan a las personas. Por lo
* tanto, lo primero que se debe hacer es recorrer en profundidad el grafo para
* averiguar cuál es el grupo de amistades mayor. El coste de esta operación, por
* lo tanto, al ser un recorrido lineal, es de coste O(V + A), siendo V los vértices
* (o como he dicho antes las personas) y A las aristas (que en este caso son las
* propias amistades).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void numOfFriends(const Grafo& gr, std::vector<bool>& visited, 
    int vertex, int& count) {
    visited[vertex] = true;
    ++count;

    for (auto& e : gr.ady(vertex)) {
        if (!visited[e]) {
            numOfFriends(gr, visited, e, count);
        }
    }
}

void resuelveCaso() {
    // leer los datos de la entrada
    int N, M; std::cin >> N >> M;
    Grafo gr(N);

    for (int i = 0; i < M; ++i) {
        int A, B; std::cin >> A >> B;
        --A; --B;
        gr.ponArista(A, B);
    }

    std::vector<bool> visited(N, false);
    int maxFriends = INT_MIN;
    
    // resolver el caso posiblemente llamando a otras funciones
    for (int j = 0; j < N; ++j) {
        int count = 0;
        if (!visited[j]) {
            numOfFriends(gr, visited, j, count);
            maxFriends = std::max(maxFriends, count);
        }
    }

    // escribir la solución
    std::cout << maxFriends << '\n';
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);;
#endif
    return 0;
}