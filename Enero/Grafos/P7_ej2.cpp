/*
Se dispone de un laberinto de NxN  casillas del que se conocen las casillas de entrada y salida del mismo. Si te encuentras en una casilla
sólo puedes moverte en las siguientes cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las 
casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared (en caso contrario  no sería un verdadero laberinto). 
Implementa un subprograma que dados: N (dimensión del laberinto), la lista de paredes del laberinto, la casilla de entrada, y la casilla de salida, 
calcule el camino más corto para ir de la entrada a la salida y su longitud.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <iostream>
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct casilla
{
    int x, y;
};

struct pared
{
    casilla origen, destino;
};

struct camino
{
    tCoste tCoste;
    tCamino od;
};

camino laberinto(size_t N, vector<pared>& vp, casilla& entrada, casilla& salida)
{
    GrafoP<int> G(N*N);
    for(vertice i = 0; i < N*N; i++)
    {
        G[i][i] = 0;
        for(vertice j = 0; j < N*N; j++)
        {
            if(adyacentes(NodoCasilla(i, N), NodoCasilla(j, N)))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] GrafoP<int>::INFINITO;
            }
        }
    }
    for(vertice i = 0; i < vp.size(); i++)
    {
        casilla origen = vp[i].origen, destino = vp[i].destino;
        vertice v1 = CasillaNodo(origen, N), v2 = CasillaNodo(destino, N);
        G[v1][v2] = GrafoP<int>::INFINITO;
        G[v2][v1] = GrafoP<int>::INFINITO;
    }
    vertice o = CasillaNodo(entrada, N), d = CasillaNodo(destino, N);
    vector<vertice> VC(G.numVert());
    vector<tCoste> VCostes = dijsktra(G, o, VC);
    camino resultado;
    resultado.coste = VCostes[d];
    tCamino ruta = camino<GrafoP<int>::vertice>(o, d, VC);
    resulrado.od = ruta;
    return resultado;
}

casilla NodoCasilla(vertice i, size_t N)
{
    casilla c;
    c.x = i / N;
    c.y = i % N;
    return c;
}

vertice CasillaNodo(casilla i, size_t N)
{
    return ((v.x * N) + v.y);
}

bool adyacentes(casilla c1, casilla c2)
{
    return (abs(c1.x - c2.x) + abs(c1.y - c2.y) == 1);
}