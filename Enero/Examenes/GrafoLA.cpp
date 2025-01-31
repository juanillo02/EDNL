/*
El archipiélago de Tombuctú está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de 
ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. 
Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas existen carreteras
que permiten viajar entre todas las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación más
económica de implantar será el avión. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. 
Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El
objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago,
siguiendo los siguientes criterios:
1)Se implantará una y sólo una línea aérea entre cada par de islas.
2)La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles. Así pues, dados los siguientes datos:
•Lista de ciudades de Tombuctú representada cada una de ellas por sus coordenadas cartesianas.
•Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago,
Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los 
criterios anteriormente expuestos.
*/
#include "alg_grafoPMC.h"
#include "grafoMA.h"
#include "grafoPMC.h"
#include "particion.h"
#include "apo.h"
#include <algorithm>
#include <iostream>
#include <cmath>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct ciudad
{
    double x, y;
};

struct LineaAerea
{
    ciudad c1, c2;
    tCoste coste;
    LineaArea(ciudad c1, ciudad c2): c1{c1}, c2{c2}, coste{distancia(c1, c2)} {}
};

std::vector<LineaAerea> Tombuctu(Grafo MA, std::vector<ciudad> ciudad)
{
    size_t n = MA.numVert();
    GrafoP<double> G(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(M[i][j])
            {
                G[i][j] = distancia(ciudad[i], ciudad[j]);
            }
            if(M[j][i])
            {
                G[j][i] = distancia(ciudad[j], ciudad[i]);
            }
        }
    }
    matriz<vertice> MV(n);
    matri<tCoste> MC = Floyd(G, MV);
    size_t nIslas = n;
    Particion islas(n);
    Apo<LineaAerea> LinAe(n*(n-1)/2);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(islas.encontrar(i) != islas.encontrar(j))
            {
                if(MC[i][j] != GrafoP<double>::INFINITO || M[j][i] != GrafoP<double>::INFINITO)
                {
                    islas.unir(i, j);
                    nIslas--;
                }
                LinAe.insertar(LineaAerea(ciudades[i], ciudades[j]));
            }
        }
    }
    Grafo LineasEncontradas(nIslas);
    std::vector<LineaAerea> resultado(n*(n-1)/2);
    for(size_t i = 0; i < resultado.size(); i++)
    {
        LineaAerea aux = LinAe.cima();
        LinAe.suprimir();
        vertice v = buscarciudad(aux.c1, ciudad), w = buscarciudad(aux.c2, ciudad);
        if(!LineasEncontradas[v][w])
        {
            LineasEncontradas[v][w] = true;
            LineasEncontradas[w][v] = true;
            resultado.push_back(aux);
        }
    }
    return resultado;
}

double distancia(ciudad c1, ciudad c2)
{
    return std::sqrt(std::pow((c1.x - c2.x), 2) + std::pow((c1.y - c2.y), 2));
}

vertice buscarciudad(ciudad c, std::vector<ciudad> ciudad)
{
    for(size_t i = 0; i < ciudad.size(); i++)
    {
        if(c.x == ciudad[i].x && c.y == ciudad[i].y)
        {
            return i-1;
        }
    }
}