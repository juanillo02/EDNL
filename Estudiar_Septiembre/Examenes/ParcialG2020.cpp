/*
    Pedido de bebidas hacia los clientes
*/
#include <vector>
#include <algorithm>
#include "../Grafos/matriz.h"
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct Cliente
{
    bool servido = false;
    size_t pedido;
};

tCoste Distancia(GrafoP<int>& G, size_t cantidadBebidas, vertice& centro)
{
    matriz<vertice> P;
    matriz<tCoste> M = Floyd(G, P);
    tCoste DistTotal = 0;
    std::vector<Cliente> ClienteServido(G.numVert());
    ClienteServido[centro].servido = true;
    vertice clienteActual = centro;
    size_t Capacidad = cantidadBebidas;
    while(!Clientes(ClienteServido))
    {
        if(clienteActual == centro)
        {
            Capacidad = cantidadBebidas;
            Siguiente(M, ClienteServido, clienteActual, centro, DistTotal);
        }
        else
        {
            if(Capacidad - Pedido(ClienteServido, clienteActual) <= 0)
            {
                Capacidad = 0;
                DistTotal += M[clienteActual][centro];
                clienteActual = centro;
            }
            else
            {
                Capacidad -= Pedido(ClienteServido, clienteActual);
                ClienteServido[clienteActual].servido = true;
                clienteActual = Siguiente(M, ClienteServido, clienteActual, centro, DistTotal);
            }
        }
    }
    return DistTotal;
}

bool Clientes(std::vector<Cliente> Clientes)
{
    for(Cliente faltan : Clientes)
    {
        if(faltan.servido == false)
        {
            return false;
        }
    }
}

size_t Pedido(std::vector<Cliente> Clientes, vertice& actual)
{
    return Clientes[actual].pedido;
}

vertice Siguiente(matriz<tCoste>& M, std::vector<Cliente> Clientes, vertice& actual, vertice& centro, tCoste Distancia)
{
    vertice siguiente;
    tCoste minimo = GrafoP<tCoste>::INFINITO;
    for(size_t i = 0; i < M.dimension(); ++i)
    {
        if(M[actual][i] < minimo && !Clientes[i].servido)
        {
            minimo = M[actual][i];
            siguiente = i;
        }
    }
    return siguiente;
}