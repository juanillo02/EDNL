/*Contar cuantos nodos del árbol A tienen exactamente 3 nietos.*/
#include <iostream> 
#include <fstream> 
#include "../Arboles/abin.h" 
#include "../Arboles/abin_E-S.h" 
 
using namespace std; 
 
typedef char tElto;

int nietosRec(const Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        Abin<tElto>::nodo hi = A.hijoIzqdo(n), hd = A.hijoDrcho(n);
        if(hi != Abin<tElto>::NODO_NULO && hd != Abin<tElto>::NODO_NULO)
        {
            if((A.hijoIzqdo(hi) != Abin<tElto>::NODO_NULO && A.hijoDrcho(hi) != Abin<tElto>::NODO_NULO && A.hijoIzqdo(hd) != Abin<tElto>::NODO_NULO && A.hijoDrcho(hd) == Abin<tElto>::NODO_NULO) || (A.hijoIzqdo(hi) != Abin<tElto>::NODO_NULO && A.hijoDrcho(hi) != Abin<tElto>::NODO_NULO && A.hijoIzqdo(hd) == Abin<tElto>::NODO_NULO && A.hijoDrcho(hd) != Abin<tElto>::NODO_NULO) || (A.hijoIzqdo(hi) != Abin<tElto>::NODO_NULO && A.hijoDrcho(hi) == Abin<tElto>::NODO_NULO && A.hijoIzqdo(hd) != Abin<tElto>::NODO_NULO && A.hijoDrcho(hd) != Abin<tElto>::NODO_NULO) || (A.hijoIzqdo(hi) == Abin<tElto>::NODO_NULO && A.hijoDrcho(hi) != Abin<tElto>::NODO_NULO && A.hijoIzqdo(hd) != Abin<tElto>::NODO_NULO && A.hijoDrcho(hd) != Abin<tElto>::NODO_NULO))
            {
                return 1 + nietosRec(A, hi) + nietosRec(A, hd);
            }
            else
            {
                return nietosRec(A, hi) + nietosRec(A, hd);
            }
        }
        else
        {
            return nietosRec(A, hi) + nietosRec(A, hd);;
        }
    }
}

int nietos(const Abin<tElto>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return nietosRec(A, A.raiz());
    }
}

int main()
{
    Abin<tElto> A;

    A.insertarRaiz('A'); // nivel 0

    A.insertarHijoIzqdo(A.raiz(), 'B'); // nivel 1
    A.insertarHijoDrcho(A.raiz(), 'C'); // nivel 1

    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 'D'); // nivel 2
    A.insertarHijoDrcho(A.hijoIzqdo(A.raiz()), 'E'); // nivel 2
    A.insertarHijoIzqdo(A.hijoDrcho(A.raiz()), 'F'); // nivel 2
    A.insertarHijoDrcho(A.hijoDrcho(A.raiz()), 'G'); // nivel 2

    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'H'); // nivel 3
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'I'); // nivel 3
    A.insertarHijoIzqdo(A.hijoDrcho(A.hijoIzqdo(A.raiz())), 'J'); // nivel 3

    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 'K'); // nivel 4
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 'L'); // nivel 4
    A.insertarHijoIzqdo(A.hijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 'M'); // nivel 4

    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())))), 'N'); // nivel 5
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())))), 'O'); // nivel 5

    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))))), 'P'); // nivel 6
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))))), 'Q'); // nivel 6

    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())))))), 'R'); // nivel 7

    // Contar nodos con exactamente 3 nietos
    int resultado = nietos(A);
    cout << "Nodos con exactamente 3 nietos: " << resultado << endl;

    return 0;
}
