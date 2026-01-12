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

const std::string ERROR_MSG = "Imposible";

/*@ <answer>
* La autonomía del coche y sus posibles desplazamientos a lo largo
* de las distintas ciudades se plantea como un grafo valorado y no
* dirigido en el que cada ciudad representa un vértices y las
* carreteras que interconectan las ciudades como aristas. Para el
* problema, además incluiremos la estructura de las colas de prioridad
* para almacenar las aristas por coste mínimo y los conjuntos disjuntos
* para, durante el recorrido del árbol de recubrimiento mínimo, poder
* verificar que no estamos generando un ciclo.
* 
* Toda esta operación supondrá un coste en el orden O(A * log(A)), siendo
* A el número de aristas totales del grafo valorado. Además, tendremos
* una complejidad en espacio adicional en el orden O(A).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int howLongDoesBatteryLast(GrafoValorado<int>& grafo) {
    int coste = INT_MIN;
    std::vector<Arista<int>> _ARM;

    PriorityQueue<Arista<int>> pq(grafo.aristas());
    ConjuntosDisjuntos cjtos(grafo.V());

    while (!pq.empty()) {
        auto a = pq.top(); pq.pop();
        int v = a.uno(); int w = a.otro(v);
        if (!cjtos.unidos(v, w)) {
            cjtos.unir(v, w);
            _ARM.push_back(a); 
            if (coste < a.valor()) coste = a.valor();
            if (_ARM.size() == grafo.V() - 1) return coste;
        }
    }

    return INT_MIN;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M; std::cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> grafo(N);

    for (int i = 0; i < M; ++i) {
        int v, w, c; std::cin >> v >> w >> c;
        --v; --w;
        grafo.ponArista({ v, w, c });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int length;
    if (N == 1) length = 0;
    else length = howLongDoesBatteryLast(grafo);

    // escribir la solución
    std::string sol = (length != INT_MIN) ? std::to_string(length) : ERROR_MSG;
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
