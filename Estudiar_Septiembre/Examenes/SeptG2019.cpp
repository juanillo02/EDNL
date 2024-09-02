/*
El archipiélago de Grecoland está formado únicamente por dos islas, Fobos y Demos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2 son costeras
(Obviamente C1 <= N1 y C2 <= N2).
Nos planteamos la construcción de un puente entre las posibles ciudades costeras, cuyo coste directo de viajar por él, al igual que en el caso de las carreteras,
coincidirá con su distancia euclídea.
Se asume que se realizarán exactamente el mismo número de viajes entre cualesquiera ciudades del archipiélago. 
Por ejemplo, se considerará que el número de viajes entre la ciudad P de Fobos y la Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. 
Dicho de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son igual de importantes.
Dada la matriz de adyacencia del archipiélago, las coordenadas cartesianas de cada ciudad y la lista de ciudades costeras de Fobos y Deimos, 
implementa una función que calcule que dos ciudades unirán el puente.
*/

#include <iostream>
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/alg_grafoMA.h"
#include "../Grafos/grafoMA.h"
#include "../Grafos/grafoMA.cpp"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <cmath>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct ciudad
{
    double x, y;
};

struct puente
{
    ciudad c1, c2;
    double coste;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x - c2.x), 2) + pow(abs(c1.y - c2.y), 2));
}

puente MejorPuente(vector<ciudad> CostFobos, vector<ciudad> CostDeimos)
{
    puente p;
    p.coste = GrafoP<int>::INFINITO;
    double minimo;
    for(size_t i = 0; i < CostFobos.size(); i++)
    {
        for(size_t j = 0; j < CostDeimos.size(); j++)
        {
            minimo = (distancia(CostFobos[i], CostDeimos[j]));
            if(minimo < p.coste)
            {
                p.c1 = CostFobos[i];
                p.c2 = CostDeimos[j];
                p.coste = minimo;
            }
        }
    }
    return p;
}

puente Construir(Grafo G, vector<ciudad> Ciudades, vector<ciudad> CostFobos, vector<ciudad> CostDeimos)
{
    size_t n = G.numVert();
    GrafoP<int> Archipielago(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(G[i][j])
            {
                Archipielago[i][j] = distancia(Ciudades[i], Ciudades[j]);
            }
        }
    }
    puente p = MejorPuente(CostFobos, CostDeimos);
    vertice v1, v2;
    for(size_t i = 0; i < Ciudades.size(); i++)
    {
        if(Ciudades[i].x == p.c1.x && Ciudades[i].y == p.c1.y)
        {
            v1 = i;
        }
        if(Ciudades[i].x == p.c2.x && Ciudades[i].y == p.c2.y)
        {
            v2 = i;
        }
    }
    Archipielago[v1][v2] = p.coste;
    Archipielago[v2][v1] = p.coste;
    return p;
}