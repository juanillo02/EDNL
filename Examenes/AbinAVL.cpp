/*EsAvl -> Recibe un arbol binario, y devuelve true si es un Arbol Binario de Busqueda Equilibrado (AVL) o false si no*/
#include <iostream>
#include <cmath>
#include <limits>
#include "../Arboles/abin.h"

typedef char tElto;

int altura(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(altura(A, A.hijoIzqdo(n)), altura(A, A.hijoDrcho(n)));
    }
}

bool EsABB(Abin<tElto>& A, Abin<tElto>::nodo n, tElto min, tElto max)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    tElto valor = A.elemento(n);
    if (valor <= min || valor >= max)
    {
        return false;
    }
    else
    {
        return EsABB(A, A.hijoIzqdo(n), min, valor) && EsABB(A, A.hijoDrcho(n), valor, max);   
    }
}
    

bool EsAVLRec(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true; // Un nodo nulo es considerado AVL
    }
    else
    {
        return std::abs(altura(A, A.hijoIzqdo(n)) - altura(A, A.hijoDrcho(n))) <= 1 && EsAVLRec(A, A.hijoIzqdo(n)) && EsAVLRec(A, A.hijoDrcho(n));
    }
}

bool EsAVL(Abin<tElto>& A)
{
    return EsABB(A, A.raiz(), std::numeric_limits<tElto>::min(), std::numeric_limits<tElto>::max()) && EsAVLRec(A, A.raiz());
}

int main() {
    Abin<tElto> A1;
    A1.insertarRaiz('M');
    A1.insertarHijoIzqdo(A1.raiz(), 'F');
    A1.insertarHijoDrcho(A1.raiz(), 'T');
    A1.insertarHijoIzqdo(A1.hijoIzqdo(A1.raiz()), 'C');
    A1.insertarHijoDrcho(A1.hijoIzqdo(A1.raiz()), 'H');
    A1.insertarHijoIzqdo(A1.hijoDrcho(A1.raiz()), 'P');
    A1.insertarHijoDrcho(A1.hijoDrcho(A1.raiz()), 'X');
    std::cout << "¿A1 es un AVL? " << (EsAVL(A1) ? "Sí" : "No") << std::endl; // Esperado: Sí
    Abin<tElto> A2;
    A2.insertarRaiz('M');
    A2.insertarHijoIzqdo(A2.raiz(), 'F');
    A2.insertarHijoIzqdo(A2.hijoIzqdo(A2.raiz()), 'C');
    A2.insertarHijoIzqdo(A2.hijoIzqdo(A2.hijoIzqdo(A2.raiz())), 'A');
    std::cout << "¿A2 es un AVL? " << (EsAVL(A2) ? "Sí" : "No") << std::endl; // Esperado: No
    return 0;
}