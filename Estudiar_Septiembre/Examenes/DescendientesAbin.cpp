/*
    Contar descendientes: 'Dado un árbol binario, contar el número de nodos de dicho árbol que tienen 4 descendientes.'
*/

#include "../Abin/abin.hpp"
#include <iostream>

typedef char T;

int descendientes(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return descendientesRec(A, A.raiz());
    }else{
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
        if(Contar(A, n) == 4)
        {
            return 1 + descendientesRec(A, A.hijoIzqdo(n)) + descendientesRec(A, A.hijoDrcho(n));
        }
        else
        
        {
            return descendientesRec(A, A.hijoIzqdo(n)) + descendientesRec(A, A.hijoDrcho(n));
        }
    }
}

int Contar(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + Contar(A, A.hijoIzqdo(n)) + Contar(A, A.hijoDrcho(n));
    }
}