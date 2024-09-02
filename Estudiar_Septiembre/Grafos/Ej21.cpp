/*
La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del valle del Jerte (Cáceres), teniendo en cuenta las siguientes premisas:
− El coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final debe tener un número mínimo de canales.
− El Ministerio de Fomento nos subvenciona por m3 /sg de caudal, luego el conjunto de los canales debe admitir el mayor caudal posible, pero por otra parte, el coste
de abrir cada canal es proporcional a su longitud, por lo que el conjunto de los canales también debería medir lo menos posible. Así pues, la solución óptima
debería combinar adecuadamente ambos factores.
Dada la matriz de distancias entre las diferentes ciudades del valle del Jerte, otra matriz con los diferentes caudales máximos admisibles entre estas ciudades teniendo en
cuenta su orografía, la subvención que nos da Fomento por m3 /sg. de caudal y el coste por km. de canal, implementen un subprograma que calcule qué canales y de qué
longitud y caudal deben construirse para minimizar el coste total de la red de canales.
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
#include "apo.h"
#include <vector>
#include <cmath>
#include <algorithm>

typedef typename GrafoP<int>::tCoste tCoste;

GrafoP<tCoste> JerteGordo(const GrafoP<tCoste>& ciudades, const GrafoP<tCoste>& caudal, int subvencion, int coste)
{
    size_t n = ciudades.numVert();
    GrafoP<tCoste> G(n);
    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; ++j)
        {
            G[i][j] = ciudades[i][j] * coste - caudal[i][j] * subvencion;
        }
    }
    return Kruskall(G);
}