/*
El archipìélago de Grecoland (Zuelandia) está formado únicamente por tres islas, Fobos, Deimos y Europa, que tienen N1, N2 y N3 ciudades,
respectivamente, de las cuales C1, C2 y C3 ciudaqdes son costeras (obviamente C1 <= N1, C2 <= N2 y C3 <= N3). Se dispone de las coordenadas
cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. El huracán Isadore acaba de devastar el archipiélago, con lo que todas
las carreteras y puentes construidos en su día han desaparecido. En esta terrible situación se pide ayuda a la ONU, que acepta reconstruir el
archipiélago (es decir volver a comunicar todas las ciudades del archipiélago) siempre que se haga al mínimo coste.
De cara a poder comparar costes de posibles reconstrucciones se asume lo siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud (distancia euclídea entre las poblaciones de
inicio y fin de la carretera o el puente).
2. Cualquier puente que se construya siempre será más barato que cualquier carretera que se construya.
En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de Grecoland origen y destino,
después de haberse reconstruido el archipiélago, dados los siguientes datos:
·Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
·Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.
·Lista de ciudades de Europa representadas mediante sus coordenadas cartesianas.
·Lista de ciudades costeras de Fobos.
·Lista de ciudades costeras de Deimos.
·Lista de ciudades costeras de Europa.
·Ciudad origen del viaje.
·Ciudad destino del viaje.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>
#include <cmath>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct ciudad
{
    double x, y;
};

double Grecoland(std::vector<ciudad>& ciudadesF, std::vector<ciudad>& ciudadesD, std::vector<ciudad>& ciudadesE, std::vector<ciudad>& costerasF, std::vector<ciudad>& costerasD, std::vector<ciudad>& costerasE, ciudad origen, ciudad destino)
{
    
    GrafoP<isize_t nf = ciudadesF.size(), nd = ciudadesD.size(), ne = ciudadesE.size();nt> G(nf+nd+ne);
    double puente = 0;
    for(vertice i = 0; i < costerasF.size(); i++)
    {
        vertice cf = buscarciudad(costerasF[i], ciudadesF);
        for(vertice j = 0; j < costerasD.size(); j++)
        {
            vertice cd = buscarciudad(costerasD[j], ciudadesD);
            double distancia = distancia(cf, cd);
            G[i][j] = G[j][i] = distancia;
            if(distancia > puente)
            {
                puente = distancia;
            }
        }
    }
    for(vertice i = 0; i < costerasF.size(); i++)
    {
        vertice cf = buscarciudad(costerasF[i], ciudadesF);
        for(vertice j = 0; j < costerasE.size(); j++)
        {
            vertice ce = buscarciudad(costerasE[j], ciudadesE);
            double distancia = distancia(cf, ce);
            G[i][j] = G[j][i] = distancia;
            if(distancia > puente)
            {
                puente = distancia;
            }
        }
    }
    for(vertice i = 0; i < costerasD.size(); i++)
    {
        vertice cd = buscarciudad(costerasD[i], ciudadesD);
        for(vertice j = 0; j < costerasE.size(); j++)
        {
            vertice ce = buscarciudad(costerasE[j], ciudadesE);
            double distancia = distancia(cd, ce);
            G[i][j] = G[j][i] = distancia;
            if(distancia > puente)
            {
                puente = distancia;
            }
        }
    }
    for(vertice i = 0; i < nf; i++)
    {
        for(vertice j = 0; j < nf; j++)
        {
            if(i != j)
            {
                G[i][j] = G[j][i] = distancia(ciudadesF[i], ciudades[j]) + puente;
            }
        }
    }
    for(vertice i = nf; i < nf+nd; i++)
    {
        for(vertice j = nf; j < nf+nd; j++)
        {
            if(i != j)
            {
                G[i][j] = G[j][i] = distancia(ciudadesD[i], ciudades[j]) + puente;
            }
        }
    }
    for(vertice i = nf+nd; i < nf+nd+ne; i++)
    {
        for(vertice j = nf+nd; j < nf+nd+ne; j++)
        {
            if(i != j)
            {
                G[i][j] = G[j][i] = distancia(ciudadesE[i], ciudades[j]) + puente;
            }
        }
    }
    for(vertice i = 0; i < G.numVert(); i++)
    {
        G[i][i] = 0;
    }
    GrafoP<double> G = Kruskal(G);
    vertice o = buscarciudad(origen, ciudadesF);
    if(o == -1)
    {
        o = buscarciudad(origen, ciudadesD);
    }
    if(o == -1)
    {
        o = buscarciudad(origen, ciudadesE);
    }
    vertice d = buscarciudad(destino, ciudadesF);
    if(d == -1)
    {
        d = buscarciudad(destino, ciudadesD);
    }
    if(d == -1)
    {
        d = buscarciudad(destino, ciudadesE);
    }
    vector<vertice> VV(G.numVert());
    vector<tCoste> VD = dijsktra(G, o, VV);
    return VD[d];
}

double distancia(ciudad c1, ciudad c2)
{
    return std::sqrt(std::pow(abs(c1.x - c2.x), 2) + std::pow(abs(c1.y - c2.y), 2));
}

vertice buscarciudad(ciudad c, std::vector<ciudad> ciudades)
{
    for(size_t i = 0; i < ciudades.size(); i++)
    {
        if(c.x == ciudades[i].x && c.y == ciudades[i].y)
        {
            return i;
        }
        else
        {
            return -1;
        }
    }
}