/*
Tu empresa de transportes “PEROTRAVEZUNGRAFO S.A.” acaba de recibir la lista de posibles subvenciones del Ministerio de Fomento en la que una de las más
jugosas se concede a las empresas cuyo grafo asociado a su matriz de costes sea acíclico. ¿Puedes pedir esta subvención?
Implementa un subprograma que a partir de la matriz de costes nos indique si tu empresa tiene derecho a dicha subvención. 
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"

bool aciclico(GrafoP<int>&);

int main()
{
    GrafoP<int> G(7);
    if(aciclico(G))
    {
        std::cout << "Puede obtener la subvencion" << std::endl;
    }
    else
    {
        std::cout << "No puede obtener la subvencion" << std::endl;
    }
    return 0;
}

bool aciclico(GrafoP<int>& G)
{
    typedef typename GrafoP<int>::vertice vertice;
    typedef typename GrafoP<int>::tCoste tCoste;
    matriz<vertice> M(G.numVert());
    matriz<tCoste> MCoste = Floyd(G, M);
    bool aciclico = true;
    for(vertice i = 0; i < G.numVert(); i++)
    {
        if(MCoste[i][i] == GrafoP<int>::INFINITO)
        {
            aciclico = false;
        }
    }
    return aciclico;
}