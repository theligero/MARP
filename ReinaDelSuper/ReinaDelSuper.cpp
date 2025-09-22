
/*@ <authors>
 *
 * Ignacio Ligero Martín - MARP32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <list>

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct infoCliente {
	int pos; // posición en la cola
	int tiempo_est; // tiempo estimado de compra 
};

bool operator<(const infoCliente& a, const infoCliente& b) {
	return a.pos < b.pos;
}

struct infoCaja {
	int num_caja; // número de la caja
	int tiempo_total; // tiempo (por tramos) de apertura de cajas
};

bool operator<(const infoCaja& a, const infoCaja& b) {
	if (a.tiempo_total == b.tiempo_total) return a.num_caja < b.num_caja;
	else return a.tiempo_total < b.tiempo_total;
}

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C;

	if (!(std::cin >> N >> C)) return false;
	if (N == 0 && C == 0) return false;

	PriorityQueue<infoCaja> cajas;

	for (int k = 1; k <= N; ++k) {
		cajas.push({ k, 0 });
	}

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < C; ++i) {
		int aux; std::cin >> aux;
		infoCaja top = cajas.top(); cajas.pop();
		top.tiempo_total += aux;
		cajas.push(top);
	}

	// escribir la solución

	std::cout << cajas.top().num_caja << '\n';

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
