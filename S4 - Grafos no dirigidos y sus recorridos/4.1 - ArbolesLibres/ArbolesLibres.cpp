/*@ <authors>
 * Ignacio Ligero Martín - MARP32
 *@ </authors> */

#include <iostream>
#include <fstream>

#include "Grafo.h"

/*@ <answer>
* El problema abarca un caso donde existe un grafo no dirigido y hay que
* averiguar si todos los vértices están conectados entre sí de manera que
* se pueda hacer un camino independientemente del vértices que marque el
* punto de partida. Por lo tanto, estamos ante un problema con complejidad
* en el orden O(V + A), siendo V el número de vértices del propio grafo y A
* el número de aristas de éste.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void esArbolLibre(const Grafo& gr, std::vector<bool>& visit,
	int& numVer, int s) {
	visit[s] = true;
	++numVer;

	for (auto& e : gr.ady(s)) {
		if (!visit[e]) {
			esArbolLibre(gr, visit, numVer, e);
		}
	}
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, N;

	std::cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo gr(V);

	std::cin >> N;
	int a, b;

	for (int i = 0; i < N; ++i) {
		std::cin >> a >> b;
		gr.ponArista(a, b);
	}

	bool noEsAclicico = gr.A() != gr.V() - 1;

	if (!noEsAclicico) {
		// resolver el caso posiblemente llamando a otras funciones
		int numVer = 0;
		std::vector<bool> visitados(V, false);
		std::vector<int> anterior(V, -1);

		esArbolLibre(gr, visitados, numVer, 0);

		// escribir la solución
		std::string sol = (numVer == V) ? "SI" : "NO";
		std::cout << sol << '\n';
	}
	else {
		std::cout << "NO" << '\n';
	}

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
