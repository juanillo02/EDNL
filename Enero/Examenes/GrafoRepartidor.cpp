/*
Un repartidor de una empresa de distribución de bebidas tiene que visitar a todos sus clientes cada día. Pero, al comenzar su jornada de trabajo,
no conoce qué cantidad de bebidas tiene que servir a cada cliente, por lo que no puede planificar una ruta óptima para visitarlos a todos.
Por tanto, nuestro repartidor decide llevar a cabo la siguiente estrategia:
- El camión parte del almacén con la máxima carga permitida rumbo a su cliente más próximo.
- El repartidor descarga las cajas de bebidas que le pide el cliente. Si no tiene suficientes cajas en el camión, le entrega todas las que tiene.
Este cliente terminará de ser servido en algún otro momento a lo largo del día, cuando la estrategia de reparto vuelva a llevar al 
repartidor hasta él.
- Después de servir a un cliente:
    o Si quedan bebidas en el camión, el repartidor consulta su sistema de navegación basado en GPS para conocer la ruta que le lleva hasta su
    cliente más próximo pendiente de ser servido.
    o Si no quedan bebidas en el camión, vuelve al almacén por el camino más corto y otra vez carga el camión completamente.
- Después de cargar el camión, el repartidor consulta su sistema de navegación y se va por el camino más corto a visitar al cliente pendiente de
ser servido más próximo. Implementa un subprograma que calcule y devuelva la distancia total recorrida en un día por nuestro repartidor,
a partir de lo siguiente:    
    1. Grafo representado mediante matriz de costes con las distancias de los caminos directos entre los clientes y entre ellos y la central.
    2. Capacidad máxima del camión (cantidad de cajas de bebidas).
    3. Asumiremos que existe una función int Pedido() que devuelve el número de cajas que quedan por servir al cliente en el que se encuentra el
    repartidor.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

tCoste distruidora(GrafoP<int>& G, int capacidad, vertice origen)
{
    size_t n = G.numVert();
    int capacidadactual = capacidad;
    std::vector<bool> visitado(n, false);
    visitado[origen] = true;
    tCoste distancia = 0;
    vertice actual = origen;
    matriz<vertice> MV(n);
    matriz<tCoste> MC = Floyd(G, MV);
    std::vector<int> falta(n);
    for(size_t i = 0; i < falta.size(); i++)
    {
        falta[i] = pedido(i);
    }
    while(!quedanClientes(visitado))
    {
        if(actual == origen)
        {
            capacidadactual = capacidad;
            actual = siguiente(MC, actual, visitado, falta, distancia, capacidadactual, origen);
        }
        else
        {
            if(capacidadactual > falta[actual])
            {
                capacidadactual -= falta[actual];
                visitado[actual] = true;
                falta[actual] = 0;
                actual = siguiente(MC, actual, visitado, falta, distancia, capacidadactual, origen);
            }
            else
            {
                falta[actual] -= capacidadactual;
                capacidadactual = 0;
                actual = siguiente(MC, actual, visitado, falta, distancia, capacidadactual, origen);
            }
        }
    }
    return distancia;
}

bool quedanClientes(std::vector<bool> vector)
{
    bool res = true;
    for(size_t i = 0; i < vector.size(); i++)
    {
        if(vector[i] == false)
        {
            res false;
        }
    }
    return res;
}

vertice siguiente(matri<tCoste> M, vertice actual, std::vector<bool> visitado, std::vector<int> falta, tCoste& distancia, int capacidad, vertice origen)
{
    vertice v;
    tCoste minimo = GrafoP<int>::INFINITO;
    if(capacidad == 0)
    {
        v = origen;
    }
    else
    {
        if(quedanClientes(visitado))
        {
            v = origen;
        }
        else
        {
            for(vertice i = 0; i < falta.size(); i++)
            {
                if(falta[i] > 0 && M[actual][i] < minimo)
                {
                    v = i;
                    minimo = M[actual][i];
                }
            }
        }
    }
    distancia += M[actual][v];
    return v;
}