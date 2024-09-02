/*
Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice la poda de A a partir de x. Se asume que no hay elementos repetidos en A. 
*/

#include <iostream>
#include "agen.hpp"


const int fin = 0;

void Poda(Agen<int>, int);
void PodaRec(Agen<int>, Agen<int>::nodo, int);
void Podar(Agen<int>, Agen<int>::nodo, int);


int main()
{
    Agen<int> A;
    Poda(A, 3);
    std::cout << "Se ha cumplido la Poda" << std::endl;

    return 0;
}

void Poda(Agen<int> A, int x)
{
    if(A.raiz() != Agen<int>::NODO_NULO)
    {
        PodaRec(A, A.raiz(), x);
    }
}

void PodaRec(Agen<int> A, Agen<int>::nodo n, int x)
{
    if (n != Agen<int>::NODO_NULO)
    {
        if(A.elemento(n) == x)
        {
            Podar(A, n, x);
        }
        else
        {
            Agen<int>::nodo p = A.hijoIzqdo(n);
            while(p != Agen<int>::NODO_NULO)
            {
                PodaRec(A, p, x);
                p = A.hermDrcho(p);
            }
        }
    }
}

void Podar(Agen<int> A, Agen<int>::nodo n, int x)
{
    Agen<int>::nodo hi = A.hijoIzqdo(n);
    Agen<int>::nodo hd = A.hermDrcho(hi);
    if(hi != Agen<int>::NODO_NULO && hd != Agen<int>::NODO_NULO)
    {
        if(A.hijoIzqdo(hi) != Agen<int>::NODO_NULO)
        {
            Podar(A, hi, x);  //podamos el/los hijos(del hijo izquierdo)
            Podar(A, n, x);   //llamada para podar hijo izquierdo
        }
        else
        {
            A.eliminarHijoIzqdo(n); //podamos hijo izquierdo 
            Podar(A, n, x);   //lamada para podar a su hermano derecho (nuevo hijo izquierdo)
        }
    }
    if(hi != Agen<int>::NODO_NULO && hd == Agen<int>::NODO_NULO)
    {
        A.eliminarHijoIzqdo(n); //podamos el hijo izquierdo unico y no llamamos mas por que solo queda este :)
    }
}