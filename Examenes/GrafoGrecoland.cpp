/*
El archipiélago de Grecoland está formado únicamente por dos islas, Fobos y Demos, 
que tienen N1 y N2 coordenadaes, respectivamente, de las cuales C1 y C2 son costeras (Obviamente C1 <= N1 y C2 <= N2).
Nos planteamos la construcción de un puente entre las posibles coordenadaes costeras, cuyo coste directo de viajar por él,
al igual que en el caso de las carreteras, coincidirá con su distancia euclídea.
Se asume que se realizarán exactamente el mismo número de viajes entre cualesquiera coordenadaes del archipiélago. 
Por ejemplo, se considerará que el número de viajes entre la coordenada P de Fobos y la Q de Deimos será el mismo que entre las coordenadaes R y S de la misma isla. 
Dicho de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son igual de importantes.
Dada la matriz de adyacencia del archipiélago, las coordenadas cartesianas de cada coordenada y la lista de coordenadaes costeras de Fobos y Deimos, 
implementa una función que calcule que dos coordenadaes unirán el puente.
*/
#include <iostream>
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>
#include <cmath>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct coordenada
{
    double x,y;
};

struct puente
{
    coordenada c1,c2;
    double coste;
};


double distancia(coordenada c1, coordenada c2)
{
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

puente mejorpuente(std::vector<coordenada> cf, std::vector<coordenada> cd)
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

puente Grecoland(GrafoP<double>& G, std::vector<coordenada> coordenadaes, std::vector<coordenada> costerasF, std::vector<coordenada> costerasD)
{
    size_t n = G.numVert();
    GrafoP<double> Grecoland(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(G[i][j])
            {
                Grecoland[i][j] = distancia(coordenadaes[i], coordenadaes[j]);
            }
        }
    }
    puente p = mejorpuente(costerasF, costerasD);
    vertice v1, v2;
    for(size_t i = 0; i < coordenadaes.size(); i ++)
    {
        if(coordenadaes[i].x == p.c1.x && coordenadaes[i].y == p.c1.y)
        {
            v1 = i;
        }
        if(coordenadaes[i].x == p.c2.x && coordenadaes[i].y == p.c2.y)
        {
            v2 = i;
        }
    }
    Grecoland[v1][v2] = p.coste;
    Grecoland[v2][v1] = p.coste;
    return p;
}

int main() {
    // 4 vértices: 2 en Fobos, 2 en Deimos
    GrafoP<double> G(4);
    std::vector<coordenada> coords = {
        {0, 0},   // Fobos 0
        {0, 1},   // Fobos 1
        {100, 0}, // Deimos 2
        {100, 1}  // Deimos 3
    };

    // Unimos internamente Fobos y Deimos
    G[0][1] = G[1][0] = 1.0;
    G[2][3] = G[3][2] = 1.0;

    std::vector<coordenada> costerasF = {coords[0], coords[1]};
    std::vector<coordenada> costerasD = {coords[2], coords[3]};

    puente p = Grecoland(G, coords, costerasF, costerasD);
    std::cout << "Puente más barato:\n";
    std::cout << "  Desde (" << p.c1.x << ", " << p.c1.y << ")";
    std::cout << " a (" << p.c2.x << ", " << p.c2.y << ")\n";
    std::cout << "  Coste: " << p.coste << "\n";

    return 0;
}