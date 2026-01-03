/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <climits>
#include <iostream>
#include <fstream>
#include <set>
#include <stack>
#include <string>

#include "Digrafo.h"

/*@ <answer>
* El problema se plantea como un grafo de los distintos restaurante
* que el petardo de Franco quiere visitar. Por ello, como dichos
* restaurantes se conectan a través de las calles de un único sentido
* (salvo que haya otra calle en dirección opuesta desde el otro restaurante),
* se plantea como un grafo dirigido. A continuación, la clave será tener dos
* grafos distintos: uno el original, que es que se lee a través de los
* casos de prueba, y uno invertido. Con ambos dos, ubicaremos todos los
* posibles restaurantes alcanzables, tanto desde la ida con el original
* como desde el destino como el inverso. Estas posiciones "alcanzables"
* se mantendrán en un vector de booleanos tanto del de ida como el de
* vuelta. Luego, se compararán una por una las posiciones para poder
* garantizar que si puedo ir hasta un punto cualquiera puedo llegar
* de vuelta y por tanto "alargar" el camino para el caudillo. Por tanto,
* este problema tendrá una complejidad en el orden O(Q * (NV + NA))
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

std::vector<bool> reachableRestaurants(const Digrafo& digrafo, 
    const int& origin, const int& dest, const int& size) {
    std::vector<bool> result(size, false);
    result[origin] = true;
    std::stack<int> pila; pila.push(origin);
    while (!pila.empty()) {
        int v = pila.top(); pila.pop();
        for (auto& w : digrafo.ady(v)) {
            if (!result[w]) {
                result[w] = true;
                pila.push(w);
            }
        }
    }

    return result;
}


int numOfStreets(const Digrafo& digrafo, const Digrafo& digrafoInv, 
    const int& size, const int& origen, const int& dest) {
    std::vector<bool> reachOrigin = reachableRestaurants(digrafo, origen, dest, size);
    std::vector<bool> reachDest = reachableRestaurants(digrafoInv, dest, origen, size);

    int cont = -2;

    for (int i = 0; i < size; ++i) {
        if (reachOrigin[i] && reachDest[i]) ++cont;
    }

    return cont;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int NV, NA; std::cin >> NV >> NA;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo digrafo(NV);

    for (int i = 0; i < NA; ++i) {
        int v, w; std::cin >> v >> w;
        --v; --w;
        digrafo.ponArista(v, w);
    }

    Digrafo digrafoInv = digrafo.inverso();

    // resolver el caso posiblemente llamando a otras funciones
    int Q; std::cin >> Q;

    // escribir la solución
    for (int j = 0; j < Q; ++j) {
        int origen, destino; std::cin >> origen >> destino;
        --origen; --destino;
        int result = numOfStreets(digrafo, digrafoInv, NV, origen, destino);
        std::string sol = (result != -2) ? std::to_string(result) : "IMPOSIBLE";
        std::cout << sol << '\n';
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
