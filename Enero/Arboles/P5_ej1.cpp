/*
Dado un árbol binario de enteros donde el valor de cada nodo es menor que el de sus hijos, implementa un subprograma para eliminar un valor del
mismo preservando la propiedad de orden establecida. Explica razonadamente la elección de la estructura de datos. 
Nota: Se supone que en el árbol no hay elementos repetidos, y que el número de nodos del mismo no está acotado 
*/
#include "abin.hpp"

void eliminar(Abin<int>& A, int x)
{
    if(!A.arbolVacio())
    {
        eliminarRec(A, A.raiz(), x);
    }
}

void eliminarRec(Abin<int>& A, Abin<int>::nodo n, int x)
{
    if(n != Abin<int>::NODO_NULO)
    {
        if(A.elemento(n) != x)
        {
            eliminarRec(A, A.hijoDrcho(n), x);
            eliminarRec(A, A.hijoIzqdo(n), x);
        }
        else
        {
            quitar(A, n, x);
        }
    }
}

void quitar(Abin<int>& A, Abin<int>::nodo n, int x)
{
    int aux;
    if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
    {
        if(A.elemento(A.hijoIzqdo(n)) < A.elemento(A.hijoDrcho(n)))
        {
            aux = A.elemento(n);
            A.elemento(n) = A.elemento(A.hijoIzqdo(n));
            A.elemento(A.hijoIzqdo(n)) = aux;
            quitar(A, A.hijoIzqdo(n), x);
        }
        else
        {
            aux = A.elemento(n);
            A.elemento(n) = A.elemento(A.hijoDrcho(n));
            A.elemento(A.hijoDrcho(n)) = aux;
            quitar(A, A.hijoDrcho(n), x);
        }
    }
    if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
    {
        aux = A.elemento(n);
        A.elemento(n) = A.elemento(A.hijoIzqdo(n));
        A.elemento(A.hijoIzqdo(n)) = aux;
        quitar(A, A.hijoIzqdo(n), x);
    }
    if(A.hijoIzqdo(n) == Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
    {
        aux = A.elemento(n);
        A.elemento(n) = A.elemento(A.hijoDrcho(n));
        A.elemento(A.hijoDrcho(n)) = aux;
        quitar(A, A.hijoDrcho(n), x);
    }
    if(A.hijoIzqdo(n) == Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
    {
        quitarNodo(A, A.padre(n), x);
    }
}

void quitarNodo(Abin<int>& A, Abin<int>::nodo n, int x)
{
    if(A.elemento(A.hijoIzqdo(n)) == x)
    {
        A.eliminarHijoIzqdo(n);
    }
    else
    {
        A.eliminarHijoDrcho(n);
    }
}