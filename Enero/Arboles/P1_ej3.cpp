/*
Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine la profundidad de este nodo en dicho árbol.
Operaciones:
- A.arbolVacio() -> booleano que devuelve true si está vacío y false si no.
- A.padre(nodo n) -> n es un nodo del árbol y devuelve el nodo padre de n, si es el nodo raiz devuelve nodo nulo.
*/
#include "abin.hpp"

typedef char T;

int profundidad(Abin<T>& A, Abin<T>::nodo n)
{
    if(!A.arbolVacio())
    {
        return profundidadRec(A, n);
    }
    else
    {
        return 0;
    }
}

int profundidadRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + profundidadRec(A, A.padre(n));
    }
}