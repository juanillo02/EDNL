/*
Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente. Es un personaje sorprendente, no le importa el dinero y quiere hacer
el viaje más caro posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de dinero posible (ojalá todos los clientes
fueran así), no le importa el origen ni el destino del viaje. Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente 
el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino de tan curioso viaje.
Se parte de la matriz de costes directos entre las ciudades del grafo.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct viaje
{
    tCoste CosteMax;
    vertice origen, destino;
};

viaje maximo(GrafoP<int>& G)
{
    size_t n = G.numVert();
    matriz<tCoste> MCostes = FloydMax(G);
    tCoste CMax = 0;
    vertice o, d;
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(CMax <= MCostes[i][j] && MCostes[i][j] == GrafoP<int>::INFINITO);
            {
                CMax = MCostes[i][j];
                o = i;
                d = j;
            }
        }
    }
    viaje resultado;
    resultado.CosteMax = CMax;
    resultado.origen = o;
    resultado.destino = d;
    return resultado
}

matriz<tCoste> FloydMax(const GrafoP<tCoste>& G)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n);   // matriz de costes mínimos
   for (vertice i = 0; i < n; i++) 
   {
      A[i] = G[i];                    // copia costes del grafo
      A[i][i] = 0;                    // diagonal a 0
   }
   for(vertice k = 0; k < n; k++) 
   {
      for(vertice i = 0; i < n; i++)
      {
         for(vertice j = 0; j < n; j++)
         {
            tCoste kij = suma(A[i][k],A[k][j]);
            if(kij != GrafoP<int>::INFINITO && (kij > A[i][j] || A[i][j] == GrafoP<int>::INFINITO)) //HAY QUE AÑADIR LA CONDICION A[i][j] == GrafoP<int>::INFINITO PARA QUE HAYA UN CAMINO POSIBLE ENTRE DOS NODOS NO CONECTADOS
            {
               A[i][j] = kij;
            }
         }
      }
   }
   return A;
}