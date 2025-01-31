/*
Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario, definido como el máximo desequilibrio de todos sus nodos.
El desequilibrio de un nodo se define como la diferencia entre las alturas de los subárboles del mismo.
Operciones:
- A.raiz() -> booleano que devuelve true si el árbol está vacío o false si no.
- A.raiz() -> devuelve el nodo raíz del árbol, si está vacío devuelve nodo nulo.
- A.hijoIzqdo(nodo n) -> (Pre) n es un nodo del árbol y (Post) devuelve el nodo hijo izquierdo del árbol, si no existe devuelve nodo nulo.
- A.hijoDcho(nodo n) -> (Pre) n es un nodo del árbol y (Post) devuelve el nodo hijo derecho del árbol, si no existe devuelve nodo nulo.
*/
#include "abin.hpp"
#include <iostream>

typedef char T;

int desequilibrio(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return desequilibrioRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int desequilibrioRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(abs(altura(A, A.hijoIzqdo(n)) - altura(A, A.hijoDrcho(n))), std::max(desequilibrioRec(A, A.hijoIzqdo(n)), desequilibrioRec(A, A.hijoDrcho(n))));
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