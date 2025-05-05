/*
El archipiélago de las Huríes acaba de ser devastado por un maremoto de dimensiones desconocidas hasta la fecha. La primera consecuencia ha sido
que todos y cada uno de los puentes que unían las diferentes ciudades de las tres islas han sido destruidos. En misión de urgencia las Naciones
Unidas han decidido construir el mínimo número de puentes que permitan unir las tres islas. Asumiendo que el coste de construcción de los puentes
implicados los pagará la ONU, por lo que se considera irrelevante, nuestro problema es decidir qué puentes deben construirse. Las tres islas de 
las Huríes tienen respectivamente N1, N2 y N3 ciudades, de las cuales C1, C2 y C3 son costeras (obviamente C1 ≤ N1, C2 ≤ N2 y C3 ≤ N3). Nuestro
problema es elegir los puentes a construir entre todos los posibles. Por tanto, escogeremos aquellos puentes que minimicen el coste global de
viajar entre todas las ciudades de las tres islas, teniendo en cuenta las siguientes premisas: 
1. Se asume que el coste viajar entre las ciudades que unan los puentes es 0. 
2. La ONU subvencionará únicamente el número mínimo de puentes necesario para comunicar las tres islas. 
3. Para poder plantearse las mejoras en el transporte que implica la construcción de un puente frente a cualquier otro, se asume que se
realizarán exactamente el mismo número de viajes entre cualesquiera ciudades del archipélago. Dicho de otra forma, todos los posibles trayectos
a realizar dentro del archipiélago son igual de importantes. Dadas las matrices de costes directos de las tres islas y las listas de ciudades
costeras del archipiélago, implementad un subprograma que calcule los puentes a construir en las condiciones anteriormente descritas. 
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct puente
{
    vertice origen, destino;
};

vector<puente> construir(GrafoP<int>& G1, GrafoP<int>& G2, GrafoP<int>& G3, vector<vertice>& costeras1, vector<vertice>& costeras2, vector<vertice>& costeras3)
{
    size_t n1 = G1.numVert(), n2 = G2.numVert(), n3 = G3.numVert();
    size_t n = n1 + n2 + n3;
    GrafoP<int> G(n);
    for(vertice i = 0; i < n1; i++)
    {
        for(vertice j = 0; j < n1; j++)
        {
            G[i][j] = G1[i][j];
        }
    }
    for(vertice i = n1; i < n1+n2; i++)
    {
        for(vertice j = n1; j < n1+n2; j++)
        {
            G[i][j] = G1[i-n1][j-n1];
        }
    }
    for(vertice i = n1+n2; i < n1+n2+n3; i++)
    {
        for(vertice j = n1+n2; j < n1+n2+n3; j++)
        {
            G[i][j] = G1[i-n1-n2][j-n1-n2];
        }
    }
    for(vertice i = 0; i < costeras2.size(); i++)
    {
        costeras2[i] += n1;
    }
    for(vertice i = 0; i < costeras3.size(); i++)
    {
        costeras3[i] += (n1+n2);
    }
    matriz<vertice> MV(n);
    matriz<tCoste> MC;
    tCoste minimo = GrafoP<int>::INFINITO, coste;
    vertice v1a, v1b, v2a, v2b;
    for(size_t i = 0; i < costeras1.size(); i++)
    {
        for(size_t j = 0; j < costeras2.size(); j++)
        {
            for(size_t k = 0; k < costeras3.size(); k++)
            {
                G[costeras1[i]][costeras2[j]] = 0;
                G[costeras2[j]][costeras1[i]] = 0;
                G[costeras1[i]][costeras3[k]] = 0;
                G[costeras3[k]][costeras1[i]] = 0;
                MC = Floyd(G, MV);
                coste = total(MC, n);
                if(coste < minimo)
                {
                    minimo = coste;
                    v1a = costeras1[i];
                    v1b = costeras2[j];
                    v2a = costeras1[k];
                    v2b = costeras3[i];
                }
                G[costeras1[i]][costeras2[j]] = GrafoP<int>::INFINITO;
                G[costeras2[j]][costeras1[i]] = GrafoP<int>::INFINITO;
                G[costeras1[i]][costeras3[k]] = GrafoP<int>::INFINITO;
                G[costeras3[k]][costeras1[i]] = GrafoP<int>::INFINITO;
            }
        }
    }
    vector<puente> resultado(2);
    resultado[0].origen = v1a;
    resultado[0].destino = v1b;
    resultado[1].origen = v2a;
    resultado[1].destino = v2b;
    return resultado;
}

tCoste total(matriz<tCoste> G, size_t n)
{
    tCoste suma = 0;
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            if(G[i][j] != GrafoP<int>::INFINITO)
            {
                suma += G[i][j];
            }
        }
    }
    return suma;
}