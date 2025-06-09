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
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

std::vector<int> pedidos = {0, 7, 4, 10, 3};

int Pedido(int cliente)
{
    return pedidos[cliente];
}

bool quedanClientes(const std::vector<int>& falta)
{
    for (int f : falta)
    {
        if (f > 0)
        {
            return true;
        }
    }
    return false;
}

// Esta función NO suma distancia, solo busca el más cercano pendiente
vertice siguiente(const matriz<tCoste>& MC, vertice actual, const std::vector<int>& falta)
{
    tCoste minDistancia = GrafoP<int>::INFINITO;
    vertice siguienteCliente = actual;

    for(size_t i = 0; i < falta.size(); i++)
    {
        if(falta[i] > 0)
        {
            tCoste dist = MC[actual][i];
            if(dist < minDistancia)
            {
                minDistancia = dist;
                siguienteCliente = i;
            }
        }
    }
    return siguienteCliente;
}

tCoste distribuidor(GrafoP<int>& G, int capacidad, vertice origen)
{
    size_t n = G.numVert();
    int CapActual = capacidad;
    tCoste distancia = 0;
    vertice actual = origen;
    matriz<vertice> MV(n);
    matriz<tCoste> MC = Floyd(G, MV);
    std::vector<int> falta(n);
    for(size_t i = 0; i < falta.size(); i++)
    {
        falta[i] = Pedido(i);
    }
    while(quedanClientes(falta))
    {
        if(actual == origen)
        {
            CapActual = capacidad;
            vertice siguienteCliente = siguiente(MC, actual, falta);
            distancia += MC[actual][siguienteCliente];
            actual = siguienteCliente;
        }
        else
        {
            if(CapActual >= falta[actual])
            {
                CapActual -= falta[actual];
                falta[actual] = 0;
            }
            else
            {
                falta[actual] -= CapActual;
                CapActual = 0;
            }
            if(CapActual == 0)
            {
                distancia += MC[actual][origen];
                actual = origen;
            }
            else
            {
                vertice siguienteCliente = siguiente(MC, actual, falta);
                distancia += MC[actual][siguienteCliente];
                actual = siguienteCliente;
            }
        }
    }
    // Si terminó el día en un cliente, puede (opcionalmente) regresar al origen
    distancia += MC[actual][origen];
    return distancia;
}

int main() {
    const int N = 5; // 0 = almacén, 1-4 = clientes
    GrafoP<int> G(N);
    // Inicializar distancias
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            G[i][j] = (i == j) ? 0 : GrafoP<int>::INFINITO;
    // Conexiones simétricas
    G[0][1] = G[1][0] = 5;
    G[0][2] = G[2][0] = 8;
    G[0][3] = G[3][0] = 12;
    G[0][4] = G[4][0] = 10;
    G[1][2] = G[2][1] = 3;
    G[2][3] = G[3][2] = 2;
    G[3][4] = G[4][3] = 4;
    int capacidadCamion = 10;
    vertice origen = 0;
    tCoste total = distribuidor(G, capacidadCamion, origen);
    std::cout << "Distancia total recorrida: " << total << std::endl;
    return 0;
}