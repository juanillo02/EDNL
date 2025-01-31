/*
Implementa un subprograma que calcule la altura de un árbol binario.
Operaciones:
- A.arbolVacio() -> es un booleano que devuelve true si el árbol está vacio y false si no.
- A.raiz() -> devuelve el nodo raiz si el árbol no está vacío, sino devuelve nodo nulo.
- A.hijoIzqdo(nodo n) -> (Pre) n es un nodo del árbol y (Post) devuelve el nodo hijo izquierdo del nodo n, si no existe devuelve nodo nulo.
- A.hijoDcho(nodo n) -> (Pre) n es un nodo deñ árbol y (Post) devuelve el nodo hijo derecho del nodo n, si no existe devuelve nodo nulo.
*/
#include "abin.hpp"
#include <iostream>

typedef char T;

int altura(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return alturaRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int alturaRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(alturaRec(A, A.hijoIzqdo(n)), alturaRec(A, A.hijoDrcho(n)));
    }
}