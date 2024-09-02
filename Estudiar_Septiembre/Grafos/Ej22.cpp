/*
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas, Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2 ). Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. El huracán
Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes construidos en su día han desaparecido. En esta terrible situación se pide ayuda a la
ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las ciudades del archipiélago) siempre que se haga al mínimo coste.
De cara a poder comparar costes de posibles reconstrucciones se asume lo siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o
del puente).
2. Cualquier puente que se construya siempre será más caro que cualquier carretera que se construya.
De cara a poder calcular los costes de VIAJAR entre cualquier ciudad del archipiélago se considerará lo siguiente:
1. El coste directo de viajar, es decir de utilización de una carretera o de un puente, coincidirá con su longitud (distancia euclídea entre las poblaciones origen y
destino de la carretera o del puente).
En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse
reconstruido el archipiélago, dados los siguientes datos:
1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
2. Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.
3. Lista de ciudades costeras de Fobos.
4. Lista de ciudades costeras de Deimos.
5. Ciudad origen del viaje.
6. Ciudad destino del viaje.
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

struct puente
{
    vertice v1,v2;
    double coste;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x-c2.x),2) + pow(abs(c1.y-c2.y),2));
}

double viajar(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos,vector<vertice> costerasDeimos , vertice origen, vertice destino);
puente Puenteminimo(vector<ciudad> ciudadesFobos,vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos, vector<vertice> costerasDeimos);

int main()
{
    vector<ciudad> ciudadesFobos(4);
    ciudadesFobos[0].x = 1; ciudadesFobos[0].y = 2;
    ciudadesFobos[1].x = 2; ciudadesFobos[1].y = 2;
    ciudadesFobos[2].x = 3; ciudadesFobos[2].y = 2;
    ciudadesFobos[3].x = 5; ciudadesFobos[3].y = 2;

    vector<ciudad> ciudadesDeimos(4);
    ciudadesDeimos[0].x = 3; ciudadesDeimos[0].y = -1;
    ciudadesDeimos[1].x = 3; ciudadesDeimos[1].y = -3;
    ciudadesDeimos[2].x = 3; ciudadesDeimos[2].y = -4;
    ciudadesDeimos[3].x = 3; ciudadesDeimos[3].y = -5;

    vector<vertice> costerasFobos{0,2};
    vector<vertice> costerasDeimos{0,3};

    double costemin = viajar(ciudadesFobos,ciudadesDeimos,costerasFobos,costerasDeimos,0,5);

    cout << "El coste minimo para llegar desde el origen hasta el destino es de: " << costemin;

    return 0;
}

double viajar(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos,vector<vertice> costerasDeimos , vertice origen, vertice destino)
{
    size_t nf = ciudadesFobos.size();
    size_t nd = ciudadesDeimos.size();

    GrafoP<double> GFobos(nf);

    for(vertice i = 0 ; i < nf ; i++)
    {
        for(vertice j = 0 ; j < nf ; j++)
        {
            if(i != j)
            {
                GFobos[i][j] = distancia(ciudadesFobos[i],ciudadesFobos[j]);
            }
        }
    }
    GrafoP<double> GFobosPrim = Prim(GFobos);

    GrafoP<double> GDeimos(nd);

    for(vertice i = 0 ; i < nd ; i++)
    {
        for(vertice j = 0 ; j < nd ; j++)
        {
            if(i != j)
            {
                GDeimos[i][j] = distancia(ciudadesDeimos[i],ciudadesDeimos[j]);
            }
        }
    }
    GrafoP<double> GDeimosPrim = Prim(GDeimos);

    GrafoP<double> Grecoland (nf+nd);

    for(vertice i = 0 ; i < nf ; i++)
    {
        for(vertice j = 0 ; j < nf ; j++)
        {
            Grecoland[i][j] = GFobosPrim[i][j];
        }
    }

    for(vertice i = nf ; i < nf+nd ; i++)
    {
        for(vertice j = nf ; j < nf+nd ; j++)
        {
            Grecoland[i][j] = GDeimosPrim[i-nf][j-nf];
        }
    }

    puente p = Puenteminimo(ciudadesFobos,ciudadesDeimos,costerasFobos,costerasDeimos);
    p.v2 = p.v2 + nf;

    Grecoland[p.v1][p.v2] = p.coste;
    Grecoland[p.v2][p.v1] = p.coste;

    vector<vertice> P(nf+nd);
    vector<double> D = Dijkstra(Grecoland,origen,P);

    return D[destino];
}


puente Puenteminimo(vector<ciudad> ciudadesFobos,vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos, vector<vertice> costerasDeimos)
{
    puente p;
    p.coste = GrafoP<double>::INFINITO;

    for(size_t i = 0; i < costerasFobos.size() ; i++)
    {
        for(size_t j = 0 ; j < costerasDeimos.size() ; j++)
        {
            double cost = distancia(ciudadesFobos[costerasFobos[i]], ciudadesDeimos[costerasDeimos[j]]);
            if(cost < p.coste)
            {
                p.coste = cost;
                p.v1 = costerasFobos[i];
                p.v2 = costerasDeimos[j];
            }
        }
    }
    return p;
}