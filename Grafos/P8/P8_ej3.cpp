/*
Implementa un subprograma para encontrar un árbol de extensión máximo. ¿Es más difícil que encontrar un árbol de extensión mínimo?
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "particion.h"
#include "alg_grafoPMC.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<tCoste>::arista arista;
typedef typename GrafoP<tCoste>::vertice vertice;

GrafoP<tCoste> KruskallMax(const GrafoP<tCoste> &G)
{
	assert(!G.esDirigido());
	const size_t n = G.numVert();
	GrafoP<tCoste> g(n);  // Árbol generador de coste mínimo.
	Particion P(n);       // Partición inicial del conjunto de vértices de G.
	Apo<arista> A(n * n); // Aristas de G ordenadas por costes.
	// Copiar aristas del grafo G en el APO A.
	for (vertice u = 0; u < n; u++)
		for (vertice v = u + 1; v < n; v++)
			if (G[u][v] != GrafoP<tCoste>::INFINITO)
				//Guardarlo como negativo
				A.insertar(arista(u, v, (G[u][v]) *(-1)));
	size_t i = 1;
	while (i <= n - 1)
	{
		arista a = A.cima();
		A.suprimir();
		vertice u = P.encontrar(a.orig);
		vertice v = P.encontrar(a.dest);
		if (u != v)	//Si no es el mismo vertice
		{ // Los extremos de a pertenecen a componentes distintas
			P.unir(u, v);
			// Incluir la arista a en el árbol g
			g[a.orig][a.dest] = g[a.dest][a.orig] = (a.coste) * (-1);	//Volverlo el mayor de nuevo
			i++;
		}
	}
	return g;
}

template <typename tCoste>
GrafoP<tCoste> PrimMax(const GrafoP<tCoste>& G)
// Devuelve un árbol generador de coste mínimo
// de un grafo no dirigido ponderado y conexo G.
{
	assert(!G.esDirigido());

	typedef typename GrafoP<tCoste>::vertice vertice;
	typedef typename GrafoP<tCoste>::arista arista;
	const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
	arista a;
	const size_t n = G.numVert();
	GrafoP<tCoste> g(n);			// Árbol generador de coste mínimo.
	vector<bool> U(n, false);		// Conjunto de vértices incluidos en g.
	Apo<arista> A(n*(n-1)/2-n+2);	// Aristas adyacentes al árbol g
									// ordenadas por costes.
	U[0] = true;					// Incluir el primer vértice en U.

	// Introducir en el APO las aristas adyacentes al primer vértice
	for (vertice v = 1; v < n; v++)
		if (G[0][v] != INFINITO)
			A.insertar(arista(0, v, G[0][v] * -1));
	for (size_t i = 1; i <= n-1; i++) {     // Seleccionar n-1 aristas.
		// Buscar una arista a de coste maximo que no forme un ciclo.
		// Nota: Las aristas en A tienen sus orígenes en el árbol g.
		do {
			a = A.cima();
			A.suprimir();
		} while (U[a.dest]); // a forma un ciclo (a.orig y a.dest están en U y en g).
		// Incluir la arista a en el árbol g y el nuevo vértice u en U.
		g[a.orig][a.dest] = g[a.dest][a.orig] = -1 * a.coste;
		vertice u = a.dest;
		U[u] = true;
		// Introducir en el APO las aristas adyacentes al vértice u
		// que no formen ciclos.
		for (vertice v = 0; v < n; v++)
			if (!U[v] && G[u][v] != INFINITO)
				A.insertar(arista(u, v, -1 * G[u][v]));
	}
	return g;
}