/*
Eres el orgulloso dueño de la empresa “Cementos de Zuelandia S.A”. Empresa dedicada a la fabricación y distribución de cemento, sita en la capital de Zuelandia. Para
la distribución del cemento entre tus diferentes clientes (ciudades de Zuelandia) dispones de una flota de camiones y de una plantilla de conductores zuelandeses.
El problema a resolver tiene que ver con el carácter del zuelandés. El zuelandés es una persona que se toma demasiadas “libertades” en su trabajo, de hecho, tienes
fundadas sospechas de que tus conductores utilizan los camiones de la empresa para usos particulares (es decir indebidos, y a tu costa) por lo que quieres controlar los
kilómetros que recorren tus camiones.
Todos los días se genera el parte de trabajo, en el que se incluyen el número de cargas de cemento (1 carga = 1 camión lleno de cemento) que debes enviar a cada
cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay que enviar cargas a todos los clientes, y además, puedes suponer razonablemente que tu
flota de camiones es capaz de hacer el trabajo diario.
Para la resolución del problema quizá sea interesante recordar que Zuelandia es un país cuya especial orografía sólo permite que las carreteras tengan un sentido de
circulación.
Implementa una función que dado el grafo con las distancias directas entre las diferentes ciudades zuelandesas, el parte de trabajo diario, y la capital de Zuelandia, devuelva
la distancia total en kilómetros que deben recorrer tus camiones en el día, para que puedas descubrir si es cierto o no que usan tus camiones en actividades ajenas a la empresa. 
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;


struct parte
{
    vertice destino;
    int carga;
};


tCoste calcularViaje(GrafoP<int>& G, vector<parte>& P, vertice o);

int main()
{
    GrafoP<int> G ("4.txt");
    vector<parte> P(3); // Haremos 3 partes 
    P[0].carga = 10;    P[1].carga = 4;     P[2].carga = 2;
    P[0].destino = 2;   P[1].destino = 1;   P[2].destino = 3;
    //La capital de zuelandia estará en el vertice 0
    tCoste totalKm = calcularViaje(G,P,0);

    cout << "El total de km que han de recorrer los camiones es de: " << totalKm << endl;

    return 0;
}

tCoste calcularViaje(GrafoP<int>& G, vector<parte>& P, vertice o)
{
    vector<vertice> PD (G.numVert());
    vector<tCoste> VD = Dijkstra(G,o,PD);
    vector<vertice> PI (G.numVert());
    vector<tCoste> VI = DijkstraInv(G,o,PI);
    tCoste distMinima = 0;
    for(size_t i = 0; i < P.size(); i++)
    {
        distMinima += VD[P[i].destino] * P[i].carga + VI[P[i].destino] * P[i].carga;
    }
    return distMinima;
}