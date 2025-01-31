/*
Disponemos de tres grafos (matriz de costes) que representan los costes directos de viajar entre las ciudades de tres de las islas del archipiélago
de las Huríes (Zuelandia). Para poder viajar de una isla a otra se dispone de una serie de puentes que conectan ciudades de las diferentes islas
a un precio francamente asequible (por decisión del Prefecto de las Huríes, el uso de los puentes es absolutamente gratuito). Si el alumno desea
simplificar el problema, puede numerar las N1 ciudades de la isla 1, del 0 al N1-1, las N2 ciudades de la isla 2, del N1 al N1+N2-1, y las N3 de
la última, del N1+ N2 al N1+N2+ N3-1. Disponiendo de las tres matrices de costes directos de viajar dentro de cada una de las islas, y la lista
de puentes entre ciudades de las mismas, calculad los costes mínimos de viajar entre cualesquiera dos ciudades de estas tres islas. 
¡¡¡ QUE DISFRUTÉIS EL VIAJE !!!
*/
#include <iostream>
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct puente
{
    vertice origen, destino;
};

matriz<tCoste> viaje(GrafoP<int>& N1, GrafoP<int>& N2, GrafoP<int>& N3, vector<puente>& puentes)
{
    size_t n1 = N1.numVert(), n2 = N2.numVert(), n3 = N3.numVert();
    size_t n = n1 + n2 + n3;
    GrafoP<int> G(n);
    for(vertice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            G[i][j] = N1[i][j];
        }
    }
    for(vertice i = n1; i < n1 + n2; i++)
    {
        for(vertice j = n1; j < n1 + n2; j++)
        {
            G[i][j] = N2[i-n1][j-n1];
        }
    }
    for(vertice i = n1 + n2; i < n1+n2+n3; i++)
    {
        for(vertice j = n1 + n2; j < n1+n2+n3; j++)
        {
            G[i][j] = N3[i-(n1+n2)][j-(n1+n2)];
        }
    }
    for(vertice i = 0; i < puentes.size(); i++)
    {
        G[puentes[i].origen][puentes[i].destino] = 0;
        G[puentes[i].destino][puentes[i].origen] = 0;
    }
    matriz<vertice> MC(n);
    matriz<tCoste> resultado = Floyd(G, MC);
    return resultado;
}