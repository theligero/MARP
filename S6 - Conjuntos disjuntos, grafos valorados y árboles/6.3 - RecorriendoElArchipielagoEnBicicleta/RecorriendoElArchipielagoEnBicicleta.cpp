/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include <string>

#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"
#include "PriorityQueue.h"

const std::string ERROR_MSG = "No hay puentes suficientes";

/*@ <answer>
* El problema se plantea como un grafo no dirigido valorado en el
* que los vértices representan las distintas islas y las aristas
* los diferentes puentes que puede llegar a haber en el archipiélago.
* Se pide, por tanto, el coste mínimo de las obras para poder unir
* a todo el archipiélago con puente. Por lo tanto, usaremos varias
* estructuras de datos: una cola de prioridad que vaya almacenando
* todos las aristas por menor coste, un grafo valorado y una estructura
* de conjuntos disjuntos para verificar la propiedad de Kruskal (árbol
* de recubrimiento de coste mínimo).
* 
* Por ello, el problema tendrá una complejidad total en el orden
* O(A * log(A)), siendo A el número de aristas totales (o, en este caso,
* de puentes que unen el archipiélago), y con un coste de espacio
* adicional de O(A).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int minCostOfBridges(GrafoValorado<int>& grafo) {
    int coste = 0;
    std::vector<Arista<int>> _ARM;
    PriorityQueue<Arista<int>> pq(grafo.aristas());
    ConjuntosDisjuntos cjtos(grafo.V());

    while (!pq.empty()) {
        auto a = pq.top(); pq.pop();
        int v = a.uno(); int w = a.otro(v);
        if (!cjtos.unidos(v, w)) {
            cjtos.unir(v, w);
            _ARM.push_back(a); coste += a.valor();
            if (_ARM.size() == grafo.V() - 1) return coste;
        }
    }

    return INT_MAX;
}


bool resuelveCaso() {
    // leer los datos de la entrada
    int I; std::cin >> I;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> grafo(I);
    int P; std::cin >> P;

    for (int i = 0; i < P; ++i) {
        int v, w, c; std::cin >> v >> w >> c;
        --v; --w;
        grafo.ponArista({ v, w, c });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int value; 
    if (I == 1) value = 0; 
    else value = minCostOfBridges(grafo);
    std::string sol = (value != INT_MAX) ? std::to_string(value) : ERROR_MSG;

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