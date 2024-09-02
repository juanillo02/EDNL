#include <iostream>
#include "../Abin/abin.hpp"

typedef char T;

bool Psudocompleto(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        int altura = AlturaRec(A, A.raiz());
        return PseudocompletoRec(A, A.raiz(), altura);
    }
    else
    {
        return false;
    }
}

bool PseudocompletoRec(Abin<T>& A, Abin<T>::nodo n, int altura)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(ProfundidadRec(A, n) != altura - 1)
        {
            return PseudocompletoRec(A, A.hijoIzqdo(n), altura) && PseudocompletoRec(A, A.hijoDrcho(n), altura);
        }
        else
        {
            if(A.hijoDrcho(n) == Abin<T>::NODO_NULO && A.hijoIzqdo(n) == Abin<T>::NODO_NULO)
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

int AlturaRec(Abin<T>& A, Abin<T>::nodo n)
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

int ProfundidadRec(Abin<T>& A, Abin<T>::nodo n)
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