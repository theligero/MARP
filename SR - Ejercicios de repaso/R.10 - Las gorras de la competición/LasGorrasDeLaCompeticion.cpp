/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <cstdint>
#include <iostream>
#include <fstream>
#include <queue>

/*@ <answer>
* El problema se plantea como una cola de prioridad de mínimos donde
* cada equipo es insertado en un struct con dos parámetros (su id, y
* el número de aficionados que conforman el equipo). Se insertan en
* primera instancia todos los aficionados dentro de la cola de prioridad
* y posteriormente se extraen de ellas dos equipos para compararlos y
* añadir al montículo el "nuevo" equipo que se conforma con los aficionados
* del equipo perdedor. De esta forma, añadiendo un contador para llevar
* la cuenta del número mínimo de gorras necesarios, estamos ante un
* problema de tipo logarítmico por la propia naturaleza de la cola de
* prioridad y el uso de montículos, siendo esta de O(N * log(N)), siendo
* N el número de equipos que conforman el campeonato.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct equipo {
    int id;
    int64_t num_aficionados;

    bool operator>(const equipo& other) const {
        if (num_aficionados == other.num_aficionados) {
            return id > other.id;
        }
        else {
            return num_aficionados > other.num_aficionados;
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N; std::cin >> N;
    if (N == 0)
        return false;

    std::priority_queue<equipo, std::vector<equipo>, std::greater<equipo>> equipos;

    for (int i = 0; i < N; ++i) {
        int s; std::cin >> s;
        equipos.push({ i, s });
    }

    // resolver el caso posiblemente llamando a otras funciones
    int64_t acc = 0;
    while (equipos.size() >= 2) {
        equipo a = equipos.top(); equipos.pop();
        equipo b = equipos.top(); equipos.pop();
        b.num_aficionados += a.num_aficionados;
        acc += b.num_aficionados;
        equipos.push(b);
    }

    // escribir la solución
    std::cout << acc << '\n';

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
