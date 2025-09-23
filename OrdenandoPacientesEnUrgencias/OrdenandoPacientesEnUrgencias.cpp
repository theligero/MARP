/*@ <authors>
 *
 * Ignacio Ligero Martín - MARP32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

/* @ <answer>
* Primero pongo en mi variable N el número que me llega a través
* de la entrada. En caso de ser mayor que 0, creo una cola de infoPaciente
* que almacena el nombre del paciente, la gravedad del mismo y la marca de tiempo
* para su posible comparación en caso de misma gravedad en cola. Luego hago un for
* por el número de elementos: si es A hago un top() y pop() y me quedo con el valor
* de la cola y lo imprimo por pantalla, mientras que si es una I creo un infoPaciente
* con los datos de entrada y voy sumando a mi acumulador de num_paciente para mantener
* el orden de llegada de éstos. Por lo tanto, como la cola de prioridad es logarítmica
* en lo que respecta a su inserción y se hace un recorrido lineal del número de casos
* a tratar, estamos ante un caso de coste O(N*log(N)).
@ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct infoPaciente {
	char nombre[21];
	int gravedad;
	int marca_tiempo;
};

bool operator<(const infoPaciente& a, const infoPaciente& b) {
	if (a.gravedad == b.gravedad) return a.marca_tiempo > b.marca_tiempo;
	else return a.gravedad < b.gravedad;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	if (!(std::cin >> N)) return false;
	if (N == 0) return false;

	std::priority_queue<infoPaciente> cola;
	int num_paciente = 1;

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < N; ++i) {
		char c; std::cin >> c;
		if (c == 'I') {
			infoPaciente nuevoPaciente;
			std::cin >> nuevoPaciente.nombre;
			std::cin >> nuevoPaciente.gravedad;
			nuevoPaciente.marca_tiempo = num_paciente++;
			cola.push(nuevoPaciente);
		}
		else if (c == 'A') {
			infoPaciente aux = cola.top(); cola.pop();
			std::cout << aux.nombre << '\n';
		}
	}

	// escribir la solución
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
