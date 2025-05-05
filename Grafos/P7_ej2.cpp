#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <iostream>
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

// Estructura que representa una casilla en el laberinto
struct casilla
{
    int x, y;  // Coordenadas de la casilla (fila y columna)
};

// Estructura que representa una pared entre dos casillas
struct pared
{
    casilla origen, destino;  // Dos casillas que forman la pared
};

// Estructura para almacenar el resultado final del camino más corto
struct path
{
    tCoste tCoste;  // Costo del camino más corto
    tCamino od;     // El camino más corto como una secuencia de nodos
};

// Función que convierte un índice de nodo en una casilla (coordenadas x, y)
casilla NodoCasilla(size_t i, size_t N)
{
    casilla c;
    c.x = i / N;     // La fila es el cociente de la división
    c.y = i % N;     // La columna es el resto de la división
    return c;
}

// Función que determina si dos casillas son adyacentes (si están separadas por una casilla)
bool adyacentes(casilla C1, casilla C2)
{
    return (abs(C1.x - C2.x) + abs(C1.y - C2.y) == 1);
}

// Función que convierte una casilla (coordenadas x, y) en el índice de nodo correspondiente en el grafo
vertice CasillaNodo(casilla C, size_t N)
{
    return C.x * N + C.y;  // La fórmula es x * N + y para convertir a índice lineal
}

// Función principal que resuelve el laberinto
path laberinto(size_t N, std::vector<pared>& vp, casilla& entrada, casilla& salida)
{
    // Crear un grafo de NxN nodos (uno por cada casilla del laberinto)
    GrafoP<int> G(N * N); 
    // Inicializar las distancias entre nodos adyacentes (con valor 1) y no adyacentes (con valor INFINITO)
    for (vertice i = 0; i < G.numVert(); i++)
    {
        G[i][i] = 0;  // El costo de moverse a la misma casilla es 0
        for (vertice j = 0; j < G.numVert(); j++)
        {
            if (adyacentes(NodoCasilla(i, N), NodoCasilla(j, N)))  // Si son casillas adyacentes
            {
                G[i][j] = 1;  // El costo de mover entre casillas adyacentes es 1
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;  // Si no son adyacentes, el costo es infinito
            }
        }
    }
    // Marcar las paredes (bloquear las conexiones entre las casillas bloqueadas por las paredes)
    for (vertice i = 0; i < vp.size(); i++)
    {
        casilla origen = vp[i].origen, destino = vp[i].destino;
        vertice v1 = CasillaNodo(origen, N), v2 = CasillaNodo(destino, N);
        G[v1][v2] = GrafoP<int>::INFINITO;  // Bloquear la conexión entre las casillas de la pared
        G[v2][v1] = GrafoP<int>::INFINITO;  // Bloquear la conexión en la otra dirección también
    }
    // Convertir las casillas de entrada y salida a nodos del grafo
    vertice o = CasillaNodo(entrada, N), d = CasillaNodo(salida, N);
    // Ejecutar el algoritmo de Dijkstra desde la entrada
    std::vector<vertice> VC(G.numVert());
    std::vector<tCoste> VCostes = Dijkstra(G, o, VC);  // Obtener los costos mínimos para cada nodo
    // Crear el resultado con el costo del camino más corto y el camino
    path resultado;
    resultado.tCoste = VCostes[d];  // El costo mínimo de la salida
    tCamino ruta = camino<GrafoP<int>::vertice>(o, d, VC);  // Obtener el camino más corto
    resultado.od = ruta;  // Guardar el camino en el resultado
    return resultado;  // Devolver el resultado
}

// Función main para probar el código
int main()
{
    size_t N = 5;  // Tamaño del laberinto (5x5)
    // Definir las paredes (como una lista de paredes entre casillas)
    std::vector<pared> vp = {
        {{0, 0}, {0, 1}},  // Pared entre (0,0) y (0,1)
        {{1, 1}, {1, 2}},  // Pared entre (1,1) y (1,2)
        {{2, 2}, {3, 2}},  // Pared entre (2,2) y (3,2)
        {{3, 3}, {4, 3}},   // Pared entre (3,3) y (4,3)
    };
    // Definir la casilla de entrada y salida
    casilla entrada = {0, 0};  // Entrada en la casilla (0, 0)
    casilla salida = {4, 4};   // Salida en la casilla (4, 4)
    // Llamar a la función laberinto para obtener el camino más corto
    path resultado = laberinto(N, vp, entrada, salida);
    // Imprimir el resultado
    std::cout << "El costo del camino más corto es: " << resultado.tCoste << std::endl;
    std::cout << "El camino más corto es: ";
    // Iterar sobre la lista de camino (tCamino) que es una Lista<vertice>
    for (auto p = resultado.od.primera(); p != resultado.od.fin(); p = resultado.od.siguiente(p)) {
        vertice v = resultado.od.elemento(p);  // Acceder al valor del nodo
        casilla c = NodoCasilla(v, N);  // Convierte el nodo en una casilla
        std::cout << "(" << c.x << ", " << c.y << ") ";
    }
    std::cout << std::endl;
    return 0;
}
