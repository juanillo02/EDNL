/*
La nueva compañía de telefonía RETEUNI3 tiene que conectar entre sí, con fibra óptica, todas y cada una de las ciudades del país. Partiendo del
grafo que representa las distancias entre todas las ciudades del mismo, implementad un subprograma que calcule la longitud mínima de fibra óptica
necesaria para realizar dicha conexión.
*/
//Aplicar Floyd no sirve de nada al hacer Kruskall
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
        for(size_t j = i + 1; j < n; j++) 
        {
            if(GK[i][j] != GrafoP<int>::INFINITO)
            {
                total += GK[i][j];
            }
        }
    }
    return total;
}

int main()
{
    const size_t N = 6;
    GrafoP<int> G(N);

    // Definimos las distancias entre ciudades
    G[0][1] = G[1][0] = 4;
    G[0][2] = G[2][0] = 3;
    G[1][2] = G[2][1] = 1;
    G[1][3] = G[3][1] = 2;
    G[2][3] = G[3][2] = 4;
    G[2][4] = G[4][2] = 5;
    G[3][4] = G[4][3] = 1;
    G[3][5] = G[5][3] = 7;
    G[4][5] = G[5][4] = 3;

    std::cout << "Conexiones óptimas de fibra:\n";
    double total = fibra(G);
    std::cout << "\nLongitud total de fibra óptica necesaria: " << total << std::endl;

    return 0;
}