/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <climits>

#include "Grafo.h"

/*@ <answer>
* El problema plantea una matriz de píxeles donde hay una serie de manchas
* a lo largo de la pantalla, y se pide ubicar tanto el número de manchas
* totales (es decir, el conjunto de píxeles negros) como la propia mancha
* con mayor número de píxeles de color negro. Para esto, se utiliza la
* representación de grafos que se da de la asignatura para crear un grafo
* no dirigido en el que cada píxel tiene una conexión (o, en el homólogo
* de los grafos, una arista). Por ello, para averiguar tanto el número de
* manchas como el número máximo de píxeles por mancha se ha de hacer un
* recorrido lineal por el número de elementos del grafo sumado a sus
* aristas donde, potencialmente, esté un píxel negro. Por lo tanto, si
* entendemos los píxeles como P y las conexiones como P, el problema
* tiene una complejidad en el orden O(P + C).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void largestSpot(const Grafo& matrix, std::vector<bool>& colors,
    std::vector<bool>& visited, int i, int& numSpots) {
    ++numSpots;
    visited[i] = true;

    for (auto& e : matrix.ady(i)) {
        if (colors[e] && !visited[e]) {
            largestSpot(matrix, colors, visited, e, numSpots);
        }
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int F, C; std::cin >> F >> C;

    if (!std::cin)  // fin de la entrada
        return false;
    
    int numVertex = F * C;
    Grafo matrix(numVertex);

    std::vector<bool> colors(numVertex, false);
    std::vector<bool> visited(numVertex, false);

    for (int i = 0; i < F - 1; ++i) {
        int result, below;
        std::string line;
        std::cin >> line;
        for (int j = 0; j < C - 1; ++j) {
            result = (i * C) + j;
            below = ((i + 1) * C) + j;
            int beside = (i * C) + (j + 1);
            colors[result] = (line[j] == '#');
            matrix.ponArista(result, below); // arista con el de abajo
            matrix.ponArista(result, beside); // arista con el de la derecha
        }
        result = (i * C) + (C - 1);
        below = ((i + 1) * C) + (C - 1);
        colors[result] = (line[C - 1] == '#');
        matrix.ponArista(result, below); // arista con el de abajo
    }

    std::string line; std::cin >> line;

    for (int k = 0; k < C - 1; ++k) {
        int result = ((F - 1) * C) + k;
        int beside = ((F - 1) * C) + (k + 1);
        colors[result] = (line[k] == '#');
        matrix.ponArista(result, beside); // arista con el de la derecha
    }

    colors[numVertex - 1] = (line[C - 1] == '#');

    // resolver el caso posiblemente llamando a otras funciones
    int currSpots = 0;
    int maxNumSpots = 0;
    int numSpots = 0;
    for (int i = 0; i < numVertex; ++i) {
        if (colors[i]) { // comprobar primero que es mancha
            if (!visited[i]) { // y luego comprobar que no ha sido visitado
                currSpots = 0;
                largestSpot(matrix, colors, visited, i, currSpots);
                maxNumSpots = std::max(maxNumSpots, currSpots);
                ++numSpots;
            }
        }
    }

    // escribir la solución
    std::cout << numSpots << ' ' << maxNumSpots << '\n';

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
