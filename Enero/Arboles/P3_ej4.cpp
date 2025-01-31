/*
Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice la poda de A a partir de x. Se asume que no hay elementos
repetidos en A.
*/
#include "Agen.hpp"

void poda(Agen<int>& A, int x)
{
    if(!(A.raiz() == Agen<int>::NODO_NULO))
    {
        podaRec(A, A.raiz(), x);
    }
}

void podaRec(Agen<int>& A, Agen<int>::nodo n, int x)
{
    if(n != Agen<int>::NODO_NULO)
    {
        if(A.elemento(n) == x)
        {
            podar(A, n);
        }
        else
        {
            Agen<int>::nodo aux = A.hijoIzqdo(n);
            while(aux != Agen<int>::NODO_NULO)
            {
                podaRec(A, aux, x);
                aux = A.hermDrcho(aux);
            }
        }
    }
}

void podar(Agen<int>& A, Agen<int>::nodo n)
{
    Agen<int>::nodo ni = A.hijoIzqdo(n), nd = A.hermDrcho(ni);
    if(ni != Agen<int>::NODO_NULO && nd != Agen<int>::NODO_NULO)
    {
        if(A.hijoIzqdo(ni) != Agen<int>::NODO_NULO)
        {
            podar(A, ni);
            podar(A, n);
        }
        else
        {
            A.eliminarHijoIzqdo(n);
            podar(A, n);
        }
    }
    if(ni != Agen<int>::NODO_NULO && nd == Agen<int>::NODO_NULO)
    {
        if(A.hijoIzqdo(ni) == Agen<int>::NODO_NULO)
        {
            A.eliminarHijoIzqdo(n);
        }
    }
}