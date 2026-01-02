/*@ <authors>
 * MARP32 Ignacio Ligero Martín
 *@ </authors> */

#include <climits>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

/*@ <answer>
* El problema se plantea utilizando dos mapas no ordenados como forma
* de almacenamiento tanto de los actores como de las películas; luego,
* una vez se haya recorrido la totalidad de los casos de prueba, se
* almacenará un vector de tamaño V, siendo V el número de actores total,
* que mantendrá la información de cara a la búsqueda iterativa de nodos
* anteriores, siguientes y distancia con respecto al origen (en este
* caso Kevin Bacon). A partir de ahí, se hará un recorrido lineal sobre
* este grafo construido a base mapas no ordenados y sets no ordenados con
* inserción constante, en busca de alcanzar a todos los actores con el
* menor número posible de películas entre la fuente (Kevin Bacon) y el
* destino (el actor / actriz buscado/a). Este recorrido tendrá, por tanto,
* una complejidad del tipo O(V + A), siendo V el número de actores que
* hay en escena y A el número de conexiones que existen a través de las
* películas.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Actor = std::string;
using Movie = std::string;

using Cast = std::unordered_set<Actor>;
using Filmography = std::unordered_set<Movie>;

class GrafoCine {
private:
    std::unordered_map<Movie, Cast> movieCast;
    std::unordered_map<Actor, Filmography> appearancesActor;

public:
    GrafoCine() {}

    void InsertMovie(Movie movie) {
        Cast newCast;
        auto it = movieCast.find(movie);
        if (it == movieCast.cend()) {
            movieCast.insert({ movie, newCast });
        }
    }

    void InsertActor(Actor actor) {
        Filmography films;
        auto it = appearancesActor.find(actor);
        if (it == appearancesActor.cend()) {
            appearancesActor.insert({ actor, films });
        }
    }

    void InsertActorInMovie(Movie movie, Actor actor) {
        auto it = movieCast.find(movie);

        if (it != movieCast.cend()) {
            it->second.insert(actor);
        }
        else {
            // throw std::exception("No se ha encontrado dicha película");
        }
    }

    void InsertMovieInActorsFilmography(Actor actor, Movie movie) {
        auto it = appearancesActor.find(actor);

        if (it != appearancesActor.cend()) {
            it->second.insert(movie);
        }
        else {
            // throw std::exception("No se ha encontrado dicho actor");
        }
    }

    int GetActorListSize() const { return appearancesActor.size(); }

    const Filmography& GetFilmography(Actor actor) const {
        const Filmography& empty{};
        auto it = appearancesActor.find(actor);
        return (it == appearancesActor.cend()) ? empty : it->second;
    }

    const Cast& GetCast(Movie movie) const {
        const Cast& empty{};
        auto it = movieCast.find(movie);
        return (it == movieCast.cend()) ? empty : it->second;
    }
};

struct GrafoInfo {
    bool visit = false;
    std::string ant;
    int dist = INT_MAX;
};

using GrafoActores = std::unordered_map<Actor, GrafoInfo>;

void bfs(const GrafoCine& grafoCine, GrafoActores& grafoActores,
    std::unordered_set<Movie>& moviesVisited) {
    std::queue<Actor> q;
    
    auto it = grafoActores.find("KevinBacon");
    if (it != grafoActores.cend()) {
        it->second.dist = 0; it->second.visit = true;
        q.push(it->first);
        while (!q.empty()) {
            Actor actor = q.front(); q.pop();
            auto itActor = grafoActores.find(actor);
            const Filmography& actorFilms = grafoCine.GetFilmography(actor);
            for (auto i = actorFilms.cbegin(); i != actorFilms.cend(); ++i) {
                auto itFilm = moviesVisited.find(*i);
                if (itFilm == moviesVisited.cend()) {
                    const Cast& cast = grafoCine.GetCast(*i);
                    for (auto& e : cast) {
                        auto itOtherActor = grafoActores.find(e);
                        if (!itOtherActor->second.visit) {
                            itOtherActor->second.ant = itActor->first;
                            itOtherActor->second.dist = itActor->second.dist + 1;
                            itOtherActor->second.visit = true;
                            q.push(itOtherActor->first);
                        }
                    }
                    moviesVisited.insert(*i);
                }
            }
        }
    }
}

int funcionSolucion(const GrafoActores& grafoActores, const std::string& actor) {
    auto it = grafoActores.find(actor);
    if (it != grafoActores.cend()) {
        return it->second.dist;
    }

    return INT_MAX;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int P; std::cin >> P;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoCine grafoCine;
    GrafoActores grafoActores;

    for (int i = 0; i < P; ++i) {
        std::string film; std::cin >> film;
        grafoCine.InsertMovie(film);
        int actors; std::cin >> actors;
        for (int j = 0; j < actors; ++j) {
            std::string actor; std::cin >> actor;
            GrafoInfo grInfo;
            grafoCine.InsertActor(actor);
            grafoCine.InsertActorInMovie(film, actor);
            grafoCine.InsertMovieInActorsFilmography(actor, film);
            if (grafoActores.find(actor) == grafoActores.cend()) 
                grafoActores.insert({ actor, grInfo });
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    std::unordered_set<Movie> seenMovies;
    bfs(grafoCine, grafoActores, seenMovies);

    int N; std::cin >> N;
    std::string actor;

    // escribir la solución
    for (int i = 0; i < N; ++i) {
        std::string actor; std::cin >> actor;
        int dist = funcionSolucion(grafoActores, actor);
        std::string sol = (dist == INT_MAX) ? "INF" : std::to_string(dist);
        std::cout << actor << ' ' << sol << '\n';
    }

    std::cout << "---\n";

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
