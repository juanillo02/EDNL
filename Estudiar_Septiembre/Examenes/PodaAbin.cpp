#include <iostream>
#include "../Abin/abin.hpp"

typedef char T;

void Poda(Abin<T>& A, char c)
{
    if(!A.arbolVacio())
    {
        PodaRec(A, A.raiz(), c);
    }
}

void PodaRec(Abin<T>& A, Abin<T>::nodo n, char c)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(A.elemento(n) == c)
        {
            PodarArbol(A, n);
        }
        else
        {
            PodaRec(A, A.hijoIzqdo(n), c);
            PodaRec(A, A.hijoDrcho(n), c);
        }
    }
}

void PodarArbol(Abin<T>& A, Abin<T>::nodo n)
{
    Abin<T>::nodo ni = A.hijoIzqdo(n), nd = A.hijoDrcho(n);
    if(A.hijoIzqdo(ni) == Abin<T>::NODO_NULO && A.hijoDrcho(ni) == Abin<T>::NODO_NULO)
    {
        A.eliminarHijoIzqdo(n);
        A.eliminarHijoDrcho(n);
    }
    else
    {
        PodarArbol(A, ni);
    }
    if(A.hijoIzqdo(nd) == Abin<T>::NODO_NULO && A.hijoDrcho(nd) == Abin<T>::NODO_NULO)
    {
        A.eliminarHijoIzqdo(n);
        A.eliminarHijoDrcho(n);
    }
    else
    {
        PodarArbol(A, nd);
    }
}