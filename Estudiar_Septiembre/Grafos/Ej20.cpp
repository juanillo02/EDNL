/*
La nueva compañía de telefonía RETEUNI3 tiene que conectar entre sí, con fibra óptica, todas y cada una de las ciudades del país. Partiendo del grafo que representa las
distancias entre todas las ciudades del mismo, implementad un subprograma que calcule la longitud mínima de fibra óptica necesaria para realizar dicha conexión.
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "alg_grafoMA.h"
#include "grafoMA.h"
#include "grafoMA.cpp"
#include "particion.h"
#include "particion.cpp"
#include "grafoPMC.h"
#include "matriz.h"
#include "apo.h"
#include <vector>
#include <cmath>
#include <algorithm>

typedef typename GrafoP<int>::tCoste tCoste;

int RETEUNI3(const GrafoP<tCoste>& G)
{
    GrafoP<tCoste> aux = Kruskall(G); //Sacp caminos mínimos
    size_t n = aux.numVert(); //Tamaño
    int suma = 0; //Variable a devolver que almacena suma mínima
    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; ++j)
        {
            suma += aux[i][j];
        }
    }
    return suma;
}