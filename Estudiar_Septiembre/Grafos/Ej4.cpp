/*
Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente.
Es un personaje sorprendente, no le importa el dinero y quiere hacer el viaje más caro posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de
dinero posible (ojalá todos los clientes fueran así), no le importa el origen ni el destino del viaje.
Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino
de tan curioso viaje. Se parte de la matriz de costes directos entre las ciudades del grafo. 
*/

#include <iostream>
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct Viaje
{
    tCoste coste;
    typename GrafoP<int>::vertice origen, destino;
};

Viaje ViajeLargo(GrafoP<int>&);

int main()
{
    GrafoP<int> G(5);
    Viaje v = ViajeLargo(G);
    std::cout << "El viaje mas costoso, tiene un coste de: " << v.coste << " y parte del vertice: " << v.origen << " y va hacia: " << v.destino << std::endl;
    return 0;
}

Viaje ViajeLargo(GrafoP<int>& G)
{
    Viaje v;
    matriz<tCoste> MCoste = FloydMax(G);
    for(vertice i = 0; i < G.numVert(); i++)
    {
        for(vertice j = 0; j < G.numVert(); j++)
        {
            if(v.coste < MCoste[i][j] && MCoste[i][j] != GrafoP<int>::INFINITO)
            {
                v.coste = MCoste[i][j];
                v.origen = i;
                v.destino = j;
            }
        }
    }
    return v;
}