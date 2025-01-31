/*
Implementa un subprograma que dado un árbol general nos calcule su grado.
*/

#include "Agen.hpp"
#include <iostream>

typedef char T;

int grado(Agen<T>& A)
{
    if(A.raiz() != Agen<T>::NODO_NULO)
    {
        return gradoRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int gradoRec(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int suma = numHijo(A, n);
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            suma = std::max(suma, gradoRec(A, n));
            n = A.hermDrcho(n);
        }
        return suma;
    }
}

int numHijo(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int suma = 1;
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            suma++;
            n = A.hermDrcho(n);
        }
        return suma;
    }
}