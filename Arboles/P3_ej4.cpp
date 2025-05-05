/*
Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice la poda de A a partir de x.
Se asume que no hay elementos repetidos en A. 
*/

#include "agen.h"
#include <iostream>
#include "agen_E-S.h"

typedef char tElto;

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

void poda(Agen<int>& A, int x)
{
    if(!A.vacio())
    {
        podaRec(A, A.raiz(), x);
    }
}

int main()
{
    Agen<int> A;
    A.insertarRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 4);
    A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 5);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 6);
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())), 7);
    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 8);
    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 9);
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())))), 10);
    A.insertarHermDrcho(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))))), 11);
    std::cout << "Árbol antes de la poda:" << std::endl;
    imprimirAgen(A);
    poda(A, 3);
    std::cout << "\nÁrbol después de la poda:" << std::endl;
    imprimirAgen(A);
    return 0;
}