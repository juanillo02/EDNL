/*
El archipiélago de Tombuctú2 está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de
ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se conoce el número total de ciudades del
archipiélago (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades
de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación más económica de implantar será el avión. 
Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. Se dispone de un grafo (matriz de
adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema
es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios: 
1) Se implantará una y sólo una línea aérea entre cada par de islas. 
2) La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles. 
Así pues, dados los siguientes datos: 
• Lista de ciudades de Tombuctú2 representada cada una de ellas por sus coordenadas cartesianas. 
• Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago, 
Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los
criterios anteriormente expuestos.
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

struct coordenada
{
    int x, y;
};

struct avion
{
    coordenada c1, c2;
    tCoste coste
};

vector<avion> LineaArerea(GrafoP<int>& G, vector<coordenada>& ciudades)
{
    GrafoP<int> GC(G.numVert());
    Particion p(G.numVert());
    size_t n = G.numVert();
    for(size_t i = 0; i < G.numVert(); i++)
    {
        for(size_t j = 0; j < G.numVert(); j++)
        {
            if(G[i][j] && i != j)
            {
                GC[i][j] = distancia(ciudades[i], ciudades[j]);
                if(p.encontrar(i) != p.encontrar(j))
                {
                    p.unir(i, j);
                    n--;
                }
            }
            else
            {
                GC[i][j] = GrafoP<int>::INFINITO;
            }
        }
    }
    matriz<vertice> MV(G.numVert());
    matriz<tCoste> MC = Floyd(GC, MV);
    vector<avion> resultado;
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            if(p.encontrar(i) != p.encontrar(j))
            {
                double min = MC[i][j], minimo = GrafoP<double>::INFINITO;
                vertice v1, v2;
                if(min < minimo)
                {
                    min = minimo;
                    v1 = i;
                    v2 = j;
                }
                avion a;
                a.c1 = ciudades[v1];
                a.c2 = ciudades[v2];
                a.coste = min;
                resultado.push_back(a);
            }
        }
    }
    return resultado;
}

double distancia(coordenada c1, coordenada c2)
{
    return std::sqrt(std::pow(abs(c1.x-c2.x),2) + std::pow(abs(c1.y-c2.y),2));
}