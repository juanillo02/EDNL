/*
Para un árbol binario B, podemos construir el árbol binario reflejado B^R cambiando los subárboles izquierdo y derecho en cada nodo. Implementa un subprograma que devuelva
el árbol binario reflejado de uno dado.
*/

#include "abin.hpp"
#include <iostream>

typedef char T;

Abin<T> AReflejado(Abin<T>);
void AReflejadoRec(Abin<T>, Abin<T>::nodo, Abin<T>::nodo, Abin<T>, Abin<T>::nodo);

int main()
{
    Abin<T> A, Reflejado;
    Reflejado = AReflejado(A);
    return 0;
}

Abin<T> AReflejado(Abin<T> A)
{
    if(!A.arbolVacio())
    {
        Abin<T> Ref;
        Ref.insertarRaiz(A.elemento(A.raiz()));
        AReflejadoRec(A, A.hijoIzqdo(A.raiz()), A.hijoDrcho(A.raiz()), Ref, Ref.raiz());
        return Ref;
    }
    else
    {
        std::cout << "El arbol esta vacio, por lo que no se puede reflejar nada.";
        return A;
    }
}

void AReflejadoRec(Abin<T> A, Abin<T>::nodo ni, Abin<T>::nodo nd, Abin<T> R, Abin<T>::nodo nR)
{
    if(ni != Abin<T>::NODO_NULO && nd != Abin<T>::NODO_NULO)
    {
        R.insertarHijoDrcho(nR, A.elemento(ni));
        R.insertarHijoIzqdo(nR, A.elemento(nd));
        AReflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(nd), R, R.hijoIzqdo(nR));
        AReflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(nd), R, R.hijoDrcho(nR));
    }
    if(ni == Abin<T>::NODO_NULO && nd != Abin<T>::NODO_NULO)
    {
        R.insertarHijoIzqdo(nR, A.elemento(nd));
        AReflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(nd), R, R.hijoIzqdo(nR));
    }
    if(ni != Abin<T>::NODO_NULO && nd == Abin<T>::NODO_NULO)
    {
        R.insertarHijoDrcho(nR, A.elemento(ni));
        AReflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(nd), R, R.hijoDrcho(nR));
    }
}