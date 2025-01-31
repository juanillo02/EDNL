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

tCoste laberinto()
{
    GrafoP<int> G(8*8);
    for(vertice i = 0; i < 8*8; i++)
    {
        for(vertice j = 0; j < 8*8; j++)
        {
            if(caballo(nodocasilla(i), nodocasilla(j)))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
    }
    vector<vertice> VV(8*8);
    vector<tCoste> VD = dijsktra(G, 0, VV);
    return VD[(8*8)-1];
}

casilla nodocasilla(vertice v)
{
    casilla c;
    c.x = v / 8;
    c.y = v % 8;
    return c;
}

bool caballo(casilla c1, casilla c2)
{
    if(c2.x >= 0 && c2.x < 8 && c2.y >= 0 && <2.y < 8)
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