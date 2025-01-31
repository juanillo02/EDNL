/*
Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol determine la profundidad de éste nodo en el árbol.
*/

#include "Agen.hpp"

typedef char T;

int profundidad(Agen<T>& A)
{
    if(A.raiz() == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return profundidadReC(A, A.raiz());
    }
}

int profundidadReC(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + profundidadReC(A, A.padre(n));
    }
}