/*El archipielago de Grecoland (Nozuelandia) está formado unicamente por tres islas, Fobos, Deimos y Europa y tienen N1, N2 y N3 ciudades
respectivamente, todas ellas costeras. Se dispone de la relacion de ciudades de cada una de las tres islas, representadas por sus coordenadas
cartesianas. Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. Las condiciones del
programa COMUNICA indican que se sufragaran todos los costes de construcción de las comunicaciones (carreteras y puentes) al menor coste posible.
Se sabe que la mera construccion de un puente o carretera ya implica una serie de costes fijos, que difieren para el caso de carretera y puente.
Además, el coste por unidad de longitud para carreteras y puentes tambien es distinto. En estas condiciones se debe calcular (mediante una
funcion) que carreteras y puentes deben construirse para comunicar entre si todas las ciudades de Grecoland, dados los siguientes datos:
1. Relacion de las ciudades de Fobos, representadas mediante sus coordenadas cartesianas
2. Relacion de las ciudades de Deimos, representadas mediante sus coordenadas cartesianas
3. Relacion de las ciudades de Europa, representadas mediante sus coordenadas cartesianas
4. Coste inicial de construccion de un puente
5. Coste inicial de construccion de una carreteras
6. Coste adicional por unidad de longitud de construccion de un puente
7. Coste adicional por unidad de longitud de construccion de una carretera
*/
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>
#include <iostream>

typedef GrafoP<double>::tCoste tCoste;
typedef GrafoP<double>::vertice vertice;

struct ciudad
{
    double x, y;
}

struct puente
{
    vertice v1, v2;
    ciudad c1, c2;
    tCoste coste;
};

struct puentes
{
    puente p1, p2;
};

tCoste Grecoland(std::vector<ciudad>& ciudadesF, std::vector<ciudad>& ciudadesD, std::vector<ciudad>& ciudadesE, tCoste costeP, tCoste costeC, tCoste lonP, tCoste lonC)
{
    size_t n1 = ciudadesF.size(), n2 = ciudadesD.size(), n3 = ciudadesE.size();
    tCoste construccion = 0;
    GrafoP<double> GF(n1), GD(n2), GE(n3);
    for(verice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            if(i != j)
            {
                GF[i][j] = distancia(ciudadesF[i], ciudadesF[j]);
            }
        }
    }
    for(verice i = 0; i < n2; i++)
    {
        for(vertice j = 0; j < n2; j++)
        {
            if(i != j)
            {
                GD[i][j] = distancia(ciudadesD[i], ciudadesD[j]);
            }
        }
    }
    for(verice i = 0; i < n3; i++)
    {
        for(vertice j = 0; j < n3; j++)
        {
            if(i != j)
            {
                GE[i][j] = distancia(ciudadesE[i], ciudadesE[j]);
            }
        }
    }
    GrafoP<double> GFP = Prim(GF), GDP = Prim(GD), GEP = Prim(GE);
    for(verice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            if(GFP[i][j] != GrafoP<double>::INFINITO)
            {
                construccion += costeC + (lonC + GFP[i][j]);
            }
        }
    }
    for(verice i = 0; i < n2; i++)
    {
        for(vertice j = 0; j < n2; j++)
        {
            if(GDP[i][j] != GrafoP<double>::INFINITO)
            {
                construccion += costeC + (lonC + GDP[i][j]);
            }
        }
    }
    for(verice i = 0; i < n3; i++)
    {
        for(vertice j = 0; j < n3; j++)
        {
            if(GEP[i][j] != GrafoP<double>::INFINITO)
            {
                construccion += costeC + (lonC + GEP[i][j]);
            }
        }
    }
    GrafoP<double> Grecoland(n1+n2+n3);
    for(vertice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            Grecoland[i][j] = GFP[i][j];
        }
    }
    for(vertice i = n1; i < n1+n2; i++)
    {
        for(vertice j = n1; j < n1+n2; j++)
        {
            Grecoland[i][j] = GDP[i-n1][j-n2];
        }
    }
    for(vertice i = n1+n2; i < n1+n2+n3; i++)
    {
        for(vertice j = n1+n2; i < n1+n2+n3; j++)
        {
            Grecoland[i][j] = GEP[i-(n1+n2)][j-(n1+n2)];
        }
    }
    puentes p = mejorespuentes(ciudadesF, ciudadesD, ciudadesE, n1, n2, n3);
    puente p1 = p.p1, p2 = p.p2;
    Gecoland[p1.v1][p1.v2] = p1.coste;
    construccion += costeP + (lonP * p1.coste);
    Gecoland[p1.v2][p1.v1] = p1.coste;
    construccion += costeP + (lonP * p1.coste);
    Gecoland[p2.v1][p2.v2] = p2.coste;
    construccion += costeP + (lonP * p2.coste);
    Gecoland[p2.v2][p2.v1] = p2.coste;
    construccion += costeP + (lonP * p2.coste);
    return construccion;
}

double distancia(ciudad c1, ciudad c2)
{
    return std::sqrt(std::pow(abs(c1.x - c2.x), 2) + std::pow(abs(c1.y - c2.y), 2));
}

puentes mejorespuentes(std::vector<ciudad>& ciudadesF, std::vector<ciudad>& ciudadesD, std::vector<ciudad>& ciudadesE, size_t nf, size_t nd, size_t ne)
{
    puentes p;
    puente p1, p2, FD, FE, DE;
    FD.coste = GrafoP<double>::INFINITO;
    FE.coste = GrafoP<double>::INFINITO;
    DE.coste = GrafoP<double>::INFINITO;
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < nd; j++)
        {
            double coste = distancia(ciudadesFobos[i], ciudadesDeimos[j]);
            if(coste < FD.coste)
            {
                FD.coste = coste;
                FD.c1 = ciudadesFobos[i];
                FD.c2 = ciudadesDeimos[j];
                FD.v1 = i;
                FD.v2 = j + nf;
            }
        }
    }
    for(size_t i = 0; i < nf; i++)
    {
        for(size_t j = 0; j < ne; j++)
        {
            double coste = distancia(ciudadesFobos[i], ciudadesEuropa[j]);
            if(coste < FE.coste)
            {
                FE.coste = coste;
                FE.c1 = ciudadesFobos[i];
                FE.c2 = ciudadesEuropa[j];
                FE.v1 = i;
                FE.v2 = j + nf + nd;
            }
        }
    }
    for(size_t i = 0; i < nd; i++)
    {
        for(size_t j = 0; j < ne; j++)
        {
            double coste = distancia(ciudadesDeimos[i], ciudadesEuropa[j]);
            if(coste < DE.coste)
            {
                DE.coste = coste;
                DE.c1 = ciudadesDeimos[i];
                DE.c2 = ciudadesEuropa[j];
                DE.v1 = i + nf;
                DE.v2 = j + nf + nd;
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