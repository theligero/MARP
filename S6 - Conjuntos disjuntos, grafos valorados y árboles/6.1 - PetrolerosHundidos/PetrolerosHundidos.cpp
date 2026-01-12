/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>

#include "ConjuntosDisjuntos.h"

/*@ <answer>
* El problema de los petroleros se plantea como una matriz
* representada linealmente, donde cada mancha es añadida a
* una matriz de igual tamaño formada por booleanos (verdadero
* si hay mancha y falso si no). Se recorre linealmente los datos
* recibidos por la entrada y se dibuja tal matriz, mientras se
* mantiene un entero que marca el cardinal "padre" con mayor
* extensión de mancha. A continuación, se hace el recorrido
* lineal de N elementos donde se ha ubicado coordendas exactas
* de dónde hay nueva mancha y se añade a la matriz, interpretando
* consecuentemente las nuevas hipotéticas manchas y/o ampliación
* de manchas anteriores, con el fin de cambiar el valor del entero
* que contiene la información de la ubicación de la mayor mancha.
* 
* Este problema, por tanto, si suponemos que S es el número total
* de celdas (conformada por F * C), K es el número de manchas total
* de la foto original y N es el número de nuevas manchas ubicadas en
* las nuevas fotografías, estamos ante algo con complejidad
* O(S + (K + N) * log*S).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void checkProximity(const int& pos, const int& F, const int& C,
    ConjuntosDisjuntos& cjtosDisjtos, const std::vector<bool>& isPolluted) {

    const int r = pos / C;
    const int c = pos % C;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            const int nr = r + dr;
            const int nc = c + dc;

            if (nr < 0 || nr >= F || nc < 0 || nc >= C) continue;

            const int npos = nr * C + nc;
            if (isPolluted[npos]) cjtosDisjtos.unir(pos, npos);
        }
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int F, C; std::cin >> F >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    int M = F * C; // número de celdas totales
    ConjuntosDisjuntos cjtosDisjtos(M);
    std::vector<bool> isPolluted(M, false);

    int largestSpot = -1;

    for (int j = 0; j < F; ++j) {
        for (int i = 0; i < C; ++i) {
            int pos = (C * j) + i;
            char c; std::cin >> c;
            if (c == '#') {
                isPolluted[pos] = true;
                checkProximity(pos, F, C, cjtosDisjtos, isPolluted);
                int father = cjtosDisjtos.buscar(pos);
                if (largestSpot == -1 || cjtosDisjtos.cardinal(father) > cjtosDisjtos.cardinal(largestSpot)) 
                    largestSpot = father;
            }
        }
    }

    if (largestSpot == -1) std::cout << 0 << ' ';
    else std::cout << cjtosDisjtos.cardinal(largestSpot) << ' ';

    // resolver el caso posiblemente llamando a otras funciones
    int N; std::cin >> N;

    for (int i = 0; i < N; ++i) {
        int y, x;
        std::cin >> y >> x;
        int pos = (y - 1) * C + (x - 1);
        isPolluted[pos] = true;
        checkProximity(pos, F, C, cjtosDisjtos, isPolluted);
        int father = cjtosDisjtos.buscar(pos);
        if (largestSpot == -1 || cjtosDisjtos.cardinal(father) > cjtosDisjtos.cardinal(largestSpot))
            largestSpot = father;

        // escribir la solución
        if (largestSpot == -1) std::cout << 0 << ' ';
        else std::cout << cjtosDisjtos.cardinal(largestSpot) << ' ';
    }

    std::cout << '\n';

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
