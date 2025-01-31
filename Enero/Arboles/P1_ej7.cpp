/*
Implementa un subprograma que determine si un árbol binario es o no pseudocompleto. En este problema entenderemos que un árbol es pseudocompleto,
si en el penúltimo nivel del mismo cada uno de los nodos tiene dos hijos o ninguno.
Operaciones:
- A.arbolVacio() -> es un booleano que devuelve true si el arbol está vacío y false si no.
- A.raiz() -> devuelve el nodo raiz, si el arbol está vacío devuelve nodo nulo.
- A.hijoIzqdo(nodo n) -> (Pre) n es un nodo del árbol y (Post) devuelve el nodo hijo izquierdo, si no existe devuelve nodo nulo.
- A.hijoDcho(nodo n) -> (Pre) n es un nodo del árbol y (Post) devuelve el nodo hijo derecho, si no existe devuelve nodo nulo.
- A.padre(nodo n) -> (Pre) n es un nodo del árbol y (Post) devuelve el nodo padre del nodo n, si es la raiz, devuelve nodo nulo.
*/
#include "abin.hpp"

typedef char T;

bool pseudocompleto(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        int alt = altura(A, A.raiz());
        return pseudocompletoRec(A, A.raiz(), alt);
    }
    else
    {
        return false;
    }
}

bool pseudocompletoRec(Abin<T>& A, Abin<T>::nodo n, int altura)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(profundidad(A, n) == altura - 1)
        {
            return (A.hijoDrcho(n) != Abin<T>::NODO_NULO && A.hijoIzqdo(n) != Abin<T>::NODO_NULO) || (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
        }
    }
}

int altura(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(altura(A, A.hijoIzqdo(n)), altura(A, A.hijoDrcho(n)));
    }
}

int profundidad(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + profundidad(A, A.padre(n));
    }
}