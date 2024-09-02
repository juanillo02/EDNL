/*
    Contar descendientes: 'Dado un árbol general, contar el número de nodos de dicho árbol que tienen 4 descendientes.'
*/

#include "../Agen/agen.hpp"
#include <iostream>

typedef char T;

int descendientes(Agen<T>& A)
{
    if(!(A.raiz() != Agen<T>::NODO_NULO))
    {
        int cont = 0;
        return descendientesRec(A, A.raiz(), cont);
    }else{
        return 0;
    }
}

int descendientesRec(Agen<T>& A, Agen<T>::nodo n, int cont)
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
            while(ni != Agen<T>::NODO_NULO)
            {
                cont += Contar(A, ni);
                Agen<T>::nodo nd = A.hermDrcho(ni);
                while(nd != Agen<T>::NODO_NULO)
                {
                    cont += Contar(A, nd);
                    nd = A.hermDrcho(nd);
                }
                ni = A.hermDrcho(ni);
            }
            descendientesRec(A, ni, cont);
        }
    }
}

int Contar(Agen<T>& A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int cont;
        Agen<T>::nodo ni = A.hijoIzqdo(n);
        while(ni != Agen<T>::NODO_NULO)
        {
            cont ++;
            Agen<T>::nodo nd = A.hermDrcho(ni);
            {
                while(nd != Agen<T>::NODO_NULO)
                {
                    cont ++;
                    nd = A.hermDrcho(nd);
                }
            }
            ni = A.hijoIzqdo(n);
        }
        if(cont == 4)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}