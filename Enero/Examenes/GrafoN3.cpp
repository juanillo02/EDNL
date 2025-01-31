/*
Se dispone de un laberinto de NxNxN casillas del que se conocen las casillas de entrada y salida del mismo. Si te encuentras en una casilla
sólo puedes moverte (en el mejor caso) en las siguientes seis direcciones (arriba, abajo, derecha, izquierda, adentro, afuera). 
Por otra parte, entre algunas de las casillas hay una piedra que impide moverse hacia ella. Implementa un subprograma que dados: N (dimensión del
laberinto), la lista de casillas que poseen una piedra, la casilla de entrada, y la casilla de salida, calcule el coste del camino más corto para
ir de la entrada a la salida y su longitud. 
*Nota: definir tipos de datos, prototipos de las operaciones de los TADs y de los algoritmos de grafos.
*/
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>
#include <iostream>

typedef GrafoP<int>::tCoste tCoste;
typedef GrafoP<int>::vertice vertice;

struct casilla
{
    int x, y, z;
};

tCoste laberinto(size_t N, std::vector<casilla>& piedra, vertice entrada, vertice salida)
{
    GrafoP<int> G(N*N*N);
    size_t n = G.numVert();
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < piedra.size(); j++)
        {
            G[i][casillanodo(piedra[j], N)] = GrafoP<int>::INFINITO;
            G[casillanodo(piedra[j], N)][i] = GrafoP<int>::INFINITO;
        }
    }
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(adyacentes(nodocasilla(i, N), nodocasilla(j, N)))
            {
                G[i][j] = 1;
                G[j][i] = 1;
            }
        }
    }
    vector<vertice> VV(n);
    vector<tCoste> VC = dijsktra(G, entrada, VV);
    return VD[casillanodo(salida, N)];
}

vertice casillanodo(casilla c, size_t n)
{
    return c.x + c.y*N + c.z*(N*N);
}

casilla nodocasilla(vertice i, size_t N)
{
    casilla c;
    c.x = i % N;
    c.y = (i / N) % N;
    c.z = i / (N*N);
    return c;
}

bool adyacentes(casilla c1, casilla c2)
{
    if(c1.z == c2.z)
    {
        return (abs(c1.x - c2.x) + (c1.y - c2.y)) == 1;
    }
    else
    {
        return c1.x == c2.x && c1.y == c2.y && abs(c1.z - c2.z) == 1;
    }
}