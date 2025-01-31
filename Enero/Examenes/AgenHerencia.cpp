/*
Dado un árbol general donde sus nodos pueden estar vivos o muertos, implementa una función en C++ que, dado un nodo n de éste con una riqueza
acumulada, simule un reparto entre todos sus herederos. Son herederos de un nodo n sus hijos vivos y sus hijos muertos con descendientes vivos.
Para hacer el reparto se divide en cantidades exactamente iguales entre todos sus herederos y, en cuyo caso no sea exacto, el resto se lo quedará
el erario público. Un nodo seguirá heredando hasta el final, si sigue cumpliendo la condición, o hasta que no quede más riqueza que repartir.
*/
#include "../Arboles/Agen.hpp"
#include <vector>

void riqueza(Agen<double>& A, Agen<double>::nodo n)
{
    if(n != Agen<double>::NODO_NULO)
    {
        int numero = Herederos(A, n);
        if(numero > 0)
        {
            double cantidad = A.elemento(n) / numero;
            A.elemento(n) = 0;
            Agen<double>::nodo aux = A.hijoIzqdo(n);
            while(aux != Agen<double>::NODO_NULO)
            {
                if(A.elemento(aux) > 0)
                {
                    A.elemento(aux) = cantidad;
                    riqueza(A, aux);
                }
                else if(descendientes(A, aux))
                {
                    riqueza(A, aux);
                }
                aux = A.hermDrcho(aux);
            }
        }
        else
        {
            A.elemento(n) = 0;
        }
    }
}

bool descendientes(Agen<double>& A, Agen<double>::nodo n)
{
    Agen<double>::nodo aux = A.hijoIzqdo(n);
    while(aux != Agen<double>::NODO_NULO)
    {
        if(A.elemento(aux) > 0 || descendientes(A, aux))
        {
            return true;
        }
        aux = A.hermDrcho(aux);
    }
    return false;
}

int Herederos(Agen<double>& A, Agen<double>::nodo n)
{
    int numero = 0;
    Agen<double>::nodo aux = A.hijoIzqdo(n);
    while(aux != Agen<double>::NODO_NULO)
    {
        if(A.elemento(aux) > 0 || descendientes(A, aux))
        {
            numero++;
        }
        aux = A.hermDrcho(aux);
    }
    return numero;
}