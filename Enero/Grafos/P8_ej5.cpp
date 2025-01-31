/*
La nueva compañía de telefonía RETEUNI3 tiene que conectar entre sí, con fibra óptica, todas y cada una de las ciudades del país. Partiendo del
grafo que representa las distancias entre todas las ciudades del mismo, implementad un subprograma que calcule la longitud mínima de fibra óptica
necesaria para realizar dicha conexión.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>
#include "particion.h"
#include <math.h>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

double fibra(GrafoP<int>& G)
{
    size_t n = G.numVert();
    double total = 0;
    GrafoP<int> GK = Kruskall(G);
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            if(GK[i][j] != GrafoP<int>::INFINITO)
            {
                total += GK[i][j];
            }
        }
    }
    return total;
}