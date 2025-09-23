
/*@ <authors>
 *
 * Ignacio Ligero Martín - MARP32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct registro {
	int momento; // cuándo le toca
	int id; // identificador (se utiliza en caso de empate)
	int periodo; // tiempo entre consultas
};

bool operator<(const registro& a, const registro& b) {
	return b.momento < a.momento ||
		(a.momento == b.momento && b.id < a.id);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int32_t N;

	if (!(std::cin >> N)) return false;
	if (N == 0) return false;

	std::priority_queue<registro> cola;

	for (int i = 0; i < N; ++i) {
		int id_usu, periodo;
		std::cin >> id_usu >> periodo;
		cola.push({periodo, id_usu, periodo});
	}

	// resolver el caso posiblemente llamando a otras funciones
	int envios;
	std::cin >> envios;


	// escribir la solución
	while (envios > 0) {
		auto e = cola.top(); cola.pop();
		std::cout << e.id << '\n';
		e.momento += e.periodo;
		cola.push(e);
		--envios;
	}

	std::cout << "---\n";

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
