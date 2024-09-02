/*
Un árbol es estrictamente ternario si todos sus nodos son hojas o tienen tres hijos.
Escribe una función que, dado un árbol de grado arbitrario, nos indique si es o no estrictamente ternario. 
*/

#include <iostream>
#include "agen.hpp"

typedef char T;

bool ternario(Agen<T>);
bool ternarioRec(Agen<T>, Agen<T>::nodo);
bool contar(Agen<T>, Agen<T>::nodo);

int main()
{
    Agen<T> A;
    if(ternario(A))
    {
        std::cout << "El arbol es ternario" << std::endl;
    }
    else
    {
        std::cout << "El arbol no es ternario" << std::endl;
    }
    return 0;
}

bool ternario(Agen<T> A)
{
    if(A.raiz() != Agen<T>::NODO_NULO)
    {
        return ternarioRec(A, A.raiz());
    }
    else
    {
        return true;
    }
}

bool ternarioRec(Agen<T> A, Agen<T>::nodo n)
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
                Agen<T>::nodo p = A.hijoIzqdo(n);
                while(p != Agen<T>::NODO_NULO)
                {
                    ternarioRec(A, p);
                    p = A.hermDrcho(p);
                }
            }
            else
            {
                false;
            }
        }
    }
}

bool contar(Agen<T> A, Agen<T>::nodo n)
{
    int suma = 0;
    Agen<T>::nodo p = A.hijoIzqdo(n);
    while(A.hermDrcho(p) != Agen<T>::NODO_NULO)
    {
        suma++;
        p = A.hermDrcho(p);
    }
    return suma;
}