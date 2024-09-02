/*
Laberinto NxNxN 
*/

#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <iostream>
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct casilla
{
    int fila, col, prof;
};

tCoste Laberinto(size_t N, vector<casilla>& piedras, casilla& entrada, casilla& salida)
{
    GrafoP<int> G(N*N*N);
    for(vertice i = 0; i < G.numVert(); i++)
    {
        for(vertice j = 0; j < G.numVert(); j++)
        {
            if(adyacentes(NodoCasilla(i, N), NodoCasilla(j, N)))
            {
                G[i][j] = 1;
                G[j][i] = 1;
            }
        }
    }
    for(vertice i = 0; i < G.numVert(); i++)
    {
        for(vertice j = 0; j < piedras.size(); j++)
        {
            G[i][CasillaNodo(piedras[j], N)] = GrafoP<int>::INFINITO;
            G[CasillaNodo(piedras[j], N)][i] = GrafoP<int>::INFINITO;
        }
    }
    vector<vertice> P;
    vector<tCoste> D = Dijkstra(G, CasillaNodo(entrada, N), P);
    return D[CasillaNodo(salida, N)];
}

bool adyacentes(casilla c1, casilla c2)
{
    if(c1.prof == c2.prof)
    {
        return abs(c1.fila - c2.fila) + abs(c1.col - c2.col) == 1;
    }
    else
    {
        return c1.col == c2.col && c1.fila == c2.fila && abs(c1.prof - c2.prof) == 1;
    }
}

casilla NodoCasilla(vertice v, size_t N)
{
    casilla aux;
    aux.fila = v % N;
    aux.col = (v / N) % N;
    aux.prof = v / (N*N);
    return aux;
}

vertice CasillaNodo(casilla c, size_t N)
{
    return c.fila + c.col*N + c.prof*(N*N);
}