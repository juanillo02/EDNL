/*
Dado un tablero de 8x8, una entrada y una salida, calcula el mínimo movimiento que puede realizar un caballo de ajedrez.
*/
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "matriz.h"
#include <iostream>
#include <vector>
#include <algorithm>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct casilla
{
    int x, y;
};

casilla nodocasilla(vertice v, size_t N)
{
    casilla c;
    c.x = v / N;
    c.y = v % N;
    return c;
}

vertice casillanodo(casilla c, size_t N)
{
    return (c.x * N) + c.y;
}

bool caballo(casilla c1, casilla c2)
{
    if(c2.x >= 0 && c2.x < 8 && c2.y >= 0 && c2.y < 8)
    {
        if((abs(c1.x - c2.x) == 1 && abs(c1.y - c2.y) == 2) || (abs(c1.x - c2.x) == 2 && abs(c1.y - c2.y) == 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

tCoste laberinto(size_t n, casilla c1, casilla c2)
{
    GrafoP<int> G(n*n);
    for(vertice i = 0; i < n*n; i++)
    {
        for(vertice j = 0; j < n*n; j++)
        {
            if(caballo(nodocasilla(i, n), nodocasilla(j, n)))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
    }
    vertice inicio = casillanodo(c1, n), fin = casillanodo(c2, n);
    vector<vertice> VV(n*n);
    vector<tCoste> VD = Dijkstra(G, inicio, VV);
    return VD[fin];
}

int main() {
    casilla inicio, fin;
    std::cout << "Introduce la posición inicial (x y) entre 0 y 7: ";
    std::cin >> inicio.x >> inicio.y;
    std::cout << "Introduce la posición final (x y) entre 0 y 7: ";
    std::cin >> fin.x >> fin.y;
    size_t n = 8; // Tablero de 8x8

    tCoste resultado = laberinto(8, inicio, fin);
    if (resultado == GrafoP<int>::INFINITO)
        std::cout << "No se puede llegar a la posición final.\n";
    else
        std::cout << "Número mínimo de movimientos: " << resultado << "\n";

    return 0;
}