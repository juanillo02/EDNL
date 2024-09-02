/*
Contar cuantos nodos del árbol A tienen exactamente 3 nietos.
*/

#include "../Agen/agen.hpp"
#include <iostream>

typedef char T;

int nietos(Agen<T>& A)
{
    if(!(A.raiz() == Agen<T>::NODO_NULO))
    {
        int cont = 0;
        return nietosRec(A, A.raiz(), cont);
    }else{
        return 0;
    }
}

int nietosRec(Agen<T>& A, Agen<T>::nodo n, int cont)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return cont;
    }
    else
    {
        Agen<T>::nodo ni = A.hijoIzqdo(n);
        if(ni != Agen<T>::NODO_NULO)
        {
            cont += contarNietos(A, ni);
            Agen<T>::nodo nd = A.hermDrcho(n);
            while(nd != Agen<T>::NODO_NULO)
            {
                cont += contarNietos(A, nd);
                nd = A.hermDrcho(nd);
            }
            nietosRec(A, ni, cont);
        }
    }
}

int contarNietos(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int cont = 0;
        Agen<T>::nodo ni = A.hijoIzqdo(n);
        if(ni != Agen<T>::NODO_NULO)
        {
            cont ++;
            Agen<T>::nodo nd = A.hermDrcho(ni);
            while(nd != Agen<T>::NODO_NULO)
            {
                cont ++;
                nd = A.hermDrcho(nd);
            }
            if(cont == 3)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
}