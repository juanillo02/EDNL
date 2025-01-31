/*
Se dispone de tres grafos que representan la matriz de costes para viajes en un determinado país, pero por diferentes medios de transporte
(tren, autobús y avión). Por supuesto los tres grafos tendrán el mismo número de nodos, N. Dados los siguientes datos: los tres grafos, una ciudad
de origen, una ciudad de destino, el coste del taxi para cambiar, dentro de una ciudad, de la estación de tren a la de autobús o viceversa
(taxi-tren-bus) y el coste del taxi desde el aeropuerto a la estación de tren o la de autobús, o viceversa (taxi-aeropuerto-tren/bus) y asumiendo
que ambos costes de taxi (distintos entre sí, son dos costes diferentes) son constantes e iguales para todas las ciudades, implementa un
subprograma que calcule el camino y el coste mínimo para ir de la ciudad origen a la ciudad destino.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct viaje
{
    tCoste costemin;
    tCamino ruta;
};

viaje precio(GrafoP<int>& tren, GrafoP<int>& bus, GrafoP<int>& avion, vertice origen, vertice destino, tCoste taxiestacion, tCoste taxiaeropuerto)
{
    size_t n = tren.numVert();
    GrafoP<int> G(n*3);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n;j++)
        {
            G[i][j] = tren[i][j];
        }
    }
    for(vertice i = n; i < n*2; i++)
    {
        for(vertice j = n; j < n*2; j++)
        {
            G[i][j] = bus[i-n][j-n];
        }
    }
    for(vertice i = n*2; i < n*3; i++)
    {
        for(vertice j = n*2; j < n*3; j++)
        {
            G[i][j] = avion[i-(n*2)][j-(n*2)];
        }
    }
    for(vertice i = 0; i < n; i++)
    {
        G[i+n][i] = taxiaeropuerto;
        G[i][n+i] = taxiaeropuerto;
        G[i+(n*2)][i] = taxiaeropuerto;
        G[i][i+(n*2)] = taxiaeropuerto;
        G[i+(n*2)][i+n] = taxiestacion;
        G[i+n][i+(n*2)] = taxiestacion;
    }
    vector<vertice> V1(n*3), V2(n*3), V3(n*3);
    vector<tCoste> VD1 = dijsktra(G, origen, V1), VD2 = dijsktra(G, origen + n, V2), VD3 = dijsktra(G, origen + (n*2), V3);
    vertice o, d;
    size_t vVehiculo = 1;
    tCoste minimo = std::min(VD[destino], VD[destino+n]);
    if(VD1[destino] < VD1[destino + n])
    {
        o = origen;
        d = destino;
    }
    else
    {
        o = origen;
        d = destino + n;
    }
    if(VD1[destino+(n*2)] < minimo)
    {
        o = origen;
        d = destino + (n*2);
    }
    minimo = std::min(minimo, VD1[destino + (n*2)]);
    if(VD2[destino] < minimo)
    {
        o = origen + n;
        d = destino;
        vVehiculo = 2;
    }
    minimo = std::min(minimo, VD2[destino]);
    if(VD2[destino + n] < minimo)
    {
        o = origen + n;
        d = destino + n;
        vVehiculo = 2;
    }
    minimo = std::min(minimo, VD2[destino + n]);
    if(VD2[destino + (n*2)] < minimo)
    {
        o = origen + n;
        d = destino + n*2;
        vVehiculo = 2;
    }
    minimo = std::min(minimo, VD2[destino + (n*2)]);
    if(VD3[destino] < minimo)
    {
        o = origen + (n*2);
        d = destino;
        vVehiculo = 3;
    }
    minimo = std::min(minimo, VD3[destino]);
    if(VD3[destino + n] < minimo)
    {
        o = origen + (n*2);
        d = destino + n;
        vVehiculo = 3;
    }
    minimo = std::min(minimo, VD3[destino + n]);
    if(VD3[destino + (n*2)] < n)
    {
        o = origen + (n*2);
        d = destino + (n*2);
        vVehiculo = 3;
    }
    minimo = std::min(minimo, VD3[destino + (n*2)]);
    viaje resultado;
    resultado.costemin = minimo;
    if(vVehiculo == 1)
    {
        resultado.ruta = camino<vertice>(o, d, V1);
    }
    else if(vVehiculo == 2)
    {
        resultado.ruta = camino<vertice>(o, d, V2);
    }
    else if(vVehiculo == 3)
    {
        resultado.ruta = camino<vertice>(o, d, V3);
    }
    return resultado;
}