/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <list>

/*@ <answer>
* El problema se resuelve colocando las distintas posiciones de los agujeros
* en una lista (aprovechando su orden creciente) para posteriormente ir
* recorriéndola con el valor de la longitud de la cinta en mente. Se hace
* por tanto un recorrido lineal de la lista tapando en primera instancia el
* primer agujero posible y averiguando si es posible que se tape algún agujero
* adicional. Por lo tanto, la solución del problema es de complejidad O(N), siendo
* N el número de posiciones de agujeros que hay en total.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int minNumOfPatches(const std::list<uint32_t>& holes, const int& tapeLenght) {
    int tapeUsed = 0;
    auto itList = holes.cbegin();

    while (itList != holes.cend()) { // mientras que no se hayan cubiertos todos los huecos
        ++tapeUsed;
        auto itList2 = itList;
        ++itList2;
        while (itList2 != holes.cend() && (*itList) + tapeLenght >= (*itList2)) {  // si tengo siguiente
            ++itList2;
        }
        itList = itList2;
    }
    
    return tapeUsed; // devuelve el número de trozos de cinta usados
}

bool resuelveCaso() {
    uint32_t N; // número de agujeros
    uint16_t L; // longitud de los parches

    // leer los datos de la entrada
    std::cin >> N >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    std::list<uint32_t> holes; // posición de los agujeros

    uint32_t lastElt = 0;

    for (uint32_t i = 0; i < N; ++i) {
        uint32_t currElt;
        std::cin >> currElt; 
        if (lastElt != currElt) // no insertamos dos veces el mismo elemento
            holes.push_back(currElt);
        lastElt = currElt;
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    std::cout << minNumOfPatches(holes, L) << std::endl;

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
