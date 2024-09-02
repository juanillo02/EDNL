/*
Dado un arbol binario de un tipo generico T, determinar si es un Arbol Binario de Busqueda Equilibrado (AVL) o no.
*/

#include "../Abin/abin.hpp"
#include<iostream>

typedef char T;

bool AVL(Abin<T>& A)
{
    return AVLRec(A, A.raiz()) && EsABB(A, A.raiz());
}

bool AVLRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
    {
        return true;
    }
    if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    {
        return std::abs(altura(A, A.hijoIzqdo(n)) - altura(A, A.hijoDrcho(n))) <= 1 && AVLRec(A, A.hijoIzqdo(n)) && AVLRec(A, A.hijoDrcho(n));
    }
    if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
    {
        return std::abs(altura(A, A.hijoIzqdo(n)) - altura(A, A.hijoDrcho(n))) <= 1 && AVLRec(A, A.hijoIzqdo(n));
    }
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    {
        return std::abs(altura(A, A.hijoIzqdo(n)) - altura(A, A.hijoDrcho(n))) <= 1 && AVLRec(A, A.hijoDrcho(n));
    }
}

bool EsABB(Abin<T>& A, Abin<T>::nodo n)
{
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
    {
        return true;
    }
    if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    {
        return A.elemento(n) > A.elemento(A.hijoIzqdo(n)) && A.elemento(n) < A.elemento(A.hijoDrcho(n)) && EsABB(A, A.hijoIzqdo(n)) && EsABB(A, A.hijoDrcho(n));
    }
    if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
    {
        return A.elemento(n) > A.elemento(A.hijoIzqdo(n)) && EsABB(A, A.hijoIzqdo(n));
    }
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    {
        return A.elemento(n) < A.elemento(A.hijoDrcho(n)) && EsABB(A, A.hijoDrcho(n));
    }
}

int altura(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(altura(A, A.hijoIzqdo(n)), altura(A, A.hijoDrcho(n)));
    }
}