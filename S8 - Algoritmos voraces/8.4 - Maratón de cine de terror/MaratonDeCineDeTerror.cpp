/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <cstdint>
#include <list>
#include <string>
#include <algorithm>

/*@ <answer>
* El problema se plantea de la siguiente forma: tenemos unas sesiones de cine 
* que vamos colocando en una lista (con estructura interna personalizada) de tal
* manera que se vayan ordenando no tanto por el orden en el que inician sino
* en el que terminan, de tal manera que se pueda maximizar el número de sesiones
* que se pueden ver en total (con coste O(N * log(N)), siendo N el número de sesiones
* que hay disponibles). A continuación, suponemos que la primera sesión (si es
* que hay) la va a ver sí o sí, y vamos iterando la lista con dos iteradores:
* uno con la sesión que ya hemos visto y otro con la posible futura sesión que
* vamos a ver. En este caso, ese recorrido sería de coste O(N), siendo N el número
* de sesiones de cine disponibles. Sin embargo, el coste total del problema sería
* del orden O(N * log(N)).
 @ </answer> */

struct movieSession { // estructura de sesión de peli
    uint32_t D;
    uint8_t H;
    uint8_t M;

    bool operator<(const movieSession& other) const {
        if (D == other.D) {
            if (H == other.H) return M < other.M;
            else return H < other.H;
        }
        else return D < other.D;
    }

    bool operator==(const movieSession& other) const {
        return D == other.D && H == other.H && M == other.M;
    }

    bool operator<=(const movieSession& other) const {
        if (D == other.D) {
            if (H == other.H) return M <= other.M;
            else return H <= other.H;
        }
        else return D <= other.D;
    }

    movieSession operator+(uint32_t dur) const {
        movieSession otherSession;
        otherSession.M = (M + dur) % 60;
        otherSession.H = (H + (M + dur) / 60) % 24;
        otherSession.D = (D + (H + (M + dur) / 60) / 24);

        return otherSession;
    }
};

struct cinemaSession { // estructura de sesión y duración de la peli
    movieSession S;
    uint32_t D;

    bool operator<(const cinemaSession& other) const {
        movieSession thisEnd = S + D;
        movieSession otherEnd = other.S + other.D;

        if (thisEnd == otherEnd) {
            return S < other.S;
        }
        else return thisEnd < otherEnd;
    }

    bool operator==(const cinemaSession& other) const {
        return S == other.S && D == other.D;
    }
};


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int maxNumberOfFilms(const std::list<cinemaSession>& cinema) {
    auto itCurrentSession = cinema.begin(); // asigno el iterador actual al inicio
    auto itNextSession = itCurrentSession; // y el siguiente al actual
    ++itNextSession; // y avanzo una posición

    int acc = itCurrentSession == cinema.end() ? 0 : 1; // si hay peli(s) aumento el acumulador en uno

    while (itNextSession != cinema.end()) { // mientras que no llegue al final
        // si me da tiempo a ir a la siguiente sesión
        if ((*itCurrentSession).S + (*itCurrentSession).D + 10 <= (*itNextSession).S) {
            ++acc; // aumento mi acumulador
            itCurrentSession = itNextSession; // asigno mi actual a mi siguiente
            ++itNextSession; // y avanzo el iterador siguiente
        } // voy buscando una sesión que me encaje con la anterior
        else { // en caso contrario
            ++itNextSession; // solo avanzo el iterador siguiente
        }
    }

    return acc; // devuelvo el acumulado
}

bool resuelveCaso() {
    // leer los datos de la entrada
    uint32_t N;
    std::cin >> N;

    if (N == 0) return false;

    std::list<cinemaSession> cinema;
    std::string aux;

    char sep = ':';

    for (int i = 0; i < N; ++i) {
        cinemaSession newSession;

        std::cin >> newSession.S.D;

        std::cin >> aux;

        newSession.S.H = std::stoi(aux.substr(0, 2));
        newSession.S.M = std::stoi(aux.substr(3, 2));

        std::cin >> newSession.D;

        cinema.push_back(newSession);
    }

    cinema.sort();

    // resolver el caso posiblemente llamando a otras funciones
    std::cout << maxNumberOfFilms(cinema) << std::endl;

    // escribir la solución

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