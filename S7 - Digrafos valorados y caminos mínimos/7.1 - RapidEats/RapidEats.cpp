/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include <stack>
#include <string>

#include "GrafoValorado.h"
#include "IndexPQ.h"

const std::string ERROR_MSG = "NO LLEGA";

/*@ <answer>
* El problema se plantea como un grafo no dirigido y valorado
* en el que cada vértice representa los puntos de recarga /
* recogida / entrega que hay a lo largo de toda la ciudad mientras
* que las aristas representan las calles que unen dichos puntos.
* Una vez llevada a a cabo dicha representación, se aplica Dijkstra
* sobre el propio grafo para hallar el camino mínimo posible entre
* dos puntos origen y destino. Para ello nos apoyamos de una
* estructura de cola de prioridad varible que vaya almacenando
* los valores obtenidos hasta cualquiera de los puntos intermedios
* y valora si hay caminos alternativos más cortos. Trabajando siempre
* con los caminos más cortos, se haya la distancia más corta que
* separa ambos puntos
* 
* Este problema, por tanto, tiene una complejidad del tipo O(A * log(A)),
* siendo A el número de aristas totales, y tendrá una complejidad en
* espacio adicional de O(V), siendo V el número de vértices totales.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int minPathDuringDelivery(GrafoValorado<int>& grafo, const int& origen, 
    const int& destino, std::vector<Arista<int>>& ult) {
    std::vector<int> dist(grafo.V(), INT_MAX);
    IndexPQ<int> pq(grafo.V());

    dist[origen] = 0;
    pq.push(origen, 0);

    while (!pq.empty()) {
        int v = pq.top().elem; pq.pop();
        for (auto& a : grafo.ady(v)) {
            int w = a.otro(v);
            if (dist[w] > dist[v] + a.valor()) {
                dist[w] = dist[v] + a.valor(); ult[w] = a;
                pq.update(w, dist[w]);
            }
        }
    }

    return dist[destino];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C; std::cin >> N >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> grafo(N);

    for (int i = 0; i < C; ++i) {
        int v, w, c; std::cin >> v >> w >> c;
        --v; --w;
        grafo.ponArista({ v, w, c });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int T; std::cin >> T;

    for (int j = 0; j < T; ++j) {
        int o, d; std::cin >> o >> d;
        --o; --d;
        // escribir la solución
        std::vector<Arista<int>> ult(grafo.V());
        int res = minPathDuringDelivery(grafo, o, d, ult);
        if (res != INT_MAX) {
            std::stack<int> pila;
            int v = d;
            while (v != o) {
                pila.push(v);
                v = ult[v].otro(v);
            }

            std::cout << res << ": " << (o + 1);
            while (!pila.empty()) {
                int w = pila.top(); pila.pop();
                std::cout << " -> " << (w + 1);
            }
            std::cout << '\n';
        }
        else {
            std::cout << ERROR_MSG << '\n';
        }
    }

    std::cout << "---\n";

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
