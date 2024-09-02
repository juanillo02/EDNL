#include <iostream>
#include "../Agen/agen.hpp"

typedef char T;

void Poda(Agen<T>& A, char c)
{
    PodaRec(A, A.raiz(), c);
}

void PodaRec(Agen<T>& A, Agen<T>::nodo n, char c)
{
    if(n != Agen<T>::NODO_NULO)
    {
        if(A.elemento(n) == c)
        {
            PodarArbol(A, n, c);
        }
        else
        {
            Agen<T>::nodo aux = A.hijoIzqdo(n);
            while(aux != Agen<T>::NODO_NULO)
            {
                PodaRec(A, aux, c);
                aux = A.hermDrcho(aux);
            }
        }
    }
}

void PodarArbol(Agen<T>& A, Agen<T>::nodo n, char c)
{
    Agen<T>:: nodo ni = A.hijoIzqdo(n), nd = A.hermDrcho(n);
    if(ni != Agen<T>::NODO_NULO && nd != Agen<T>::NODO_NULO)
    {
        if(A.hijoIzqdo(ni) == Agen<T>::NODO_NULO)
        {
            A.eliminarHijoIzqdo(n);
            PodarArbol(A, n, c);
        }
        else
        {
            PodarArbol(A, ni, c);
            PodarArbol(A, nd, c);
        }
    }
    if(A.hijoIzqdo(nd) == Agen<T>::NODO_NULO && A.hermDrcho(nd) == Agen<T>::NODO_NULO)
    {
        A.eliminarHermDrcho(nd);
    }
}