/*
El archipiélago de Tombuctú está formado por un número desconocido de  islas, cada una de las cuales tiene, a su vez, un número desconocido de 
ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. 
Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas existen 
carreteras que permiten viajar entre todas las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación 
más económica de implantar será el avión. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. 
Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El objetivo 
de nuestro problema es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes 
criterios:
1)Se implantará una y sólo una línea aérea entre cada par de islas.
2)La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles. Así pues, dados los siguientes datos:
•Lista de ciudades de Tombuctú representada cada una de ellas por sus coordenadas cartesianas.
•Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago,
Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente expuestos.
*/

#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoMA.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/particion.h"
#include "../Grafos/apo.h"
#include <algorithm>
#include <iostream>
#include <cmath>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct ciudad
{
    double x, y;
};

struct LA
{
    ciudad c1, c2;
    double coste;
    LA(ciudad c1, ciudad c2, double coste = 0): c1(c1), c2(c2), coste(coste){}
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x - c2.x), 2) + pow(abs(c1.y - c2.y), 2));
}

vertice BC(ciudad c, vector<ciudad> ciudades)
{
    bool encontrada = false;
    vertice i;
    for(i = 0; i < ciudades.size() && !encontrada; i++)
    {
        if(c.x == ciudades[i].x && c.y == ciudades[i].y)
        {
            encontrada = true;
        }
    }
    return i-1;
}

vector<LA> Tumbuctu(Grafo MA, vector<ciudad> ciudades)
{
    size_t n = MA.numVert();
    GrafoP<double> G(G);
    for(vertice i = 0; i < n; i++)
    {
        for (vertice j = 0; i < n; j++)
        {
            if(MA[i][j])
            {
                G[i][j] = distancia(ciudades[i], ciudades[j]);
            }
            if(MA[j][i])
            {
                G[j][i] = distancia(ciudades[i], ciudades[j]);
            }
        }
    }
    matriz<vertice> MV;
    matriz<tCoste> MC = Floyd(G, MV);
    size_t NumIslas = n;
    Particion Islas(NumIslas);
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            if(MA[i][j] != GrafoP<double>::INFINITO || MC[i][j] != GrafoP<double>::INFINITO && Islas.encontrar(i) != Islas.encontrar(j))
            {
                Islas.unir(i, j);
                NumIslas--;
            }
        }
    }
    Apo<LA> AL(n*(n-1)/2);
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            if(Islas.encontrar(i) != Islas.encontrar(j))
            {
                AL.insertar(LA(ciudades[i], ciudades[j]));
            }
        }
    }
    Grafo IslasCon(NumIslas);
    vector<LA> Lineas(NumIslas * (NumIslas-1)/2);
    for(size_t i = 0; i < Lineas.size(); i++)
    {
        LA l = AL.cima();
        AL.suprimir();
        vertice v = BC(l.c1, ciudades) % NumIslas;
        vertice w = BC(l.c2, ciudades) % NumIslas;
        if(!IslasCon[v][w])
        {
            IslasCon[v][w] = true;
            IslasCon[w][v] = true;
            Lineas.push_back(l);
        }
    }
    return Lineas;
}