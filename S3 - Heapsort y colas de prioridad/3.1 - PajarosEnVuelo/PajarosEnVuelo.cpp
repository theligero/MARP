/*@ <authors>
 * Ignacio Ligero Martín - MARP32
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

/*@ <answer>
* La solución se contruye planteando dos colas de prioridad (una de mínimos
* y otra de máximos) junto a la mediana que se irán actualizando según se
* vayan recibiendo valores. Por cada vuelta de bucle se imprimirá el valor
* de la mediana por pantalla. Si el valor recibido es menor que la mediana,
* se inserta por la izquierda y si es mayor por la derecha. En caso de haber
* más valores en un lado que en otro, se "equilibrarán" las colas de prioridad
* a ambos lados, llevando los valores de la cima a izquierda o a derecha,
* dependiendo de dónde sobren / falten. Por lo tanto, la solución a este problema
* es claramente de coste O(N * log(N)), siendo N el número de pájaros a insertar.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    int E, P;
    // leer los datos de la entrada
    std::cin >> E >> P;

    if (E == 0 && P == 0)
        return false;

    std::priority_queue<int, std::vector<int>, std::less<int>> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;
    int med = E;

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    for (int i = 0; i < P; ++i) {
        int firstValue, secondValue;
        std::cin >> firstValue >> secondValue;

        if (firstValue < med) left.emplace(firstValue);
        else if (firstValue > med) right.emplace(firstValue);

        if (secondValue < med) left.emplace(secondValue);
        else if (secondValue > med) right.emplace(secondValue);

        if (left.size() > right.size()) {
            int aux = left.top(); left.pop();
            right.emplace(med);
            med = aux;
        }
        else if (left.size() < right.size()) {
            int aux = right.top(); right.pop();
            left.emplace(med);
            med = aux;
        }

        std::cout << med << " ";
    }

    std::cout << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
