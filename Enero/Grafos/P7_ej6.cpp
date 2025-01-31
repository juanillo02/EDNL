/*
Al dueño de una agencia de transportes se le plantea la siguiente situación. La agencia de viajes ofrece distintas trayectorias combinadas
entre N ciudades españolas utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de costes) de viajar entre
diferentes ciudades, por un lado en tren, y por otro en autobús (por supuesto entre las ciudades que tengan línea directa entre ellas).
Además coincide que los taxis de toda España se encuentran en estos momentos en huelga general, lo que implica que sólo se podrá cambiar de
transporte en una ciudad determinada en la que, por casualidad, las estaciones de tren y autobús están unidas. Implementa una función que
calcule la tarifa mínima (matriz de costes mínimos) de viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús, 
del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>
#include "matriz.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

matriz<tCoste> tarifa(GrafoP<int>& GT, GrafoP<int>& GA, vertice transbordo)
{
    size_t n = GT.numVert();
    bool transbordotren = false; transbordobus = false;
    for(vertice i = 0; i < n; i++)
    {
        if(GT[transbordo][i] != GrafoP<int>::INFINITO)
        {
            transbordotren = true;
        }
        if(GA[transbordo][i] != GrafoP<int>::INFINITO)
        {
            transbordobus = true;
        }
    }
    if(transbordotren || transbordobus)
    {
        GrafoP<int> resultado(n);
        for(vertice i = 0; i < n; i++)
        {
            for(vertice j = 0; j < n; j++)
            {
                resultado[i][j] = std::min(GT[i][j], GA[i][j]);
                matriz<vertice> MV(resultado.numVert());
                matriz<tCoste> MC = Floyd(resultado, MV);
                return MC;
            }
        }
    }
}