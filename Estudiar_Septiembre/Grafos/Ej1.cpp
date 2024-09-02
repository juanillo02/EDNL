/*
Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que minimiza la suma de las distancias mínimas a sus dos nodos más alejados. Definiremos
el diámetro del grafo como la suma de las distancias mínimas a los dos nodos más alejados del pseudocentro del grafo.
Dado un grafo conexo representado mediante matriz de costes, implementa un subprograma que devuelva la longitud de su diámetro. 
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"

GrafoP<int>::tCoste diametro(GrafoP<int>&);

int main()
{
    GrafoP<int> G(7);
    GrafoP<int>::tCoste d = diametro(G);
    std::cout << d;
    return 0;
}

GrafoP<int>::tCoste diametro(GrafoP<int>& G)
{
    typedef typename GrafoP<int>::vertice vertice;
    typedef typename GrafoP<int>::tCoste tCoste;
    tCoste diametro, aux1 = 0, aux2;
    matriz<vertice> Mvertices(G.numVert());
    matriz<tCoste>  MCostes = Floyd(G, Mvertices);
    vertice pseudocentro;
    for(vertice i = 0; i < G.numVert(); i++)
    {
        for(vertice j = 0; j < G.numVert(); j++)
        {
            if(MCostes[i][j] >= aux1 && MCostes[i][j] != GrafoP<int>::INFINITO)
            {
                aux2 = aux1;
                aux1 = MCostes[i][j];
            }
            else
            {
                if(MCostes[i][j] >= aux2 && MCostes[i][j] != GrafoP<int>::INFINITO)
                {
                    aux2 = MCostes[i][j];
                }
            }
        }
        if(diametro < aux1 + aux2)
        {
            diametro = aux1 + aux2;
            pseudocentro = i;
        }
    }
    std::cout << "Pseudocentro: " << pseudocentro << std::endl;
    return diametro;
}