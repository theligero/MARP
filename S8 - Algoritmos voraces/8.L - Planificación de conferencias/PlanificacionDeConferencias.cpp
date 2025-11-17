/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <cstdint>
#include <list>
#include <vector>
#include <queue>

/*@ <answer>
* El problema se resuelve guardando las conferencias en una lista con su id,
* hora de inicio y hora de fin. En primer lugar, se ordena la lista por hora
* de inicio (y, en caso de empate, por hora de fin e id), lo que supone un
* coste O(N * log(N)), siendo N el número de conferencias.
*
* A continuación se recorre la lista una sola vez manteniendo una cola de
* prioridad de salas, ordenada por la hora de finalización de la última
* conferencia asignada en cada sala. Para cada conferencia se consulta la
* sala que termina antes y se decide si se puede reutilizar (si ya ha
* acabado) o si es necesario abrir una sala nueva. Cada operación de
* inserción/extracción en la cola de prioridad tiene coste O(log N), de modo
* que este recorrido completo es O(N * log(N)).
*
* Por lo tanto, la complejidad total del algoritmo viene dominada por la
* ordenación inicial y el uso de la cola de prioridad, siendo en conjunto
* O(N * log(N)), donde N es el número de conferencias.
@ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct conference {
    uint32_t id;
    uint32_t begin;
    uint32_t end;

    bool operator<(const conference& other) const {
        if (begin == other.begin) {
            if (end == other.end) {
                return id < other.id;
            }
            else return end < other.end;
        }
        return begin < other.begin;
    }
};

struct room {
    uint32_t roomID;
    uint32_t end;

    bool operator<(const room& other) const {
        if (end == other.end) {
            return roomID > other.roomID;
        }
        else return end > other.end;
    }
};


int minNumberOfClassrooms(const std::list<conference>& conferences,
    std::vector<uint32_t>& classroom, const uint32_t& N) {

    auto it = conferences.cbegin();
    int acc = 0;

    std::priority_queue<room> classroomsUsed;

    while (it != conferences.cend()) {
        room newRoom;
        if (classroomsUsed.empty() || // si no tengo salas disponibles "de reserva"
            (*it).begin < classroomsUsed.top().end) { // o si la clase más "óptima" no termina en hora
            ++acc; // subo el acumulador
            newRoom.roomID = acc;
        }
        else { // en caso contrario
            newRoom = classroomsUsed.top(); classroomsUsed.pop();
        }
        newRoom.end = (*it).end;
        classroom[(*it).id] = newRoom.roomID;
        classroomsUsed.emplace(newRoom);
        ++it;
    }
    
    return acc;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    uint32_t N;

    std::cin >> N;

    if (N == 0)
        return false;

    std::list<conference> conferences;

    for (uint32_t i = 0; i < N; ++i) {
        conference aux;
        aux.id = i;
        std::cin >> aux.begin >> aux.end;
        conferences.push_back(aux);
    }

    std::vector<uint32_t> classroom(N, 0);

    // resolver el caso posiblemente llamando a otras funciones
    conferences.sort();
    // escribir la solución
    std::cout << minNumberOfClassrooms(conferences, classroom, N) << '\n';

    for (uint32_t j = 0; j < N; ++j) {
        std::cout << classroom[j] << ' ';
    }

    std::cout << '\n';

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
