/*El archipielago de Grecoland (Nozuelandia) está formado unicamente por tres islas, Fobos, Deimos y Europa y tienen N1, N2 y N3 ciudades, respectivamente, todas ellas costeras.
Se dispone de la relacion de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.
Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. Las condiciones del programa COMUNICA indican que se sufragaran
todos los costes de construcción de las comunicaciones (carreteras y puentes) al menor coste posible.
Se sabe que la mera construccion de un puente o carretera ya implica una serie de costes fijos, que difieren para el caso de carretera y puente.
Además, el coste por unidad de longitud para carreteras y puentes tambien es distinto.
En estas condiciones se debe calcular (mediante una funcion) que carreteras y puentes deben construirse para comunicar entre si todas las ciudades de Grecoland, dados los siguientes datos:
    1. Relacion de las ciudades de Fobos, representadas mediante sus coordenadas cartesianas
    2. Relacion de las ciudades de Deimos, representadas mediante sus coordenadas cartesianas
    3. Relacion de las ciudades de Europa, representadas mediante sus coordenadas cartesianas
    4. Coste inicial de construccion de un puente
    5. Coste inicial de construccion de una carreteras
    6. Coste adicional por unidad de longitud de construccion de un puente
    7. Coste adicional por unidad de longitud de construccion de una carretera
*/

#include <iostream>
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>
#include <cmath>
#include <algorithm>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct ciudad
{
    int x, y;
};

struct puente
{
    ciudad c1, c2;
    vertice v1, v2;
    double coste;
};

struct puentes
{
    puente p1, p2;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x - c2.x), 2) + pow(abs(c1.y - c2.y), 2));
}

double Grecoland(vector<ciudad>& Fobos, vector<ciudad>& Deimos, vector<ciudad>& Europa, double costePuente, double costeCarretera, double costeLongPuente, double costeLongCarretera)
{
    size_t nf = Fobos.size();
    GrafoP<double> GF(nf);
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < nf;j ++)
        {
            GF[i][j] = distancia(Fobos[i], Fobos[j]);
        }
    }
    GrafoP<double> GFP = Prim(GF);
    double CosteConst = 0;
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < nf;j ++)
        {
            if(GFP[i][j] != GrafoP<double>::INFINITO)
            {
                CosteConst += costeCarretera + (costeLongCarretera * GFP[i][j]);
            }
        }
    }
    size_t nd = Deimos.size();
    GrafoP<double> GD(nd);
    for(size_t i = 0; i < nd; i++)
    {
        for(size_t j = 0; j < nd;j ++)
        {
            GD[i][j] = distancia(Deimos[i], Deimos[j]);
        }
    }
    GrafoP<double> GDP = Prim(GD);
    for(size_t i = 0; i < nd; i++)
    {
        for(size_t j = 0; j < nd;j ++)
        {
            if(GDP[i][j] != GrafoP<double>::INFINITO)
            {
                CosteConst += costeCarretera + (costeLongCarretera * GDP[i][j]);
            }
        }
    }
    size_t ne = Europa.size();
    GrafoP<double> GE(ne);
    for(size_t i = 0; i < ne; i++)
    {
        for(size_t j = 0; j < ne;j ++)
        {
            GE[i][j] = distancia(Europa[i], Europa[j]);
        }
    }
    GrafoP<double> GEP = Prim(GE);
    for(size_t i = 0; i < ne; i++)
    {
        for(size_t j = 0; j < ne;j ++)
        {
            if(GEP[i][j] != GrafoP<double>::INFINITO)
            {
                CosteConst += costeCarretera + (costeLongCarretera * GEP[i][j]);
            }
        }
    }
    GrafoP<double> Grecoland(nf + nd + ne);
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < nf;j ++)
        {
            Grecoland[i][j] = GFP[i][j];
        }
    }
    for(size_t i = 0; i < nf + nd; i++)
    {
        for(size_t j = 0; j < nf + nd; j ++)
        {
            Grecoland[i][j] = GD[i - nf][j - nf];
        }
    }
    for(size_t i = 0; i < nf + nd + ne; i++)
    {
        for(size_t j = 0; j < nf + nd + ne; j ++)
        {
            Grecoland[i][j] = GEP[i - nf - nd][j - nf - nd];
        }
    }
    puentes p = MPuentes(Fobos, Deimos, Europa, nf, nd, ne);
    puente p1 = p.p1, p2 = p.p2;
    Grecoland[p1.v1][p1.v2] = p1.coste;
    CosteConst += costePuente + (costeLongPuente * p1.coste);
    Grecoland[p1.v2][p1.v1] = p1.coste;
    CosteConst += costePuente + (costeLongPuente * p1.coste);
    Grecoland[p2.v1][p2.v2] = p2.coste;
    CosteConst += costePuente + (costeLongPuente * p2.coste);
    Grecoland[p2.v2][p2.v1] = p2.coste;
    CosteConst += costePuente + (costeLongPuente * p2.coste);
    return CosteConst;
}

puentes MPuentes(vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, size_t nf, size_t nd, size_t ne)
{
    puentes p;
    puente p1, p2;
    puente FD, FE, DE;
    FD.coste = GrafoP<double>::INFINITO;
    FE.coste = GrafoP<double>::INFINITO;
    DE.coste = GrafoP<double>::INFINITO;
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < nd; j++)
        {
            double coste = distancia(Fobos[i], Deimos[j]);
            if(coste < FD.coste)
            {
                FD.coste = coste;
                FD.c1 = Fobos[i];
                FD.c2 = Deimos[j];
                FD.v1 = i;
                FD.v2 = j + nf;
            }
        }
    }
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < ne; j++)
        {
            double coste = distancia(Fobos[i], Europa[j]);
            if(coste < FE.coste)
            {
                FD.coste = coste;
                FD.c1 = Fobos[i];
                FD.c2 = Europa[j];
                FD.v1 = i;
                FD.v2 = j + nf + nd;
            }
        }
    }
    for(size_t i = 0; i < nd; i++)
    {
        for(size_t j = 0; j < ne; j++)
        {
            double coste = distancia(Deimos[i], Europa[j]);
            if(coste < DE.coste)
            {
                FD.coste = coste;
                FD.c1 = Deimos[i];
                FD.c2 = Europa[j];
                FD.v1 = i;
                FD.v2 = j + nf;
            }
        }
    }
    p1.coste = std::min({FD.coste, FE.coste, DE.coste});
    if(p1.coste == FD.coste)
    {
        p1.c1 = FD.c1;
        p1.c2 = FD.c2;
        p1.v1 = FD.v1;
        p1.v2 = FD.v2;
        p2.coste = std::min(FE.coste, DE.coste);
        if(p2.coste == FE.coste)
        {
            p2.c1 = FE.c1;
            p2.c2 = FE.c2;
            p2.v1 = FE.v1;
            p2.v2 = FE.v2;
        }
        else
        {
            p2.c1 = DE.c1;
            p2.c2 = DE.c2;
            p2.v1 = DE.v1;
            p2.v2 = DE.v2;
        }
    }
    if(p1.coste == FE.coste)
    {
        p1.c1 = FE.c1;
        p1.c2 = FE.c2;
        p1.v1 = FE.v1;
        p1.v2 = FE.v2;
        p2.coste = std::min(FD.coste, DE.coste);
        if(p2.coste == FD.coste)
        {
            p2.c1 = FD.c1;
            p2.c2 = FD.c2;
            p2.v1 = FD.v1;
            p2.v2 = FD.v2;
        }
        else
        {
            p2.c1 = DE.c1;
            p2.c2 = DE.c2;
            p2.v1 = DE.v1;
            p2.v2 = DE.v2;
        }
    }
    if(p1.coste == DE.coste)
    {
        p1.c1 = DE.c1;
        p1.c2 = DE.c2;
        p1.v1 = DE.v1;
        p1.v2 = DE.v2;
        p2.coste = std::min(FD.coste, FE.coste);
        if(p2.coste == FD.coste)
        {
            p2.c1 = FD.c1;
            p2.c2 = FD.c2;
            p2.v1 = FD.v1;
            p2.v2 = FD.v2;
        }
        else
        {
            p2.c1 = FE.c1;
            p2.c2 = FE.c2;
            p2.v1 = FE.v1;
            p2.v2 = FE.v2;
        }
    }
    p.p1 = p1;
    p.p2 = p2;
    return p;
}
