/*
Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando los subárboles izquierdo y derecho en cada nodo. 
Implementa un subprograma que devuelva el árbol binario reflejado de uno dado.
Operaciones:
- A.elemento(nodo n) -> (Pre) n es un nodo del árbol y (Post) devuelve el elemento del nodo.
- A.insertarRaiz(const T& e) -> (Pre) el árbol está vacío y (Post) se inserta el elemento e en el nodo raiz.
- A.insertarHijoIzqdo(nodo n, const T& e) -> (Pre) n es un nodo del árbol que no tiene hijo izquierdo y (Post) inserta el elemento e como hijo
izquierdo del nodo.
- A.insertarHijoDcho(nodo n, const T& e) -> (Pre) n es un nodo del árbol que no tiene hijo derecho y (Post) inserta el elemento e como hijo
derecho del nodo.
*/
#include "abin.hpp"

typedef char T;

Abin<T> reflejado(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        Abin<T> RB;
        RB.insertarRaiz(A.elemento(A.raiz()));
        reflejadoRec(A, A.hijoIzqdo(A.raiz()), A.hijoDrcho(A.raiz()), RB, RB.raiz());
        return RB;
    }
    else
    {
        return A;
    }
}

void reflejadoRec(Abin<T> A, Abin<T>::nodo ni, Abin<T>::nodo nd, Abin<T> &RB, Abin<T>::nodo nr)
{
    if(ni != Abin<T>::NODO_NULO && nd != Abin<T>::NODO_NULO)
    {
        RB.insertarHijoIzqdo(nr, A.elemento(nd));
        RB.insertarHijoDrcho(nr, A.elemento(ni));
        reflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni), RB, nr);
        reflejadoRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd), RB, nr);
    }
    if(ni != Abin<T>::NODO_NULO && nd == Abin<T>::NODO_NULO)
    {
        RB.insertarHijoDrcho(nr, A.elemento(ni));
        reflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni), RB, nr);
    }
    if(ni == Abin<T>::NODO_NULO && nd != Abin<T>::NODO_NULO)
    {
        RB.insertarHijoIzqdo(nr, A.elemento(nd));
        reflejadoRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd), RB, nr);
    }
}