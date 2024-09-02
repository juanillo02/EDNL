/*
El archipiélago de Tombuctú, está formado por un número indeterminado de islas, cada una de las cuales tiene, a su vez, un número indeterminado de ciudades. En
cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo N, por ejemplo).
Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades de la isla. Se dispone de las coordenadas cartesianas (x, y) de todas y cada
una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del
archipiélago. El objetivo de nuestro problema es encontrar qué ciudades de Tombuctú pertenecen a cada una de las islas del mismo y cuál es el coste mínimo de viajar entre
cualesquiera dos ciudades de una misma isla de Tombuctú.
Así pues, dados los siguientes datos:
- Lista de ciudades de Tombuctú representada cada una de ellas por sus coordenadas cartesianas.
- Matriz de adyacencia de Tombuctú, que indica las carreteras existentes en dicho archipiélago.
Implementen un subprograma que calcule y devuelva la distribución en islas de las ciudades de Tombuctú, así como el coste mínimo de viajar entre cualesquiera dos
ciudades de una misma isla del archipiélago. 
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
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct ciudad
{
    double x,y;
};

struct solucion
{
    matriz<double> Mcostes;
    Particion p;
};

solucion tombuctu(Grafo G, vector<ciudad> Vciudad);
double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x-c2.x),2) + pow(abs(c1.y-c2.y),2));
}

int main()
{

    Grafo G("1tom.txt");

    vector<ciudad> Vciudad(5);
    Vciudad[0].x = 3; Vciudad[0].y = 5;
    Vciudad[1].x = 3; Vciudad[1].y = 2;
    Vciudad[2].x = 3; Vciudad[2].y = 1;
    Vciudad[3].x = 1; Vciudad[3].y = -1;
    Vciudad[4].x = 3; Vciudad[4].y = -1;

    solucion res = tombuctu(G, Vciudad);

    return 0;
}

solucion tombuctu(Grafo G, vector<ciudad> Vciudad)
{
    GrafoP<double> GArchipielago(G.numVert());
    Particion pa(G.numVert());
    for(vertice i = 0 ; i < G.numVert() ; i++)
    {
        for(vertice j = 0 ; j < G.numVert() ; j++)
        {
            if(G[i][j])
            {
                GArchipielago[i][j] = distancia(Vciudad[i],Vciudad[j]);

                if(pa.encontrar(i) != pa.encontrar(j))
                {
                    pa.unir(i,j);
                }
            }
            else
            {
                GArchipielago[i][j] = GrafoP<int>::INFINITO;
            }
        }
    }
    solucion res;
    res.p = pa;
    matriz<vertice> Mver(G.numVert());
    res.Mcostes = Floyd(GArchipielago,Mver);
    return res;
}

