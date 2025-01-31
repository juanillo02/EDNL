/*
Implementa un subprograma que devuelva el porcentaje de descendientes propios de un arbol general que sean multiplo de 3
*/
#include <iostream>
#include "../Arboles/agen.hpp"

typedef char T;

float descendientes(Agen<T>& A)
{
    if(A.raiz() != Agen<T>::NODO_NULO)
    {
        return (descendientesRec(A, A.raiz()) / totalNodos(A, A.raiz())) * 100;
    }
    else
    {
        return 0;
    }
}

size_t descendientesRec(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 0, propios = descendientesPropios(A, n);
        if(propios % 3 == 0 && propios != 0)
        {
            suma++;
        }
        Agen<T>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<T>::NODO_NULO)
        {
            suma += descendientesRec(A, aux);
            aux = A.hermDrcho(aux);
        }
        return suma;
    }
}

size_t totalNodos(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 1;
        Agen<T>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<T>::NODO_NULO)
        {
            suma += totalNodos(A, A.hijoIzqdo(n));
            aux = A.hermDrcho(aux);
        }
        return suma;
    }
}

size_t descendientesPropios(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 0;
        Agen<T>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<T>::NODO_NULO)
        {
            suma++;
            aux = A.hermDrcho(aux);
        }
        aux = A.hijoIzqdo(n);
        while(aux != Agen<T>::NODO_NULO)
        {
            suma += descendientesPropios(A, aux);
            aux = A.hermDrcho(aux);
        }
        return suma;
    }
}