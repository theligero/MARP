/* @ <authors>
* Ignacio Ligero Martín - MARP32
* @ </authors> */

#include <iostream>
#include <fstream>

#include "IndexPQ.h"

/*@ <answer>
* El problema pide una cola de prioridad variable donde se irán almacenando
* los distintos resultados de los diversos países que participan en el festival.
* Por lo tanto, la solución estará en el orden O(N * log(P)), siendo P el número
* de participantes del festival y N el número de eventos pues, al ser una cola de 
* prioridad personalizada, la forma de ordenación de los elementos será a través de 
* un montículo. Luego, con respecto al espacio necesitado, se requerirá algo del orden O(P).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, points;
	std::string event;

	std::cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	IndexPQ<std::string, int, std::greater<int>> eurovision;

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < N; ++i) {
		std::cin >> event;
		if (event == "?") {
			auto const& top = eurovision.top();
			std::cout << top.elem << " " << top.prioridad << std::endl;
		}
		else {
			std::cin >> points;
			if (eurovision.exists(event)) {
				eurovision.update(event, points);
			}
			else {
				eurovision.push(event, points);
			}
		}
	}

	std::cout << "---" << std::endl;

	// escribir la solución

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
