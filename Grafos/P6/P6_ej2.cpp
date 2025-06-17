/*
Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que minimiza la suma de las distancias mínimas a sus dos nodos más alejados.
Definiremos el diámetro del grafo como la suma de las distancias mínimas a los dos nodos más alejados del pseudocentro del grafo. 
Dado un grafo conexo representado mediante matriz de costes, implementa un subprograma que devuelva la longitud de su diámetro.
*/
#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "matriz.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;


tCoste diametro(GrafoP<int>& G)
{
    tCoste diametro = 0, aux1, aux2;
    matriz<vertice> MV(G.numVert());
    matriz<tCoste> MC = Floyd(G, MV);
    for(vertice i = 0; i < G.numVert(); i++)
    {
        aux1 = 0;
        aux2 = 0;
        for(vertice j = 0; j < G.numVert(); j++)
        {
            if(MC[i][j] >= aux1 && MC[i][j] != GrafoP<int>::INFINITO)
            {
                aux2 = aux1;
                aux1 = MC[i][j];
            }
            else
            {
                if(MC[i][j] >= aux2 && MC[i][j] != GrafoP<int>::INFINITO)
                {
                    aux2 = MC[i][j];
                }
            }
        }
        if(diametro < aux1 + aux2)
        {
            diametro = aux1 + aux2;
        }
    }
    return diametro;
}

int main()
{
    GrafoP<int> G ("2.txt");
    tCoste result = diametro(G);
    std::cout << "El diametro del grafo es: " << result << std::endl;
    return 0;
}
