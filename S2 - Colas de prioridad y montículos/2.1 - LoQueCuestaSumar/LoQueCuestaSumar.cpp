/*@ <authors>
 *
 * Ignacio Ligero Martín - MARP32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

/*@ <answer>
* Primero creo una cola de prioridad donde voy insertando
* valores de menor a mayor. Luego, después de haberlos insertado,
* voy cogiendo los dos elementos más bajos y los voy sumando, y
* guardo sus valores en una variable externa llamada sum (será lo
* que se imprima por pantalla). Una vez sumados, vuelvo a meter el valor
* en la cola y saco dos valores repitiendo lo anterior hasta dejar
* solo uno internamente. Por lo tanto, el coste de este problema es
* de tipo O(Nlog(N)).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	if (!(std::cin >> N)) return false;
	if (N == 0) return false;

	std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> cola;

	for (int i = 0; i < N; ++i) {
		int64_t M; std::cin >> M;
		cola.push(M);
	}

	// resolver el caso posiblemente llamando a otras funciones
	int64_t sum = 0;

	while (cola.size() > 1) {
		int64_t aux = cola.top(); cola.pop();
		aux += cola.top(); cola.pop();
		sum += aux;
		cola.push(aux);
	}

	// escribir la solución
	std::cout << sum << '\n';

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