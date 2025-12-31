/* @ <authors>
* Ignacio Ligero Martín - MARP32
* @</authors> */

#include <iostream>
#include <fstream>

#include "Grafo.h"

/*@ <answer>
* El problema propuesto de los grafos bipartitos plantea la condición de
* tener cada uno de los nodos del grafos con un valor distinto a sus
* nodos adyancentes. Por lo tanto, lo que habría que hacer es un recorrido
* lineal en forma de asignación de cada uno de los nodos y, durante dicha
* asignación, asegurarse de que el (o los) adyacente(s) al nodo actual
* tienen un valor distinto al nodo actual. Esto plantea un problema
* de complejidad O(V + A), siendo V el número de vértices del grafo y
* A el número de aristas que dicho grafo posee.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool isBipartite(const Grafo& gr, std::vector<bool>& visited, 
	std::vector<int>& type, int v, int currType) {
	visited[v] = true;
	type[v] = currType;

	for (auto& e : gr.ady(v)) {
		if (!visited[e]) {
			int newType = (currType == 0) ? 1 : 0;
			if (!isBipartite(gr, visited, type, e, newType))
				return false;
		}
		else {
			if (type[e] == currType) return false;
		}
	}

	return true;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;

	std::cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo gr(V);

	std::cin >> A;

	for (int i = 0; i < A; ++i) {
		int v, w;
		std::cin >> v >> w;
		gr.ponArista(v, w);
	}

	// resolver el caso posiblemente llamando a otras funciones
	std::vector<int> type(V, -1);
	std::vector<bool> visited(V, false);

	bool ok = true;
	int it = 0;

	while (it < V && ok) {
		if (!visited[it]) ok = isBipartite(gr, visited, type, it, 0);
		++it;
	}

	// escribir la solución
	std::string sol = (ok) ? "SI" : "NO";

	std::cout << sol << '\n';

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
