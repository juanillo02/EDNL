/*
El archipiélago de Tombuctú, está formado por un número indeterminado de islas, cada una de las cuales tiene, a su vez, un número indeterminado de
ciudades. En cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas
existen carreteras que permiten viajar entre todas las ciudades de la isla. Se dispone de las coordenadas cartesianas (x, y) de todas y cada 
una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre
cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema es encontrar qué ciudades de Tombuctú pertenecen a cada una de
las islas del mismo y cuál es el coste mínimo de viajar entre cualesquiera dos ciudades de una misma isla de Tombuctú. Así pues, dados los
siguientes datos:
- Lista de ciudades de Tombuctú representada cada una de ellas por sus coordenadas cartesianas. 
- Matriz de adyacencia de Tombuctú, que indica las carreteras existentes en dicho archipiélago. 
Implementen un subprograma que calcule y devuelva la distribución en islas de las ciudades de Tombuctú, así como el coste mínimo de viajar
entre cualesquiera dos ciudades de una misma isla del archipiélago.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<bool>::tCoste tCoste;
typedef typename GrafoP<bool>::vertice vertice;

struct coordenada
{
    int x, y;
};

struct resultado
{
    martriz<tCoste> MR;
    Particion p;
}

resultado tombuctu(GrafoP<bool>& G, vector<coordenada>& ciudades)
{
    GrafoP<double> GD(G.numVert());
    Particion p(G.numVert());
    for(size_t i = 0; i < G.numVert(); i++)
    {
        for(size_t j = 0; j G.numVert(); j++)
        {
            if(G[i][j])
            {
                GD[i][j] = distancia(ciudades[i], ciudades[j]);
                if(p.encontrar(i) != p.encontrar(j))
                {
                    p.unir(i, j);
                }
            }
        }
    }
    matriz<vertice> MV(G.numVert());
    matriz<tCoste> Mcostes = Floyd(GD, MV);
    resultado res;
    res.MR = Mcostes;
    res.p = p;
    return res;
}

double distancia(coordenada c1, coordenada c2)
{
    return std::sqrt(std::pow(abs(c1.x-c2.x),2) + std::pow(abs(c1.y-c2.y),2));
}