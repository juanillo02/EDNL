/*
Implementa un subprograma que determine si un árbol binario es o no pseudocompleto.
En este problema entenderemos que un árbol es pseudocompleto, si en el penúltimo nivel del mismo cada uno de los nodos tiene dos hijos o ninguno. 
*/

#include "abin.hpp"
#include <iostream>

typedef char T;

bool Pseudocompleto(Abin<T> A);
bool PseudocompletoRec(Abin<T> A, Abin<T>::nodo n, int altura);
int AlturaRec(Abin<T> A, Abin<T>::nodo n);
int ProfundidadRec(Abin<T> A, Abin<T>::nodo n);

int main()
{
    Abin<T> A;
    if(Pseudocompleto(A))
    {
        std::cout << "Es pseudocompleto" << std::endl;
    }
    else
    {
        std::cout << "No es pseudocompleto" << std::endl;
    }
    return 0;
}

bool Pseudocompleto(Abin<T> A)
{
    if(A.arbolVacio())
    {
        return false;
    }
    else
    {
        int altura = AlturaRec(A, A.raiz());
        return PseudocompletoRec(A, A.raiz(), altura);
    }
}

bool PseudocompletoRec(Abin<T> A, Abin<T>::nodo n, int altura)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(ProfundidadRec(A, A.raiz()) != altura - 1)
        {
            return PseudocompletoRec(A, A.hijoDrcho(n), altura) && PseudocompletoRec(A, A.hijoIzqdo(n), altura);
        }
        else
        {
            if ((A.hijoDrcho(n) == Abin<T>::NODO_NULO && A.hijoIzqdo(n) == Abin<T>::NODO_NULO) || (A.hijoDrcho(n) != Abin<T>::NODO_NULO && A.hijoIzqdo(n) != Abin<T>::NODO_NULO))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

int AlturaRec(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(AlturaRec(A, A.hijoIzqdo(n)), AlturaRec(A, A.hijoDrcho(n)));
    }
}

int ProfundidadRec(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + ProfundidadRec(A, A.padre(n));
    }
}