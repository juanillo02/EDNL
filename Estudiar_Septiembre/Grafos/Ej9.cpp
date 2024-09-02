/*
Al dueño de una agencia de transportes se le plantea la siguiente situación. La agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades españolas
utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de costes) de viajar entre diferentes ciudades, por un lado en tren, y por otro en autobús
(por supuesto entre las ciudades que tengan línea directa entre ellas). Además coincide que los taxis de toda España se encuentran en estos momentos en huelga general, lo que
implica que sólo se podrá cambiar de transporte en una ciudad determinada en la que, por casualidad, las estaciones de tren y autobús están unidas.
Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús,
del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas. 
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

matriz<tCoste> viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice trasbordo);

int main ()
{
    GrafoP<int> GTren ("6tren.txt");
    GrafoP<int> GAutobus ("6autobus.txt");

    cout << "Grafo del autobus: " << endl << GAutobus << endl;
    cout << "Grafo del tren: " << endl << GTren << endl;

    //la ciudad del vertice 2 sera donde se pueda hacer transbordo entre tren y avion
    matriz<tCoste> McosteMinimo = viajar(GTren,GAutobus,2);

    cout << "coste minimo: " << endl << McosteMinimo << endl;

    return 0;
}

matriz<tCoste> viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice ciudad)
{
    bool existeTransbordoaTren = false;
    bool existeTransbordoaBus = false;

    for(size_t i = 0; i < GTren.numVert() ; i++)
    {
        if(GAutobus[ciudad][i] != GrafoP<int>::INFINITO)
        {
            existeTransbordoaBus = true;
        }
        if(GTren[ciudad][i] != GrafoP<int>::INFINITO)
        {
            existeTransbordoaTren = true;
        }
    }
    if(existeTransbordoaBus || existeTransbordoaTren)
    {
        GrafoP<int> Gresultado(GTren.numVert());
        for(size_t i = 0 ; i < Gresultado.numVert() ; i++)
        {
            for(size_t j = 0 ; j < Gresultado.numVert() ; j++)
            {
                Gresultado[i][j] = min(GTren[i][j] , GAutobus[i][j]);
            }
        }
        matriz<vertice> P (Gresultado.numVert());
        matriz<tCoste> McosteMinimo = Floyd(Gresultado,P);
        return McosteMinimo;
    }
    else
    {
        cout << "No es posible hacer un transbordo en la ciudad: " << ciudad << " tendremos que usar o el grafo del tren o el Bus" << endl;
        matriz<vertice> P (GTren.numVert());
        return Floyd(GTren,P);
    }

}