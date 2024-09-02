/*
El archipiélago de Tombuctú2 está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales
tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo).
Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la
opción de comunicación más económica de implantar será el avión.
Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se
indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para
poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:
1) Se implantará una y sólo una línea aérea entre cada par de islas.
2) La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles.
Así pues, dados los siguientes datos:
• Lista de ciudades de Tombuctú2 representada cada una de ellas por sus coordenadas cartesianas.
• Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago,
Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente expuestos.
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

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct ciudad
{
    double x,y;
};

struct lineaerea
{
    vertice v1,v2;
    double coste;
};
/*
    1) Se implantará una y sólo una línea aérea entre cada par de islas. 
    2) La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles. 
*/

vector<lineaerea> tombuctu2(Grafo& G, vector<ciudad> Vciudad);

int main ()
{
    Grafo G("1tom.txt");

    vector<ciudad> Vciudad(5);
    Vciudad[0].x = 3; Vciudad[0].y = 5;
    Vciudad[1].x = 3; Vciudad[1].y = 2;
    Vciudad[2].x = 3; Vciudad[2].y = 1;
    Vciudad[3].x = 1; Vciudad[3].y = -1;
    Vciudad[4].x = 3; Vciudad[4].y = -1;

    vector<lineaerea> res = tombuctu2(G,Vciudad); 


    return 0;
}

vector<lineaerea> tombuctu2(Grafo& G, vector<ciudad> Vciudad)
{
    size_t n = G.numVert();
    Particion p(n);

    for(vertice i = 0 ; i < n ; i++)
    {
        for(vertice j = 0 ; j < n ; j++)
        {
            if(G[i][j])
            {
                if(p.encontrar(i) != p.encontrar(j))
                {
                    p.unir(i,j);
                }
            }
        }
    }

    Apo<lineaerea> A(n * (n-1));

    for(vertice i = 0 ; i < n ; i++)
    {
        for(vertice j = 0 ; j < n ; j++)
        {
            if(p.encontrar(i) != p.encontrar(j))
            {
                lineaerea aux;
                aux.coste = sqrt(pow(Vciudad[i].x - Vciudad[j].x,2) + pow(Vciudad[i].y - Vciudad[j].y,2));
                aux.v1 = i;
                aux.v2 = j;
                A.insertar(aux);
            }
        }
    }
    matriz<bool> islas(n, false);
    vector<lineaerea> solucion(n*(n-1));
    size_t i = 0;
    while(!A.vacio() && i < n*(n-1))
    {
        lineaerea aux = A.cima();
        if(p.encontrar(aux.v1) != p.encontrar(aux.v2) && islas[aux.v1][aux.v2] == false)
        {
            islas[aux.v1][aux.v2] = true;
            solucion[i].v1 = aux.v1;
            solucion[i].v2 = aux.v2;
            solucion[i].coste = aux.coste;
            i++;
            A.suprimir();
        }
    }
    return solucion;
}