/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <list>
#include <queue>

#include "Digrafo.h"

/*@ <answer>
* Las tareas a resolver se plantean como vértices de un grafo, y
* las "dependencias" de las propias tareas son grafos dirigidos en
* el sentido de la próxima tarea.
* 
* Para resolver el problema se contará varias dos varibles importantes:
* la primera es el digrafo original, que se lee por la entrada estándar;
* luego tenemos el digrafo inverso para tener las dependencias, que más
* adelante se utilizará para tener un vector de tamaño N (como los
* vértices) con el número de dependencias pendientes, junto a otro vector
* clásico en este tipo de problemas de también tamaño N de booleanos que
* tenga los nodos ya visitados.
* 
* Este problema, dado que se realiza a través de una pila recorriendo la
* totalidad del grafo, se trata de un problema de complejidad O(V + A),
* siendo V el número de vértices totales en el digrado y A el número de
* aristas pertenecientes a dicho digrafo.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

std::list<int> listOfTasks(const Digrafo& digrafo,
    const Digrafo& digrafoInv, std::vector<int>& indeg,
    std::vector<bool>& visited) {

    std::list<int> sol;
    std::queue<int> cola;

    for (int i = 0; i < indeg.size(); ++i) {
        if (indeg[i] == 0) cola.push(i);
    }

    while (!cola.empty()) {
        int v = cola.front(); cola.pop();
        if (!visited[v]) {
            visited[v] = true;
            sol.push_back(v);
            for (auto& w : digrafo.ady(v)) {
                --indeg[w];
                if (indeg[w] == 0) cola.push(w);
            }
        }
        else {
            if (v < indeg.size() - 1) cola.push(v + 1);
        }
    }

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N; std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo digrafo(N);

    int M; std::cin >> M;

    for (int i = 0; i < M; ++i) {
        int v, w; std::cin >> v >> w;
        --v; --w;
        digrafo.ponArista(v, w);
    }

    Digrafo digrafoInv = digrafo.inverso();

    std::vector<int> indeg(N);
    std::vector<bool> visited(N, false);

    for (int i = 0; i < N; ++i) {
        indeg[i] = digrafoInv.ady(i).size();
    }

    // resolver el caso posiblemente llamando a otras funciones
    std::list<int> sol = listOfTasks(digrafo, digrafoInv, indeg, visited);

    // escribir la solución
    if (sol.size() != N) std::cout << "IMPOSIBLE\n";
    else {
        while (!sol.empty()) {
            std::cout << sol.front() + 1 << ' ';
            sol.pop_front();
        }
        std::cout << '\n';
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
