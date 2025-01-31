/*
Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas de los subárboles más bajo y más alto de cada nivel.
Implementa un subprograma que calcule el grado de desequilibrio de un árbol general.
*/
#include "Agen.hpp"
#include <iostream>

typedef char T;

int desequilibrio(Agen<T>& A)
{
    if(A.raiz() == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return desequilibrioRec(A, A.raiz());
    }
}

int desequilibrioRec(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return std::max(abs(alturaRec(A, A.hijoIzqdo(n)) - alturaRec(A, A.hermDrcho(n))), std::max(desequilibrioRec(A, A.hijoIzqdo(n)), desequilibrioRec(A, A.hermDrcho(n))));
    }
}

int alturaRec(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(alturaRec(A, A.hijoIzqdo(n)), alturaRec(A, A.hermDrcho(n)));
    }
}