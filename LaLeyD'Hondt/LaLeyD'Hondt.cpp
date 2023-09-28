/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * MARP17 Ignacio Ligero
  * 
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>
* En primer lugar defino un struct partido que me incluya los siguientes atributos: un entero de votos para almacenar el número
* de votos de un partido, un entero con sus escaños (con valor inicial a cero), un índice para saber el orden inicial de asignación
* y el coeficiente para el cálculo del reparto de escaños a posteriori. Además, tendrá una constructora que pida un entero v como
* número de votos y un entero i para almacenar el valor de su índice, así como un bool operator< para comparar elementos de tipo
* partido entre sí teniendo en cuenta las exigencias del enunciado.
* 
* A partir de ahí, con los casos de entrada, creo una priority_queue que se ordene por std::less de tipo std::vector y vaya almacenando
* el parámetro partido previamente definido. Además, por optimizar código, creo un vector adicional de valor inicial a cero
* que me guarde los escaños de cada partido por la posición en la que se reciben. Voy añadiendo los elementos dados al priority_queue
* llamado congreso a través de un push.
* 
* Después, haré una operación que consistirá en hacer N vueltas del bucle para borrar el elemento que esté en la cima y volverlo a añadir
* con los nuevos parámetros (un escaño más y coeficiente alterado), y al índice le añado adicionalmente un escaño. Por lo tanto, en términos
* de coste, esta operación tendrá un coste en el caso peor de O(N*log(N)), siendo N el número de elementos del vector.
* 
* Para finalizar, escribiré por pantalla todos los elementos del vector de escaños previamente establecido y así devolver lo que pide el
* enunciado: el reparto de escaños por orden de candidatos.
* 
* Si hay que especificar más, el coste en memoria de estas operaciones es de O(2*N), pues necesitaré el vector del priority_queue para optimizar
* las operaciones y el vector de escaños para lo mismo en otro ámbito.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct partido {
    int votos;
    int escanyos = 0;
    int ind;
    double coef;
    partido(int v, int i) : votos(v), ind(i) {
        coef = static_cast<double>(votos) / (escanyos + 1);
    }
    bool operator<(const partido& otro) const {
        if (this->coef < otro.coef) return true;
        else if (this->coef > otro.coef) return false;
        else {
            if (this->votos < otro.votos) return true;
            else if (this->votos > otro.votos) return false;
            else {
                if (this->ind > otro.ind) return true;
                else return false;
            }
        }
    }
};


bool resuelveCaso() {

    // leemos la entrada
    int C, N;
    cin >> C >> N;

    if (C == 0)
        return false;

    // leer el resto del caso y resolverlo
    std::priority_queue<partido, std::vector<partido>, std::less<partido>> congreso;
    std::vector<int> escanyos_cand(C, 0);
    int v;

    for (int i = 0; i < C; ++i) {
        std::cin >> v;
        partido aux(v, i);
        congreso.push(aux);
    }

    int i = 0;

    while (N > 0) {
        partido ganador = congreso.top();
        congreso.pop();

        ++ganador.escanyos;
        escanyos_cand[ganador.ind] = ganador.escanyos;
        ganador.coef = static_cast<double>(ganador.votos) / (ganador.escanyos + 1);
        congreso.push(ganador);

        --N;
    }

    for (int j = 0; j < C; ++j) {
        std::cout << escanyos_cand[j] << ' ';
    }

    std::cout << std::endl;

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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
