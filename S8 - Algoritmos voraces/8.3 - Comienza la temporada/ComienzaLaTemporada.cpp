/*@ <authors>
* MARP32 Ignacio Ligero Martín
*@ </authors> */

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <stdint.h>

/* @ <answer>
* Este problema se resuelve de manera muy sencilla: primero
* se lee por parámetro tanto las camisetas disponibles como
* las camisetas que los jugadores piden de cara a la próxima
* temporada. Una vez hecho esto, se ordena (con complejidad
* O(N*log(N))) ambas listas y a continuación se llama a la
* función minNumberOfSportsKits() y, a través de un recorrido
* lineal (con complejidad O(N)) vamos asignando camisetas
* disponibles a jugadores sin camiseta. Por lo tanto, la
* complejidad de este problema estará en la línea de la
* ordenación de la lista, es decir, O(N * log(N)) siendo N
* el número de elementos de la mayor de las listas.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int minNumberOfSportsKits(const std::list<uint16_t>& wantedSizes, 
    const std::list<uint16_t>& sizesInPossession, const uint32_t& N) {
    auto itWanted = wantedSizes.cbegin(); // iterador de camisetas pedidas
    auto itInPoss = sizesInPossession.cbegin(); // iterador de camisetas en posesión

    int acc = 0; // empezamos con 0 camisetas asignadas

    while (itWanted != wantedSizes.cend() && // mientras que no llego
        itInPoss != sizesInPossession.cend()) { // al final de la(s) lista(s)
        if ((*itWanted) > (*itInPoss)) ++itInPoss;
        else if ((*itWanted) < (*itInPoss)) { // si mi talla es menor
            if ((*itWanted) + 1 == (*itInPoss)) { // y puedo "adaptarme"
                ++acc;
                ++itInPoss;
            } // avanzo el iterador de las que tengo y aumento el acumulador
            ++itWanted;
        } // avanzo sólo el iterador de las pedidas
        else { // en caso de ser iguales
            ++acc;
            ++itWanted;
            ++itInPoss;
        } // avanzo una posición ambas y sumo una a la camiseta asignada
    }

    return (N - acc); // devuelvo el número de pedidas menos el acumulado
}

bool resuelveCaso() {

    // leer los datos de la entrada
    uint32_t N, M;

    std::cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    uint16_t aux; // entero auxiliar de lectura

    std::list<uint16_t> wantedSizes; // camisetas pedidas
    std::list<uint16_t> sizesInPossession; // camisetas en posesión

    for (int i = 0; i < N; ++i) {
        std::cin >> aux;
        wantedSizes.push_back(aux);
    }

    for (int j = 0; j < M; ++j) {
        std::cin >> aux;
        sizesInPossession.push_back(aux);
    }

    wantedSizes.sort(); // ordenamos las pedidas
    sizesInPossession.sort(); // y las que tenemos

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    std::cout << minNumberOfSportsKits(wantedSizes, 
        sizesInPossession, N) << std::endl;

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