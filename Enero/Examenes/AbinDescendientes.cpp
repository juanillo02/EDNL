/*
    Contar descendientes: 'Dado un árbol binario, contar el número de nodos de dicho árbol que tienen 4 descendientes.'
*/
#include "../Arboles/abin.hpp"

typedef char T;

int descendientes(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return descendientesRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int descendientesRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(contarDescendientes(A, n) == 4)
        {
            return 1 + descendientesRec(A, A.hijoIzqdo(n)) + descendientesRec(A, A.hijoDrcho(n));
        }
        else
        {
            return descendientesRec(A, A.hijoIzqdo(n)) + descendientesRec(A, A.hijoDrcho(n));
        }
    }
}

int contarDescendientes(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + contarDescendientes(A, A.hijoIzqdo(n)) + contarDescendientes(A, A.hijoDrcho(n));
    }
}