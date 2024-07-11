// Ignacio Ligero Martín
// MARP17

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>


// función que resuelve el problema
int64_t resolver(std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> datos) {
    int64_t ac = 0;

    while (datos.size() >= 2) {
        int64_t a = datos.top(); datos.pop();
        int64_t b = datos.top(); datos.pop();
        int64_t c = a + b;
        datos.push(c);
        ac += c;
    }
    
    return ac;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (N == 0)
        return false;

    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> cola;
    int aux;

    for (int i = 0; i < N; ++i) {
        std::cin >> aux;
        cola.push(aux);
    }

    int64_t sol = resolver(cola);

    // escribir sol

    std::cout << sol << std::endl;

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
