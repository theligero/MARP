/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>

#include "DigrafoValorado.h"
#include "IndexPQ.h"

const std::string& ERROR_MSG = "IMPOSIBLE";

/*@ <answer>
* El problema se plantea como un grafo dirigido valorado en el que
* cada vértice representa una página web (con un coste de carga
* asociado) y la arista representa el tiempo que se tarda de navegar
* de una página v a otra página w. Una vez recibidos los valores de
* carga de las páginas individuales así como el coste de navegación
* de una página a otra, habrá que averiguar cuál es el coste de ir
* desde la página "principal" (que entendemos que es la inicial que
* se proporciona) hasta la última. Esta búsqueda se hará mediante
* Dijsktra, que irá buscando las aristas más "convenientes" para
* llegar a la última página, además de añadirle al coste de cada una
* ellas lo que tarda la propia página en cargar.
* 
* Por tanto, viendo el problema en su conjunto, podemos afirmar que
* en lo que se refiere a la complejidad en tiempo estamos ante algo
* parecido a O(A * log(A)), siendo A el número de aristas valoradas
* dirigidas totales que conforman el grafo, y en cuanto a espacio
* adicional necesitaremos algo del estilo O(V).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int howLongDoesItTake(DigrafoValorado<int>& digrafo,
    const std::vector<int>& values, const int& origin,
    const int& dest) {

    std::vector<int> dist(digrafo.V(), INT_MAX);
    IndexPQ<int> pq(digrafo.V());

    dist[origin] = values[origin];
    pq.push(origin, 0);

    while (!pq.empty()) {
        int u = pq.top().elem; pq.pop();
        for (auto& a : digrafo.ady(u)) {
            int v = a.desde(), w = a.hasta();
            if (dist[w] > dist[v] + a.valor() + values[w]) {
                dist[w] = dist[v] + a.valor() + values[w];
                pq.update(w, dist[w]);
            }
        }
    }

    return dist[dest];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N; std::cin >> N;

    if (N == 0)
        return false;

    DigrafoValorado<int> digrafo(N);
    std::vector<int> values(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> values[i];
    }

    int M; std::cin >> M;
    for (int j = 0; j < M; ++j) {
        int origin, dest, coste; std::cin >> origin >> dest >> coste;
        --origin; --dest;
        digrafo.ponArista({ origin, dest, coste });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int total = howLongDoesItTake(digrafo, values, 0, N - 1);
    std::string sol = (total != INT_MAX) ? std::to_string(total) : ERROR_MSG;

    // escribir la solución
    std::cout << sol << '\n';

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
