/*
El archipìélago de Grecoland (Zuelandia) está formado únicamente por tres islas, Fobos, Deimos y Europa, que tienen N1, N2 y N3 coordenadaes,
respectivamente, de las cuales C1, C2 y C3 ciudaqdes son costeras (obviamente C1 <= N1, C2 <= N2 y C3 <= N3). Se dispone de las coordenadas
cartesianas (x, y) de todas y cada una de las coordenadaes del archipiélago. El huracán Isadore acaba de devastar el archipiélago, con lo que todas
las carreteras y puentes construidos en su día han desaparecido. En esta terrible situación se pide ayuda a la ONU, que acepta reconstruir el
archipiélago (es decir volver a comunicar todas las coordenadaes del archipiélago) siempre que se haga al mínimo coste.
De cara a poder comparar costes de posibles reconstrucciones se asume lo siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud (distancia euclídea entre las poblaciones de
inicio y fin de la carretera o el puente).
2. Cualquier puente que se construya siempre será más barato que cualquier carretera que se construya.
En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos coordenadaes de Grecoland origen y destino,
después de haberse reconstruido el archipiélago, dados los siguientes datos:
·Lista de coordenadaes de Fobos representadas mediante sus coordenadas cartesianas.
·Lista de coordenadaes de Deimos representadas mediante sus coordenadas cartesianas.
·Lista de coordenadaes de Europa representadas mediante sus coordenadas cartesianas.
·Lista de coordenadaes costeras de Fobos.
·Lista de coordenadaes costeras de Deimos.
·Lista de coordenadaes costeras de Europa.
ciudad origen del viaje.
ciudad destino del viaje.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>
#include <cmath>
#include <iostream>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct coordenada
{
    double x, y;
};


tCoste distancias(coordenada c1, coordenada c2)
{
    return std::sqrt(std::pow(abs(c1.x - c2.x), 2) + std::pow(abs(c1.y - c2.y), 2));
}

vertice buscarcoordenada(coordenada c, std::vector<coordenada> coordenadaes)
{
    for(size_t i = 0; i < coordenadaes.size(); i++)
    {
        if(c.x == coordenadaes[i].x && c.y == coordenadaes[i].y)
        {
            return i;
        }
    }
    return -1;
}

double Grecoland(std::vector<coordenada>& coordenadasF, std::vector<coordenada>& coordenadasD, std::vector<coordenada>& coordenadasE, std::vector<coordenada>& costerasF, std::vector<coordenada>& costerasD, std::vector<coordenada>& costerasE, coordenada origen, coordenada destino)
{
    
    size_t nf = coordenadasF.size(), nd = coordenadasD.size(), ne = coordenadasE.size();
    GrafoP<double> G(nf+nd+ne);
    double puente = 0;
    for(vertice i = 0; i < costerasF.size(); i++)
    {
        vertice cf = buscarcoordenada(costerasF[i], coordenadasF);
        for(vertice j = 0; j < costerasD.size(); j++)
        {
            vertice cd = buscarcoordenada(costerasD[j], coordenadasD);
            double distancia = distancias(costerasF[i], costerasD[j]);
            G[cf][cd] = G[cd][cf] = distancia;
            if(distancia > puente)
            {
                puente = distancia;
            }
        }
    }
    for(vertice i = 0; i < costerasF.size(); i++)
    {
        vertice cf = buscarcoordenada(costerasF[i], coordenadasF);
        for(vertice j = 0; j < costerasE.size(); j++)
        {
            vertice ce = buscarcoordenada(costerasE[j], coordenadasE);
            double distancia = distancias(costerasF[i], costerasE[j]);
            G[cf][ce] = G[ce][cf] = distancia;
            if(distancia > puente)
            {
                puente = distancia;
            }
        }
    }
    for(vertice i = 0; i < costerasD.size(); i++)
    {
        vertice cd = buscarcoordenada(costerasD[i], coordenadasD);
        for(vertice j = 0; j < costerasE.size(); j++)
        {
            vertice ce = buscarcoordenada(costerasE[j], coordenadasE);
            double distancia = distancias(costerasD[i], costerasE[j]);
            G[cd][ce] = G[ce][cd] = distancia;
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
                G[i][j] = G[j][i] = distancias(coordenadasF[i], coordenadasF[j]) + puente;
            }
        }
    }
    for(vertice i = nf; i < nf+nd; i++)
    {
        for(vertice j = nf; j < nf+nd; j++)
        {
            if(i != j)
            {
                G[i][j] = G[j][i] = distancias(coordenadasD[i], coordenadasD[j]) + puente;
            }
        }
    }
    for(vertice i = nf+nd; i < nf+nd+ne; i++)
    {
        for(vertice j = nf+nd; j < nf+nd+ne; j++)
        {
            if(i != j)
            {
                G[i][j] = G[j][i] = distancias(coordenadasE[i], coordenadasE[j]) + puente;
            }
        }
    }
    for(vertice i = 0; i < G.numVert(); i++)
    {
        G[i][i] = 0;
    }
    GrafoP<double> GK = Kruskall(G);
    vertice o = buscarcoordenada(origen, coordenadasF);
    if(o == -1)
    {
        o = buscarcoordenada(origen, coordenadasD);
    }
    if(o == -1)
    {
        o = buscarcoordenada(origen, coordenadasE);
    }
    vertice d = buscarcoordenada(destino, coordenadasF);
    if(d == -1)
    {
        d = buscarcoordenada(destino, coordenadasD);
    }
    if(d == -1)
    {
        d = buscarcoordenada(destino, coordenadasE);
    }
    vector<vertice> VV(G.numVert());
    vector<double> VD = Dijkstra(GK, o, VV);
    return VD[d];
}

int main() {
    // Coordenadas de Fobos
    std::vector<coordenada> coordF = { {0, 0}, {1, 0}, {0, 1} };
    std::vector<coordenada> costF = { {0, 0} };

    // Coordenadas de Deimos
    std::vector<coordenada> coordD = { {5, 0}, {6, 1} };
    std::vector<coordenada> costD = { {5, 0} };

    // Coordenadas de Europa
    std::vector<coordenada> coordE = { {10, 0}, {10, 1} };
    std::vector<coordenada> costE = { {10, 0} };

    // Ciudad origen y destino
    coordenada origen = {0, 0};      // En Fobos
    coordenada destino = {10, 1};    // En Europa

    double coste = Grecoland(coordF, coordD, coordE, costF, costD, costE, origen, destino);

    if (coste == GrafoP<tCoste>::INFINITO) {
        std::cout << "No hay conexión posible entre las ciudades." << std::endl;
    } else {
        std::cout << "Coste mínimo de reconstrucción entre origen y destino: " << coste << std::endl;
    }

    return 0;
}