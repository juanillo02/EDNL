#include <iostream>
#include "../Agen/agen.hpp"

typedef char T;

bool Recorrer(Agen<T>& A, char c)
{
    return RecorrerRec(A, A.raiz(), c);
}

bool RecorrerRec(Agen<T>& A, Agen<T>::nodo n, char c)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return false;
    }
    else
    {
        if(A.elemento(n) == c)
        {
            return true;
        }
        else
        {
            bool encontrado = false;
            Agen<T>::nodo aux = A.hijoIzqdo(n);
            while(aux != Agen<T>::NODO_NULO)
            {
                encontrado = RecorrerRec(A, aux, c);
                aux = A.hermDrcho(aux);
            }
            return encontrado;
        }
    }
}