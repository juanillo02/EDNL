/*
Se dispone de tres grafos que representan la matriz de costes para viajes en un determinado país pero por diferentes medios de transporte,
por supuesto todos los grafos tendrán el mismo número de nodos. El primer grafo representa los costes de ir por carretera, el segundo en tren
y el tercero en avión. Dado un viajero que dispone de una determinada cantidad de dinero, que es alérgico a uno de los tres medios de transporte,
y que sale de una ciudad determinada, implementar un subprograma que determine las ciudades a las que podría llegar nuestro infatigable viajero.
*/

#include "alg_grafoPMC.h"
#include "grafoPMC.h"

typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCoste tCoste;

enum TipoViaje {carretera, tren, avion};

vector<vertice> viaje(GrafoP<int>& GC, GrafoP<int>& GT, GrafoP<int>& GA, unsigned dinero, TipoViaje alergia, vertice origen)
{
    size_t n = GC.numVert();
    GrafoP<int> Gaux(n);
    switch(alergia)
    {
        case 'carretera': Gaux = viajeminimo(GT, GA); break;
        case 'tren': Gaux = viajeminimo(GC, GA); break;
        case 'avion': Gaux = viajeminimo(GC, GT); break;
    }
    vector<vertice> VV(n);
    vector<tCoste> VD = dijsktra(Gaux, origen, VV);
    vector<vertice> resultado(n);
    for(vertice i = 0; i < n; i++)
    {
        if(VD[i] < dinero && i != origen && VD[i] != GrafoP<int>::INFINITO)
        {
            resultado.push_back(i);
        }
    }
    return resultado;
}

GrafoP<int> viajeminimo(GrafoP<int>& G1, GrafoP<int>& G2)
{
    size_t n = G1.numVert();
    GrafoP<int> resultado(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            resultado[i][j] = std::min(G1[i][j], G2[i][j]);
        }
    }
    return resultado;
}