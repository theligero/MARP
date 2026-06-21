/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <climits>
#include <iostream>
#include <fstream>
#include <vector>

/*@ <answer>
* El problema se plantea como un vector de elementos de tamaño P + 1,
* donde cada una de las posiciones del vector representa el número
* mínimo de dardos que son necesarios para llegar a dicha puntuación.
* De cara a su cálculo, se establecen (menos el primero, cero, que es
* cero) todos a infinito, para a continuación hacer un recorrido lineal
* incremental en base a los valores que llegan de entrada de los datos
* de los valores. A continuación, se hace un recorrido lineal desde el
* valor recibido hasta P (la puntuación) para comparar en caso de ser
* posible si la puntuación que se pudiera tener ahora es factible y se
* puede cambiar con la versión mínima registrada anteriormente. De ésta
* forma, se registra en P, al igual que en el resto de casos, el número
* mínimo de dardos requeridos para llegar a esa puntuación en base a
* las puntuaciones recibidas.
* 
* Por tanto, estamos ante un problema con una complejidad en el orden de
* O(P*S), siendo P el número de la puntuación deseada y S el número de
* las puntuaciones a evaluar en cada uno de los casos. Por contra, en
* el caso de coste en espacio, este problema tiene un coste de O(P), pues
* solo se requiere un vector para evaluar dichas condiciones durante
* el recorrido.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada
    int P, S; std::cin >> P >> S;
    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> min_dardos(P + 1, INT_MAX);
    std::vector<int> sectores(S);
    min_dardos[0] = 0;

    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < S; ++i) {
        int valor; std::cin >> valor;
        sectores[i] = valor;
        for (int j = valor; j <= P; ++j) {
            if (min_dardos[j - valor] != INT_MAX) {
                min_dardos[j] = std::min(min_dardos[j], 1 + min_dardos[j - valor]);
            }
        }
    }

    // escribir la solución
    if (min_dardos[P] != INT_MAX) {
        std::cout << min_dardos[P] << ':';

        int act = P;
        while (act > 0) {
            for (int i = S - 1; i >= 0; --i) {
                int valor = sectores[i];
                if (act - valor >= 0 && min_dardos[act] == 1 + min_dardos[act - sectores[i]]) {
                    act -= sectores[i];
                    std::cout << ' ' << sectores[i];
                    break;
                }
            }
        }

        std::cout << '\n';
    }
    else {
        std::cout << "Imposible\n";
    }

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
