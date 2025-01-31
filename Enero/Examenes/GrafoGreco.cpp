/*
El archipiélago de Grecoland está formado únicamente por dos islas, Fobos y Demos, que tienen N1 y N2 ciudades, respectivamente, de las cuales
C1 y C2 son costeras (Obviamente C1 <= N1 y C2 <= N2). Nos planteamos la construcción de un puente entre las posibles ciudades costeras, cuyo
coste directo de viajar por él, al igual que en el caso de las carreteras, coincidirá con su distancia euclídea. Se asume que se realizarán
exactamente el mismo número de viajes entre cualesquiera ciudades del archipiélago.  Por ejemplo, se considerará que el número de viajes entre
la ciudad P de Fobos y la Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. Dicho de otra forma, todos los posibles
trayectos a realizar dentro del archipiélago son igual de importantes. Dada la matriz de adyacencia del archipiélago, las coordenadas cartesianas
de cada ciudad y la lista de ciudades costeras de Fobos y Deimos, implementa una función que calcule que dos ciudades unirán el puente.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "alg_grafoMA.h"
#include "grafoMA.h"
#include "grafoMA.cpp"
#include "grafoPMC.h"
#include "matriz.h"
#include <cmath>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct ciudad
{
    double x,y;
};

struct puente
{
    ciudad c1,c2;
    double coste;
};

puente Grecoland(Grafo& G, std::vector<ciudad> ciudades, std::vector<ciudad> costerasF, std::vector<ciudad> costerasD)
{
    size_t n = G.numVert();
    GrafoP<double> Grecoland(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(G[i][j])
            {
                Grecoland[i][j] = distancia(ciudades[i], ciudades[j]);
            }
        }
    }
    puente p = mejorpuente(costerasF, costerasD);
    vertice v1, v2;
    for(size_t i = 0; i < ciudades.size(); i ++)
    {
        if(ciudades[i].x == p.v1.x && ciudades[i].y == p.v1.y)
        {
            v1 = i;
        }
        if(ciudades[i].x == p.v2.x && ciudades[i].y == p.v2.y)
        {
            v2 = i;
        }
    }
    Grecoland[v1][v2] = p.coste;
    Grecoland[v2][v1] = p.coste;
    return p;
}

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

puente mejorpuente(std::vector<ciudad> cf, std::vector<ciudad> cd)
{
    puente p;
    p.coste = GrafoP<double>::INFINITO;
    double minimo;
    for(size_t i = 0; i < cf.size(); i++)
    {
        for(size_t j = 0; j < cd.size(); j++)
        {
            minimo = distancia(cf[i], cd[j]);
            if(minimo < p.coste)
            {
                p.coste = minimo;
                p.c1 = cf[i];
                p.c2 = cd[j];
            }
        }
    }
    return p;
}