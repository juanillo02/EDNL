/*
    Implementa un subprograma que devuelva el porcentaje de descendientes propios de un arbol general que sean multiplo de 3
*/
#include "agen.hpp"
#include <iostream>

typedef char T;

float Porcentaje(Agen<T>& A)
{
    if(A.raiz() != Agen<T>::NODO_NULO)
    {
        return (PorcentajeRec(A, A.raiz())/ NumNodos(A)) * 100;
    }
    else
    {
        return 0;
    }
}

float PorcentajeRec(Agen<T> A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 1;
        Agen<T>::nodo nodo = A.hijoIzqdo(n);
        if(DesPropios(A, n) % 3 == 0 && DesPropios != 0)
        {
            suma ++;
        }
        while(nodo != Agen<T>::NODO_NULO)
        {
            suma += PorcentajeRec(A, nodo);
            nodo = A.hermDrcho(nodo);
        }
        return suma;
    }
}

size_t NumNodos(Agen<T>& A)
{
    if(A.raiz() == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 1;
        Agen<T>::nodo nodo = A.hijoIzqdo(A.raiz());
        while(nodo != Agen<T>::NODO_NULO)
        {
            suma += NumNodos(A);
            nodo = A.hermDrcho(nodo);
        }
        return suma;
    }
}

size_t DesPropios(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 0;
        Agen<T>::nodo nodo = A.hijoIzqdo(n);
        while(nodo != Agen<T>::NODO_NULO)
        {
            suma++;
            nodo = A.hermDrcho(nodo);
        }
        nodo = A.hijoIzqdo(n);
        while(nodo != Agen<T>::NODO_NULO)
        {
            suma += DesPropios(A, nodo);
            nodo = A.hermDrcho(nodo);
        }
        return suma;
    }
}