/*
La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la ciudad como paso de tránsito
hacia otras ciudades. (Para ir de una ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma empleándola
como ciudad destino u origen). Sin embargo esto podria ocasionar traslados mas largos y el consecuente descontento del viajero zuelandes, asi como
un incremento de la contaminacion eb todo el pais. Por esa razon, el gobierno solo tomara esta medida si el coste total adicional en km recorridos
por los conductores zueladeces con motivo de la medida anticontaminacion no exceden a una cantidad de km determinada. Para poder estimar/calcular
el numero total de km adicionales se dispone del numero de viajes diarios que se realizan entre cualquieras dos ciudades de Zuelandia (obviamente,
el numero de viajes diarios podrá ser distintos para dos pares diferentes de ciudades de Zuelandia). Asi pues, dados los siguientes datos: la
capital de Zuelandia, el Grafo con los km de cada carretera del est, los viajes diarios que se estima que se realizan entre todos los pares de
ciudades del pais y el numero maximo del total de km adicionales que se acepta realizar para implementar la medida.
Implementa un subprograma que calcule y devuelva el numero de km adicionales que provocara la implantacion de la medida anticontaminacion
y si debe implementarse dicha medida o no, de acuerdo al criterio anteriormente descrito.
*/
#include <iostream>
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct decision
{
    tCoste numKm;
    bool aceptar;
};

tCoste kmtotales(const matriz<int>& M, const matriz<int>& viajes, size_t n)
{
    tCoste total = 0;
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(M[i][j] != GrafoP<int>::INFINITO && viajes[i][j] > 0)
            {
                total += M[i][j] * viajes[i][j];
            }
        }
    }
    return total;
}

decision Zuelandia(const GrafoP<int>& G, vertice capital, const matriz<int>& viaje, int kmAdicionales)
{
    size_t n = G.numVert();
    GrafoP<int> GSC = G;
    matriz<vertice> MV(n);
    matriz<tCoste> MC = Floyd(G, MV);
    tCoste kmAntes = kmtotales(MC, viaje, n);
    for(vertice i = 0; i < n; i++)
    {
        if(i != capital)
        {
            GSC[i][capital] = GrafoP<int>::INFINITO;
            GSC[capital][i] = GrafoP<int>::INFINITO;
        }
    }
    matriz<vertice> MVA(n);
    matriz<tCoste> MCA = Floyd(GSC, MVA);
    vector<vertice> VV(n), VVI(n);
    vector<tCoste> VD = Dijkstra(G, capital, VV), VDI = DijkstraInv(G, capital, VVI);
    for(vertice i = 0; i < n; i++)
    {
        MCA[i][capital] = VDI[i];
    }
    MCA[capital] = VD;
    decision res;
    res.numKm = kmtotales(MCA, viaje, n);
    res.aceptar = (res.numKm < kmAdicionales + kmAntes);
    return res;
}

int main() {
    const int N = 5;
    GrafoP<int> G(N);

    // Inicializar todas las distancias a INFINITO excepto la diagonal
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            G[i][j] = (i == j) ? 0 : GrafoP<int>::INFINITO;

    // Conectamos las ciudades (simétrico)
    G[0][1] = G[1][0] = 5;
    G[0][2] = G[2][0] = 10;
    G[1][2] = G[2][1] = 3;
    G[1][3] = G[3][1] = 7;
    G[2][3] = G[3][2] = 2;
    G[3][4] = G[4][3] = 4;
    G[2][4] = G[4][2] = 9;

    // Definimos la capital (ej: nodo 2)
    vertice capital = 2;

    // Matriz de viajes diarios entre ciudades
    matriz<int> viajes(N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            viajes[i][j] = (i == j) ? 0 : 1; // Ejemplo: 1 viaje entre cada par de ciudades

    int maxKmAdicionales = 10; // límite permitido

    decision resultado = Zuelandia(G, capital, viajes, maxKmAdicionales);

    std::cout << "Kilómetros adicionales: " << resultado.numKm << std::endl;
    if (resultado.aceptar)
        std::cout << "✅ Se puede implementar la medida anticontaminación.\n";
    else
        std::cout << "❌ No se puede implementar la medida anticontaminación.\n";

    return 0;
}