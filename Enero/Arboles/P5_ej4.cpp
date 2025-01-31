/*
Un árbol es estrictamente ternario si todos sus nodos son hojas o tienen tres hijos. Escribe una función que, dado un árbol de grado arbitrario,
nos indique si es o no estrictamente ternario.
*/

#include "agen.hpp"

typedef char T;

bool ternario(Agen<T>& A)
{
    if(A.raiz() == Agen<T>::NODO_NULO)
    {
        return false;
    }
    else
    {
        return ternarioRec(A, A.raiz());
    }
}

bool ternarioRec(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        {
            return true;
        }
        else
        {
            if(contar(A, n) == 3)
            {
                Agen<T>::nodo aux = A.hijoIzqdo(n);
                while(aux != Agen<T>::NODO_NULO)
                {
                    return ternarioRec(A, aux);
                    aux = A.hermDrcho(n);
                }
            }
            else
            {
                return false;
            }
        }
    }
}

int contar(Agen<T>& A, Agen<T>::nodo n)
{
    int suma = 0;
    Agen<T>::nodo aux = A.hijoIzqdo(n);
    while(aux != Agen<T>::NODO_NULO)
    {
        suma++;
        aux = A.hermDrcho(n);
    }
    return suma;
}