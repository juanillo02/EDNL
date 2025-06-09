/*
El archipielago de Grecoland (Nozuelandia) está formado unicamente por tres islas, Fobos, Deimos y Europa y tienen N1, N2 y N3 ciudades,
respectivamente, todas ellas costeras.
Se dispone de la relacion de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.
Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. Las condiciones del programa
COMUNICA indican que se sufragaran
todos los costes de construcción de las comunicaciones (carreteras y puentes) al menor coste posible.
Se sabe que la mera construccion de un puente o carretera ya implica una serie de costes fijos, que difieren para el caso de carretera y puente.
Además, el coste por unidad de longitud para carreteras y puentes tambien es distinto.
En estas condiciones se debe calcular (mediante una funcion) que carreteras y puentes deben construirse para comunicar entre si todas las
ciudades de Grecoland, dados los siguientes datos:
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

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct coordenada
{
    int x, y;
};

struct puente
{
    vertice v1, v2;
    coordenada c1, c2;
    tCoste coste;
};

struct puentes
{
    puente p1, p2;
};

tCoste distancia(const coordenada& c1, const coordenada& c2)
{
    return static_cast<tCoste>(std::sqrt(std::pow(c1.x - c2.x, 2) + std::pow(c1.y - c2.y, 2)));
}

puentes mejorespuentes(std::vector<coordenada>& ciudadesF, std::vector<coordenada>& ciudadesD, std::vector<coordenada>& ciudadesE, size_t nf, size_t nd, size_t ne)
{
    puentes p;
    puente p1, p2, FD, FE, DE;
    FD.coste = GrafoP<tCoste>::INFINITO;
    FE.coste = GrafoP<tCoste>::INFINITO;
    DE.coste = GrafoP<tCoste>::INFINITO;
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < nd; j++)
        {
            double coste = distancia(ciudadesF[i], ciudadesD[j]);
            if(coste < FD.coste)
            {
                FD.coste = coste;
                FD.c1 = ciudadesF[i];
                FD.c2 = ciudadesD[j];
                FD.v1 = i;
                FD.v2 = j + nf;
            }
        }
    }
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < ne; j++)
        {
            double coste = distancia(ciudadesF[i], ciudadesE[j]);
            if(coste < FE.coste)
            {
                FE.coste = coste;
                FE.c1 = ciudadesF[i];
                FE.c2 = ciudadesE[j];
                FE.v1 = i;
                FE.v2 = j + nf + nd;
            }
        }
    }
    for(size_t i = 0; i < nd; i++)
    {
        for(size_t j = 0; j < ne; j++)
        {
            double coste = distancia(ciudadesD[i], ciudadesE[j]);
            if(coste < DE.coste)
            {
                DE.coste = coste;
                DE.c1 = ciudadesD[i];
                DE.c2 = ciudadesE[j];
                DE.v1 = i + nf;
                DE.v2 = j + nf + nd;
            }
        }
    }
    p1.coste = std::min(std::min(FD.coste, FE.coste), DE.coste);
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

tCoste Grecoland(std::vector<coordenada>& ciudadesF, std::vector<coordenada>& ciudadesD, std::vector<coordenada>& ciudadesE, tCoste costeP, tCoste costeC, tCoste lonP, tCoste lonC)
{
    size_t n1 = ciudadesF.size(), n2 = ciudadesD.size(), n3 = ciudadesE.size();
    tCoste construccion = 0;
    GrafoP<tCoste> GFP(n1), GDP(n2), GEP(n3);
    for(vertice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            if(i != j)
            {
                GFP[i][j] = distancia(ciudadesF[i], ciudadesF[j]);
            }
        }
    }
    for(vertice i = 0; i < n2; i++)
    {
        for(vertice j = 0; j < n2; j++)
        {
            if(i != j)
            {
                GDP[i][j] = distancia(ciudadesD[i], ciudadesD[j]);
            }
        }
    }
    for(vertice i = 0; i < n3; i++)
    {
        for(vertice j = 0; j < n3; j++)
        {
            if(i != j)
            {
                GEP[i][j] = distancia(ciudadesE[i], ciudadesE[j]);
            }
        }
    }
    GrafoP<int> GFPPrim = Prim(GFP), GDPPrim = Prim(GDP), GEPPrim = Prim(GEP);
    for(vertice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            if(GFPPrim[i][j] != GrafoP<tCoste>::INFINITO)
            {
                construccion += costeC + (lonC * GFPPrim[i][j]);
            }
        }
    }
    for(vertice i = 0; i < n2; i++)
    {
        for(vertice j = 0; j < n2; j++)
        {
            if(GDPPrim[i][j] != GrafoP<tCoste>::INFINITO)
            {
                construccion += costeC + (lonC * GDPPrim[i][j]);
            }
        }
    }
    for(vertice i = 0; i < n3; i++)
    {
        for(vertice j = 0; j < n3; j++)
        {
            if(GEPPrim[i][j] != GrafoP<tCoste>::INFINITO)
            {
                construccion += costeC + (lonC * GEPPrim[i][j]);
            }
        }
    }
    GrafoP<tCoste> Grecoland(n1 + n2 + n3);
    for(vertice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            Grecoland[i][j] = GFPPrim[i][j];
        }
    }
    for(vertice i = n1; i < n1 + n2; i++)
    {
        for(vertice j = n1; j < n1 + n2; j++)
        {
            Grecoland[i][j] = GDPPrim[i - n1][j - n1];
        }
    }
    for(vertice i = n1 + n2; i < n1 + n2 + n3; i++)
    {
        for(vertice j = n1 + n2; j < n1 + n2 + n3; j++)
        {
            Grecoland[i][j] = GEPPrim[i - (n1 + n2)][j - (n1 + n2)];
        }
    }
    puentes p = mejorespuentes(ciudadesF, ciudadesD, ciudadesE, n1, n2, n3);
    puente p1 = p.p1;
    puente p2 = p.p2;
    Grecoland[p1.v1][p1.v2] = p1.coste;
    construccion += costeP + (lonP * p1.coste);
    Grecoland[p1.v2][p1.v1] = p1.coste;
    construccion += costeP + (lonP * p1.coste);
    Grecoland[p2.v1][p2.v2] = p2.coste;
    construccion += costeP + (lonP * p2.coste);
    Grecoland[p2.v2][p2.v1] = p2.coste;
    construccion += costeP + (lonP * p2.coste);
    return construccion;
}

int main()
{
    std::vector<coordenada> fobos = {{0, 0}, {0, 1}};
    std::vector<coordenada> deimos = {{5, 0}, {5, 1}};
    std::vector<coordenada> europa = {{10, 0}, {10, 1}};
    double coste = Grecoland(
        fobos, deimos, europa,
        100,   // Coste fijo puente
        10,    // Coste fijo carretera
        5,     // Coste por unidad de longitud puente
        1      // Coste por unidad de longitud carretera
    );
    std::cout << "Coste total del proyecto COMUNICA: " << coste << " unidades monetarias\n";
    return 0;
}