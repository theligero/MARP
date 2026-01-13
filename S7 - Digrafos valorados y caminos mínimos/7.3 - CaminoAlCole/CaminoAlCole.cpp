/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>

#include "GrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>
* Este problema se plantea como un grafo no dirigido y valorado
* en el que cada vértice representa las intersecciones del pueblo
* de Lucas y las aristas las interconexiones entre estas. Una vez
* añadidas al grafo, nos apoyamos de una cola de prioridad variable
* que vaya almacenando los caminos mínimos posibles hasta el destino,
* mientras que tenemos otro vector con todas las posiciones de los
* nodos que van acumulando el número de "fórmulas" distintas que existe
* de llegar al nodo correspondiente con camino mínimo. Una vez se haya
* llegado al destino, entonces devolveremos el valor que contenga
* el nodo destino del acumulador de caminos.
* 
* Por tanto, a nivel de complejidad en tiempo, esto se traduce en un
* problema del tipo O(A * log(A)), siendo A el número de aristas totales
* que conforman el grafo y en espacio adicional sería algo como O(V),
* siendo V el número de intersecciones totales que conforman el grafo.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int numOfDifferentPaths(GrafoValorado<int>& grafo, const int& origin,
    const int& dest) {

    std::vector<int> dist(grafo.V(), INT_MAX);
    std::vector<int> ways(grafo.V(), 0);
    IndexPQ<int> pq(grafo.V());

    dist[origin] = 0;
    ways[origin] = 1;
    pq.push(origin, 0);

    while (!pq.empty()) {
        int v = pq.top().elem; pq.pop();
        for (auto& a : grafo.ady(v)) {
            int w = a.otro(v);
            if (dist[w] > dist[v] + a.valor()) {
                dist[w] = dist[v] + a.valor();
                ways[w] = ways[v];
                pq.update(w, dist[w]);
            }
            else if (dist[w] == dist[v] + a.valor()) {
                ways[w] += ways[v];
            }
        }
    }

    return ways[dest];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N; std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> grafo(N);
    int C; std::cin >> C;

    for (int i = 0; i < C; ++i) {
        int o, d, c; std::cin >> o >> d >> c;
        --o; --d;
        grafo.ponArista({ o, d, c });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int paths = numOfDifferentPaths(grafo, 0, N - 1);

    // escribir la solución
    std::cout << paths << '\n';

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
