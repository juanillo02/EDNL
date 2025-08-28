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

struct coordenada
{
    int x,y;
};

//carreteras y puentes al menor coste.
//coste por unidad de longitud es distinto en puentes y carreteras. osea el coste de construir una carretera es G[i][j] = costeC + (CosteAdC * distanciaeuclidea)


double distanciaeuclidea(coordenada c1, coordenada c2)
{
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

GrafoP<double> Grecoland( std::vector<coordenada> Fobos, std::vector<coordenada> Deimos, std::vector<coordenada> Europa, double CosteC, double CosteP, double CosteAdC, double CosteAdP)
{
    int n = n1+n2+n3;
    GrafoP<double> G(n);
    //introducimos las carreteras
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < n1; j++)
        {
            if(i != j)
            G[i][j] = G[j][i] = CosteC + (CosteAdC * distanciaeuclidea(Fobos[i], Fobos[j]));
        }
    }
    for(int i = 0; i < n2; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            if(i != j)
            G[i+n1][j+n1] = G[j+n1][i+n1] = CosteC + (CosteAdC * distanciaeuclidea(Deimos[i], Deimos[j]));
        }
    }
    for(int i = 0; i < n3; i++)
    {
        for(int j = 0; j < n3; j++)
        {
            if(i != j)
            G[i+n1+n2][j+n1+n2] = G[j+n1+n2][i+n1+n2] = CosteC + (CosteAdC * distanciaeuclidea(Europa[i], Europa[j]));
        }
    }
    //introducimos puentes
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            G[i][j+n1] = G[j+n1][i] = CosteP + (CosteAdP * distanciaeuclidea(Fobos[i], Deimos[j]));
        }
    }
    for(int i = 0; i < n2; i++)
    {
        for(int j = 0; j < n3; j++)
        {
            G[i+n1][j+n1+n2] = G[j+n1+n2][i+n1] = CosteP + (CosteAdP * distanciaeuclidea(Deimos[i], Europa[j]));
        }
    }
    for(int i = 0; i < n3; i++)
    {
        for(int j = 0; j < n1; j++)
        {
            G[i+n1+n2][j] = G[j][i+n1+n2] = CosteP + (CosteAdP * distanciaeuclidea(Europa[i], Fobos[j]));
        }
    }
    GrafoP<double> GK(n);
    GK = Kruskall(G);
    return GK;
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