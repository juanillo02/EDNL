/*
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas, Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente,
de las cuales C1 y C2 ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2). Se dispone de las coordenadas cartesianas (x, y) de todas y cada una
de las ciudades del archipiélago. El huracán Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes construidos en
su día han desaparecido. En esta terrible situación se pide ayuda a la ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar
todas las ciudades del archipiélago) siempre que se haga al mínimo coste. De cara a poder comparar costes de posibles reconstrucciones se asume
lo siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud (distancia euclídea entre las poblaciones de
inicio y fin de la carretera o del puente). 
2. Cualquier puente que se construya siempre será más caro que cualquier carretera que se construya.  
De cara a poder calcular los costes de VIAJAR entre cualquier ciudad del archipiélago se considerará lo siguiente: 
1. El coste directo de viajar, es decir de utilización de una carretera o de un puente, coincidirá con su longitud (distancia euclídea entre las
poblaciones origen y destino de la carretera o del puente). 
En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de Grecoland, origen y destino, después
de haberse reconstruido el archipiélago, dados los siguientes datos: 
1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas. 
2. Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas. 
3. Lista de ciudades costeras de Fobos. 
4. Lista de ciudades costeras de Deimos. 
5. Ciudad origen del viaje. 
6. Ciudad destino del viaje. 
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

struct ciudad
{
    int x, y;
};

struct puente
{
    ciudad c1, c2;
};

double Grecoland(std::vector<ciudad>& ciudadF, std::vector<ciudad>& ciudadD, std::vector<ciudad>& costerasF, std::vector<ciudad>& costerasD, vertice origen, vertice destino)
{
    size_t nf = ciudadF.size(), nd = ciudadD.size();
    GrafoP<int> GF(nf), GD(nd);
    for(vertice i = 0; i < nf; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(i != j)
            {
                GF[i][j] = distancia(ciudadF[i], ciudadF[j]);
            }
        }
    }
    GrafoP<int> PF = Prim(GF);
    for(vertice i = 0; i < nd; i++)
    {
        for(vertice j = 0; j < nd; j++)
        {
            if(i != j)
            {
                GD[i][j] = distancia(ciudadD[i], ciudadD[j]);
            }
        }
    }
    GrafoP<int> PD = Prim(GD), Grecoland(nf + nd);
    for(vertice i = 0; i < nf; i++)
    {
        for(vertice j = 0; j < nf; j++)
        {
            Grecoland[i][j] = GF[i][j];
        }
    }
    for(vertice i = nf; i < nf+nd; i++)
    {
        for(vertice j = nf; j < nf+nd; j++)
        {
            Grecoland[i][j] = GD[i-nf][j-nf];
        }
    }
    puente p = construirpuente(ciudadF, ciudadD, costerasF, costerasD);
    p.v2 += nf;
    Grecoland[p.v1][p.v2] = p.coste;
    Grecoland[p.v2][p.v1] = p.coste;
    std::vector<vertice> VV(Grecoland.numVert());
    std::vector<tCoste> VD = dijsktra(Grecoland, origen, VV);
    return VD[destino];
}

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x-c2.x),2) + pow(abs(c1.y-c2.y),2));
}

puente Puenteminimo(std::vector<ciudad> ciudadF,std::vector<ciudad> ciudadD, std::vector<vertice> costerasF, std::vector<vertice> costerasD)
{
    puente p;
    p.coste = GrafoP<double>::INFINITO;

    for(size_t i = 0; i < costerasF.size() ; i++)
    {
        for(size_t j = 0 ; j < costerasD.size() ; j++)
        {
            double min = distancia(ciudadF[costerasF[i]], ciudadD[costerasD[j]]);
            if(min < p.coste)
            {
                p.coste = min;
                p.v1 = costerasF[i];
                p.v2 = costerasD[j];
            }
        }
    }
    return p;
}