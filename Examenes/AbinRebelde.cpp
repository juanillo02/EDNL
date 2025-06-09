/* Contar cuantos nodos del árbol booleano A son rebeldes, un nodo es rebelde si es diferente que la mayoría de sus ancestros
(si es distinto de lo que sea la mayoría de sus ancestros)*/

#include <iostream>
#include "../Arboles/abin.h"

using namespace std;

int contarIguales(Abin<bool>& A, Abin<bool>::nodo n, bool aux)
{
    if(A.padre(n) == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(A.elemento(A.padre(n)) == aux)
        {
            return 1 + contarIguales(A, A.padre(n), aux);
        }
        else
        {
            return contarIguales(A, A.padre(n), aux);
        }
    }
}

int contar(Abin<bool>& A, Abin<bool>::nodo n)
{
    if(A.padre(n) == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + contar(A, A.padre(n));
    }
}

int rebeldeRec(Abin<bool>& A, Abin<bool>::nodo n)
{
    if(n == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        bool aux = A.elemento(n);
        if(contarIguales(A, n, aux) <= (contar(A, n)/2))
        {
            return 1 + rebeldeRec(A, A.hijoIzqdo(n)) + rebeldeRec(A, A.hijoDrcho(n));
        }
        else
        {
            return rebeldeRec(A, A.hijoIzqdo(n)) + rebeldeRec(A, A.hijoDrcho(n));
        }
    }
}

int rebelde(Abin<bool>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return rebeldeRec(A, A.raiz());
    }
}

int main() {
    Abin<bool> A;

    A.insertarRaiz(true);  // Raíz global

    // Subárbol izquierdo (antes A1)
    A.insertarHijoIzqdo(A.raiz(), true);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), false);
    A.insertarHijoDrcho(A.hijoIzqdo(A.raiz()), true);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), true);
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), false);
    A.insertarHijoIzqdo(A.hijoDrcho(A.hijoIzqdo(A.raiz())), false);
    A.insertarHijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.raiz())), true);

    // Subárbol derecho (antes A2)
    A.insertarHijoDrcho(A.raiz(), true);
    A.insertarHijoIzqdo(A.hijoDrcho(A.raiz()), false);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoDrcho(A.raiz())), true);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoDrcho(A.raiz()))), false);
    int R = rebelde(A);
    cout << "Cantidad total de nodos rebeldes: " << R << endl;

    return 0;
}