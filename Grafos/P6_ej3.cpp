/*
Tu empresa de transportes “PEROTRAVEZUNGRAFO S.A.” acaba de recibir la lista de posibles subvenciones del Ministerio de Fomento en la que una de
las más jugosas se concede a las empresas cuyo grafo asociado a su matriz de costes sea acíclico. ¿Puedes pedir esta subvención? 
Implementa un subprograma que a partir de la matriz de costes nos indique si tu empresa tiene derecho a dicha subvención.
*/
#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"

typedef typename GrafoP<int>::vertice vertice;

bool aciclico(GrafoP<int>& G)
{
    bool subvencion = false;
    size_t n = G.numVert();
    matriz<int> MC = FloydMod(G);
    for(vertice i = 0; i < n; i++)
    {
        if(MC[i][i] == GrafoP<int>::INFINITO)
        {
            subvencion = true;
        }
    }
    return subvencion;
}

int main()
{
    GrafoP<int> G ("2.txt");
    bool result = aciclico(G);
    if(result)
    {
        std::cout << "El grafo es aciclico, puedes pedir la subvencion." << std::endl;
    }
    else
    {
        std::cout << "El grafo no es aciclico, no puedes pedir la subvencion." << std::endl;
    }
    return 0;
}