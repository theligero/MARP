/*@ <authors>
* MARP32 Ignacio Ligero Martín
* @ </authors> */

#include <iostream>
#include <fstream>
#include <list>

/*@ <answer>
* La complejidad de este problema reside principalmente en la ordenación
* de las listas que se devuelven por parte del enunciado (pues estas
* no se hayan ordenadas). Para ello, insertamos los valores en una lista
* de enteros y las ordenamos. Una vez terminado este proceso, vamos comparando
* por iteradores de uno en uno si nuestro ejército aliado (ordenado de menor
* a mayor) podrá hacer frente al ejército enemigo distribuido por las
* distintas ciudades (también ordenado de menor a mayor). Si se puede combatir,
* avanzamos una posición de ambas listas; en caso contrario, solo avanzamos el
* iterador de los aliados. La comprobación termina cuando se ha llegado al final
* de alguna de las listas (muy posiblemente la de los aliados). Por lo tanto, dado
* que la complejidad de ordenar los elementos de la lista es de tipo O(N * log(N))
* y el recorrido posterior es de tipo O(N), podremos afirmar que el problema
* es de complejidad O(N * log(N)), siendo N el número de batallones (aliados y
* enemigos).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int maxNumOfVictoriousCities(const std::list<int>& allies, const std::list<int>& enemies) {
    int acc = 0;
    auto itEnemies = enemies.cbegin(); // colocamos iterador de la lista enemigos
    auto itAllies = allies.cbegin(); // e iterador de la lista aliados

    while (itEnemies != enemies.cend() && itAllies != allies.cend()) { // mientras no lleguemos al final de alguna
        if ((*itAllies) >= (*itEnemies)) { // si mi iterador aliados es mayor que mi iterador enemigos
            ++acc;
            ++itEnemies;
            ++itAllies;
        } // avanzamos una posición de ambas listas y sumamos una "victoria"
        else { // en caso contrario
            ++itAllies;
        } // solo avanzamos el iterador aliados y probamos de nuevo
    }

    return acc;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;

    std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    std::list<int> enemies; // número de efectivos enemigos en las ciudades
    std::list<int> allies; // número de efectivos aliados en las ciudades

    int aux;

    for (int i = 0; i < N; ++i) { // lectura de efectivos enemigos
        std::cin >> aux;
        enemies.push_back(aux);
    }

    for (int j = 0; j < N; ++j) { // lectura de efectivos aliados
        std::cin >> aux;
        allies.push_back(aux);
    }

    enemies.sort(); // ordenamos de menor a mayor la lista enemigos
    allies.sort(); // y la lista aliados

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    std::cout << maxNumOfVictoriousCities(allies, enemies) << std::endl;

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
