/*
Implementa un subprograma que dado un árbol general nos calcule su grado. 
*/

#include <iostream>
#include "agen.hpp"

typedef char T;

int grado(Agen<T>);
int gradoRec(Agen<T>, Agen<T>::nodo);
int numhijos(Agen<T>, Agen<T>::nodo);

int main()
{
    Agen<T> A;
    int g = grado(A);
    std::cout << "El grado del arbol es: " << g << std::endl;
    return 0;
}

int grado(Agen<T> A)
{
    if (!(A.raiz() == Agen<T>::NODO_NULO))
    {
        return gradoRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int gradoRec(Agen<T> A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 1;
    }
    else
    {
        int maximo = numhijos(A, n);
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            maximo = std::max(maximo, gradoRec(A, n));
            n = A.hermDrcho(n);
        }
        return maximo;
    }
}

int numhijos(Agen<T> A, Agen<T>::nodo n)
{
    if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int hijos = 1;
        n = A.hijoIzqdo(n);
        while(A.hermDrcho(n) != Agen<T>::NODO_NULO)
        {
            hijos ++;
            n = A.hermDrcho(n);
        }
        return hijos;
    }
}