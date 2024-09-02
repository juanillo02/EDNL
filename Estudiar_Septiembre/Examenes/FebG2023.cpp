/*
El archipìélago de Grecoland (Zuelandia) está formado únicamente por tres islas, Fobos, Deimos y Europa, que tienen N1, N2 y N3 ciudades, respectivamente,
de las cuales C1, C2 y C3 ciudades son costeras (obviamente C1 <= N1, C2 <= N2 y C3 <= N3). Se dispone de las coordenadas cartesianas (x, y) de todas
y cada una de las ciudades del archipiélago. El huracán Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes construidos en su día han desaparecido.
En esta terrible situación se pide ayuda a la ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las ciudades del archipiélago)
siempre que se haga al mínimo coste.
De cara a poder comparar costes de posibles reconstrucciones se asume lo siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o el puente).
2. Cualquier puente que se construya siempre será más barato que cualquier carretera que se construya.
En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de Grecoland origen y destino, después de haberse reconstruido el archipiélago,
dados los siguientes datos:
·Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
·Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.
·Lista de ciudades de Europa representadas mediante sus coordenadas cartesianas.
·Lista de ciudades costeras de Fobos.
·Lista de ciudades costeras de Deimos.
·Lista de ciudades costeras de Europa.
·Ciudad origen del viaje.
·Ciudad destino del viaje.
*/

#include "../Grafos/grafoPMC.h"
#include "../Grafos/alg_grafoPMC.h"
#include <vector>
#include <cmath>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct ciudad
{
    double x, y;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x - c2.x), 2) + pow(abs(c1.y - c2.y), 2));
}

vertice buscarCiu(ciudad c, vector<ciudad> ciudades)
{
    bool encontrada = false;
    size_t i;
    for(i = 0; i < ciudades.size() && !encontrada; i ++)
    {
        if(c.x == ciudades[i].x && c.y == ciudades[i].y)
        {
            encontrada = true;
        }
    }
    if(encontrada)
    {
        return i;
    }
    else
    {
        return -1;
    }
}

double Grecoland(vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, vector<ciudad> CostFobos, vector<ciudad> CostDeimos, vector<ciudad> CostEuropa, ciudad ori, ciudad dest)
{
    size_t nf = Fobos.size();
    size_t nd = Deimos.size();
    size_t ne = Europa.size();
    GrafoP<double> Grecoland(nf + nd + ne);
    double Puente = 0;
    for(vertice i = 0; i < CostFobos.size(); i ++)
    {
        vertice CF = buscarCiu(Fobos[i], CostFobos);
        for(vertice j = 0; j < CostDeimos.size(); i++)
        {
            vertice CD = buscarCiu(Deimos[i], CostDeimos);
            double dist = distancia(CostFobos[i], CostDeimos[j]);
            Grecoland[CF][CD] = dist;
            if(dist > Puente)
            {
                Puente = dist;
            }
        }
    }
    for(vertice i = 0; i < CostFobos.size(); i ++)
    {
        vertice CF = buscarCiu(Fobos[i], CostFobos);
        for(vertice j = 0; j < CostEuropa.size(); i++)
        {
            vertice CE = buscarCiu(Europa[i], CostEuropa);
            double dist = distancia(CostFobos[i], CostEuropa[j]);
            Grecoland[CF][CE] = dist;
            if(dist > Puente)
            {
                Puente = dist;
            }
        }
    }
    for(vertice i = 0; i < CostDeimos.size(); i ++)
    {
        vertice CD = buscarCiu(Deimos[i], CostDeimos);
        for(vertice j = 0; j < CostEuropa.size(); i++)
        {
            vertice CE = buscarCiu(Europa[i], CostEuropa);
            double dist = distancia(CostDeimos[i], CostEuropa[j]);
            Grecoland[CD][CE] = dist;
            if(dist > Puente)
            {
                Puente = dist;
            }
        }
    }
    for(vertice i = 0; i < nf; i++)
    {
        for(vertice j = 0; j < nf; j++)
        {
            if(i != j)
            {
                Grecoland[i][j] = Grecoland[j][i] = distancia(Fobos[i], Fobos[j]) + Puente;
            }
        }
    }
    for(vertice i = 0; i < nd; i++)
    {
        for(vertice j = 0; j < nd; j++)
        {
            if(i != j)
            {
                Grecoland[i+nf][j+nf] = Grecoland[j+nf][i+nf] = distancia(Deimos[i], Deimos[j]) + Puente;
            }
        }
    }
    for(vertice i = 0; i < ne; i++)
    {
        for(vertice j = 0; j < ne; j++)
        {
            if(i != j)
            {
                Grecoland[i+nf+nd][j+nf+nd] = Grecoland[j+nf][i+nf] = distancia(Europa[i], Europa[j]) + Puente;
            }
        }
    }
    for(vertice i = 0; i < Grecoland.numVert(); i++)
    {
        Grecoland[i][i] = 0;
    }
    GrafoP<double> K(Grecoland.numVert());
    K = Kruskall(Grecoland);
    vertice o = buscarCiu(ori, Fobos), d = buscarCiu(dest, Fobos);
    if(o == -1)
    {
        o = buscarCiu(ori, Deimos);
    }
    if(o == -1)
    {
        o = buscarCiu(ori, Europa);
    }
    if(d == -1)
    {
        d = buscarCiu(dest, Deimos);
    }
    if(d == -1)
    {
        d = buscarCiu(dest, Europa);
    }
    vector<vertice> P;
    vector<double> D = Dijkstra(K, o, P);
    return D[d];
}
