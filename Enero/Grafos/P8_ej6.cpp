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
#include "particion.h"
#include <math.h>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct canal
{
    vertice origen, destino;
    double longitud;
    tCoste caudal;
};

std::vector<canal> calculo(matriz<int>& m, matriz<int>& caudales, double subvencion, tCoste coste)
{
    size_t n = m.dimension();
    GrafoP<int> G(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            G[i][j] = m[i][j] * coste - caudales[i][j] * subvencion;
        }
    }
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