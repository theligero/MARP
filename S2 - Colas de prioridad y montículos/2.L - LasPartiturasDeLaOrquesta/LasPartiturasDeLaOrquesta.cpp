/*@ <authors>
 *
 * MARP32 Ignacio Ligero Martín
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;


/*@ <answer>
* En primer lugar hago un recorrido por el total de instrumentos para insertarlos
* en la cola de prioridad basada en mi struct de infoInstrumento (compuesto por los
* integrantes del grupo y el número de copias, que inicialmente es uno porque todos
* tienen que tener como mínimo una copia por grupo). A partir de ahí, luego hago un
* recorrido por P-N (que es el sobrante de partituras) y las reparto en los grupos
* que más desfavorecidos (véase los que tengan mayor ratio copias / integrantes). Por
* lo tanto, la solución me queda de complejidad O(P*log(N)), siendo P el número de
* partituras totales (recorrido lineal) y N el número de grupos que hay (recorrido
* logarítmico por la naturaleza de la cola de prioridad).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct infoInstrumento {
    int integrantes;
    int num_copias = 1;
};

bool operator>(const infoInstrumento& a, const infoInstrumento& b) {
    int a_prop = a.num_copias * b.integrantes;
    int b_prop = b.num_copias * a.integrantes;

    return a_prop > b_prop;
}

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    std::priority_queue<infoInstrumento, std::vector<infoInstrumento>,
        std::greater<infoInstrumento>> cola;

    for (int i = 0; i < N; ++i) {
        infoInstrumento aux;
        std::cin >> aux.integrantes;
        cola.push(aux);
        --P;
    }

    for (int j = 0; j < P; ++j) {
        infoInstrumento aux = cola.top();
        cola.pop();
        ++aux.num_copias;
        cola.push(aux);
    }

    infoInstrumento result = cola.top();
    int num_max = (result.integrantes + result.num_copias - 1) / result.num_copias;

    std::cout << num_max << '\n';

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
