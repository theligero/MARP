/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>
* El problema se plantea como un grafo dirigido valorado e inverso
* donde se representan las distintas celdas donde, potencialmente,
* estarán ubicados los ratones como vértices y los "pasadizos" que
* conectan las celdas como las aristas dirigidas. Dado que queremos
* saber si va a dar tiempo a que los ratones lleguen a la salida
* antes de un tiempo determinado, lo más lógico será construir el
* digrafo inverso a partir de la información dada y así poder
* resolver el problema de manera más sencilla y sin hacer cálculos
* extra. Durante el propio recorrido del digrafo inverso, se tiene
* la posición origen (que en este caso es la salida) y el tiempo
* máximo que se marca como límite para llegar a las distintas celdas.
* En caso de llegar y efectivamente cumplir con la condición del
* tiempo, entonces sumamos uno al número de casillas totales que
* cumplen la condición.
* 
* La operación, por tanto, se refleja como algo de coste O(A * log(A)),
* siendo A el número de aristas que conforman el grafo y en espacio
* adicional de O(V), siendo V el número de vértices (o, en este caso,
* celdas) que conforman todo el laberinto.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int howManyMousesWouldWin(DigrafoValorado<int>& digrafo, const int& origen,
    const int& tiempo) {

    IndexPQ<int> pq(digrafo.V());
    std::vector<int> dist(digrafo.V(), INT_MAX);
    std::vector<bool> visited(digrafo.V(), false);

    dist[origen] = 0;
    visited[origen] = true;
    pq.push(origen, 0);
    int cont = 0;

    while (!pq.empty()) {
        int u = pq.top().elem; pq.pop();
        for (auto& a : digrafo.ady(u)) {
            int v = a.desde(), w = a.hasta();
            if (dist[w] > dist[v] + a.valor()) {
                dist[w] = dist[v] + a.valor();
                pq.update(w, dist[w]);
                if (!visited[w] && dist[w] <= tiempo) {
                    visited[w] = true;
                    ++cont;
                }
            }
        }
    }

    return cont;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, S, T, P; std::cin >> N >> S >> T >> P;

    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> digrafo(N);

    for (int i = 0; i < P; ++i) {
        int A, B, seg; std::cin >> A >> B >> seg;
        --A; --B;
        digrafo.ponArista({ B, A, seg });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int origen = S - 1;
    int mouses = howManyMousesWouldWin(digrafo, origen, T);

    // escribir la solución
    std::cout << mouses << '\n';

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
