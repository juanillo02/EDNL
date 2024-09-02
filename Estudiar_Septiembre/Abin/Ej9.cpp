/*
Dado un árbol binario de enteros donde el valor de cada nodo es menor que el de sus hijos, implementa un subprograma para eliminar un valor del mismo preservando la
propiedad de orden establecida. Explica razonadamente la elección de la estructura de datos.
Nota: Se supone que en el árbol no hay elementos repetidos, y que el número de nodos del mismo no está acotado 
*/

#include <iostream>
#include "abin.hpp"


void Eliminar(Abin<int>&, int);
void EliminarRec(Abin<int>&, Abin<int>::nodo, int);
void Quitar(Abin<int>&, Abin<int>::nodo);
void quitarNodo(Abin<int>&, Abin<int>::nodo);

int main()
{
    Abin<int> A;
    Eliminar(A, 7);
    return 0;
}

void Eliminar(Abin<int>& A, int x)
{
    if(!A.arbolVacio())
    {
        EliminarRec(A, A.raiz(), x);
    }
}

void EliminarRec(Abin<int>& A, Abin<int>::nodo n, int x)
{
    if(n != Abin<int>::NODO_NULO)
    {
        if(x != A.elemento(n))
        {
            EliminarRec(A, A.hijoIzqdo(n), x);
            EliminarRec(A, A.hijoDrcho(n), x);
        }
        else
        {
            Quitar(A, n);
        }
    }
    
}

void Quitar(Abin<int>& A, Abin<int>::nodo n)
{
    int aux;
    if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
    {
        if(A.elemento(A.hijoIzqdo(n)) < A.elemento(A.hijoDrcho(n)))
        {
            aux = A.elemento(n);
            A.elemento(n) = A.elemento(A.hijoIzqdo(n));
            A.elemento(A.hijoIzqdo(n)) = aux;
            Quitar(A,A.hijoIzqdo(n));
        }
        else
        {
            aux = A.elemento(n);
            A.elemento(n) = A.elemento(A.hijoDrcho(n));
            A.elemento(A.hijoDrcho(n)) = aux;
            Quitar(A,A.hijoDrcho(n));      
        }
    }
    if(A.hijoIzqdo(n) == Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
    {
        quitarNodo(A,n);
    }
    if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
    {
        aux = A.elemento(n);
        A.elemento(n) = A.elemento(A.hijoIzqdo(n));
        A.elemento(A.hijoIzqdo(n)) = aux;
        Quitar(A,A.hijoIzqdo(n));
    }
    if(A.hijoIzqdo(n) == Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
    {
        aux = A.elemento(n);
        A.elemento(n) = A.elemento(A.hijoDrcho(n));
        A.elemento(A.hijoDrcho(n)) = aux;
        Quitar(A,A.hijoDrcho(n));        
    }
}

void quitarNodo(Abin<int>& A,Abin<int>::nodo n)
{
    if(A.hijoIzqdo(A.padre(n)) == n)
    {
        A.eliminarHijoIzqdo(A.padre(n));
    }
    else
    {
        A.eliminarHijoDrcho(A.padre(n));
    }
}