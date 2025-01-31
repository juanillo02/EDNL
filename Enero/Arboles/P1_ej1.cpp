/*
Implementa un subprograma que calcule el número de nodos de un árbol binario.
Operaciones:
- A.arbolVacio() -> devuelve un booleano (true si está vacio y false si no).
- A.raiz() -> devuelve el nodo raiz del arbol. Si el arbol está vacio devuelve nodo nulo.
- A.hijoIzqdo(nodo n) -> n es un nodo del árbol (Pre) y devuelve el nodo hijo izquierdo del nodo n, si no existe devuelve nodo nulo (Post).
- A.hijoDcho(nodo n) -> n es un nodo del árbol (Pre) y devuelve el nodo hijo derecho del nodo n, si no existe devuelve nodo nulo (Post).
*/
#include "abin.hpp"

typedef char T;

int numNoodos(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return numNodosRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int numNodosRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + numNodosRec(A, A.hijoIzqdo(n)) + numNodosRec(A, A.hijoDrcho(n));
    }
}