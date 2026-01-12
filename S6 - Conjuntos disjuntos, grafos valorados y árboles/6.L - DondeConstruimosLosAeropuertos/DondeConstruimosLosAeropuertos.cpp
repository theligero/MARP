/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>

#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"
#include "PriorityQueue.h"

/*@ <answer>
* El problema se plantea como un grafo no dirigido valorado en el
* que cada vértice representa una localidad y las aristas son las
* carreteras que unen dichas localidades con el coste de construcción
* asociado a ellas. Además, se sabe el coste fijo de construir un
* aeropuerto. Con esta información en mano, la forma óptima de resolver
* un problema así es tener primero, como siempre, construyendo el
* grafo valorado en base a la información que nos llega. A continuación,
* lo que habría que hacer es asumir de primeras que el coste total
* va a ser a un aeropuerto por localidad. Como sabemos que eso es algo
* "surrealista", vamos recorriendo el grafo de costes de carreteras y
* viendo si nos sale más a cuenta quitar un aeropuerto de la ecuación
* o no. Una vez tengamos ese cálculo obtenido, lo devolvemos junto al
* número de aeropuertos que al final sí que vamos a llegar a necesitar
* junto al número imprescindible de carreteras que unan toda la región.
* 
* Este problema tiene una complejidad, por tanto, en el orden de
* O(A * log(A)), siendo A el número de aristas totales que conforman
* el grafo. Además, con respecto a la complejidad en espacio, tenemos
* que este problema requerirá un espacio adicional de O(A) para los
* distintos cálculos mencionados anteriormente.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int totalRoadSpending(GrafoValorado<int>& grafo, int& num_cjtos,
    const int& airport_cost) {
    int cont = airport_cost * grafo.V();
    std::vector<Arista<int>> _ARM;

    PriorityQueue<Arista<int>> pq(grafo.aristas());
    ConjuntosDisjuntos cjtos(grafo.V());

    while (!pq.empty()) {
        auto a = pq.top(); pq.pop();
        int v = a.uno(); int w = a.otro(v);
        if (!cjtos.unidos(v, w) && airport_cost > a.valor()) {
            cjtos.unir(v, w);
            _ARM.push_back(a);
            cont -= airport_cost;
            --num_cjtos;
            cont += a.valor();
            if (_ARM.size() == grafo.V() - 1) return cont;
        }
    }

    return cont;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M, A; std::cin >> N >> M >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> grafo(N);

    for (int i = 0; i < M; ++i) {
        int X, Y, C; std::cin >> X >> Y >> C;
        --X; --Y;
        grafo.ponArista({ X, Y, C });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int num_cjtos = N;
    int coste_total = totalRoadSpending(grafo, num_cjtos, A);

    // escribir la solución
    std::cout << coste_total << ' ' << num_cjtos << '\n';

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
