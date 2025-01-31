/*
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas, Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de
las cuales C1 y C2 ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2). Se desea construir un puente que una ambas islas. Nuestro problema es
elegir el puente a construir entre todos los posibles, sabiendo que el coste de construcción del puente se considera irrelevante. Por 
tanto, escogeremos aquel puente que minimice el coste global de viajar entre todas las ciudades de las dos islas, teniendo en cuenta las
siguientes premisas: 
1. Se asume que el coste viajar entre las dos ciudades que una el puente es 0. 
2. Para poder plantearse las mejoras en el transporte que implica la construcción de un puente frente a cualquier otro, se asume que se realizarán
exactamente el mismo número de viajes entre cualesquiera ciudades del archipiélago. Por ejemplo, se considerará que el número de viajes entre
la ciudad P de Fobos y la Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. Dicho de otra forma, todos los posibles
trayectos a realizar dentro del archipiélago son igual de importantes. Dadas las matrices de costes directos de Fobos y Deimos y las listas de
ciudades costeras de ambas islas, implementa un subprograma que calcule las dos ciudades que unirá el puente. 
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct puente
{
    vertice origen, destino;
};

puente union(GrafoP<int>& Fobos, GrafoP<int>& Deimos, vector<vertice>& CosterasF, vector<vertice>& costerasD)
{
    size_t nf = Fobos.numVert(), nd = Deimos.numVert();
    size_t n = nf + nd;
    GrafoP<int> G(n);
    for(vertice i = 0; i < nf; i++)
    {
        for(vertice j = 0; j < nf; j++)
        {
            G[i][j] = Fobos[i][j];
        }
    }
    for(vertice i = nf; i < n; i++)
    {
        for(vertice j = nf; j < n; j++)
        {
            G[i][j] = Deimnos[i-nf][j-nf];
        }
    }
    matriz<vertice> MV(n);
    matriz<tCoste> MCoste;
    tCoste minimo = GrafoP<int>::INFINITO, coste;
    vertice v1, v2;
    for(vertice i = 0; i < costerasD.size(); i++)
    {
        costerasD[i] = costerasD[i] + nf;
    }
    for(vertice i = 0; i < costerasF.size(); i++)
    {
        for(vertice j = 0; j < costerasD.size(); j++)
        {
            G[costerasF[i]][costerasD[j]] = 0;
            G[costerasD[j]][costerasF[i]] = 0;
            MCoste = Floyd(G, MV);
            coste = total(MCoste, nf, nd);
            if(coste < minimo)
            {
                minimo = coste;
                v1 = costerasF[i];
                v2 = costerasD[j];
            }
            G[costerasF[i]][costerasD[j]] = GrafoP<int>::INFINITO;
            G[costerasD[j]][costerasF[i]] = GrafoP<int>::INFINITO;
        }
    }
    puente resultado;
    resultado.origen = v1;
    resultado.destino = v2;
    return resultado;
}