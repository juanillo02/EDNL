/*
La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del valle del Jerte (Cáceres), teniendo en cuenta las siguientes
premisas: 
− El coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final debe tener un número mínimo de canales. 
− El Ministerio de Fomento nos subvenciona por m3/sg de caudal, luego el conjunto de los canales debe admitir el mayor caudal posible,
pero por otra parte, el coste de abrir cada canal es proporcional a su longitud, por lo que el conjunto de los canales también debería medir lo
menos posible. Así pues, la solución óptima debería combinar adecuadamente ambos factores. 
Dada la matriz de distancias entre las diferentes ciudades del valle del Jerte, otra matriz con los diferentes caudales máximos admisibles entre
estas ciudades teniendo en cuenta su orografía, la subvención que nos da Fomento por m3/sg. de caudal y el coste por km. de canal, implementen
un subprograma que calcule qué canales y de qué longitud y caudal deben construirse para minimizar el coste total de la red de canales.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>
#include <cmath>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct canal
{
    vertice origen, destino;
    double longitud;
    tCoste caudal;
    canal(vertice o, vertice d, double l, tCoste c): origen(o), destino(d), longitud(l), caudal(c) {}
};

std::vector<canal> calculo(matriz<int>& m, matriz<int>& caudales, double subvencion, tCoste coste)
{
    size_t n = m.dimension();
    GrafoP<int> G(n);
    // Construir grafo ponderado con el "coste total" de cada canal
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if (i != j)
            {
                G[i][j] = (m[i][j] * coste) - (caudales[i][j] * subvencion);
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
    }
    // Ejecutar Kruskal para obtener solución con mínimo coste
    GrafoP<int> GK = Kruskall(G);
    std::vector<canal> resultado;
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(GK[i][j] != GrafoP<int>::INFINITO)
            {
                resultado.push_back(canal(i, j, m[i][j], caudales[i][j]));
            }
        }
    }
    return resultado;
}

int main()
{
    const int N = 4;
    matriz<int> dist(N);
    matriz<int> caudales(N);

    // Rellenar matrices de ejemplo (distancias en km, caudales en m3/s)
    dist[0][1] = dist[1][0] = 5;
    dist[0][2] = dist[2][0] = 4;
    dist[1][2] = dist[2][1] = 3;
    dist[1][3] = dist[3][1] = 6;
    dist[2][3] = dist[3][2] = 2;

    caudales[0][1] = caudales[1][0] = 10;
    caudales[0][2] = caudales[2][0] = 8;
    caudales[1][2] = caudales[2][1] = 12;
    caudales[1][3] = caudales[3][1] = 6;
    caudales[2][3] = caudales[3][2] = 5;

    double subvencion = 2.0;  // €/m3/s
    int costeKm = 3;          // €/km

    std::vector<canal> resultado = calculo(dist, caudales, subvencion, costeKm);

    std::cout << "Canales construidos:\n";
    for (const auto& c : resultado)
    {
        std::cout << "Ciudad " << c.origen << " <-> Ciudad " << c.destino
                  << " | Longitud: " << c.longitud << " km"
                  << " | Caudal: " << c.caudal << " m3/s\n";
    }

    return 0;
}
