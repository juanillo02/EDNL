/*
    EsAvl -> Recibe un arbol binario, y devuelve true si es un Arbol Binario de Busqueda Equilibrado (AVL) o false si no 
*/
#include "../Arboles/abin.hpp"

typedef char T;

bool EsAVL(Abin<T>& A)
{
    return EsABB(A, A.raiz(), '\0', '\0') && EsAVLRec(A, A.raiz());
}

bool EsABB(Abin<T>& A, Abin<T>::nodo n, T min, T max)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    T valor = A.elemento(n);
    if (valor <= min || valor >= max)
    {
        return false;
    }
    return EsABB(A, A.hijoIzqdo(n), min, valor) && EsABB(A, A.hijoDrcho(n), valor, max);
}

bool EsAVLRec(Abin<T>& A, Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        return std::abs(altura(A, A.hijoIzqdo(n)) - altura(A, A.hijoDrcho(n))) <= 1 && EsAVLRec(A, A.hijoIzqdo(n)) && EsAVLRec(A, A.hijoDrcho(n));
    }
}

int altura(Abin<T>& A, Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(altura(A, A.hijoIzqdo(n)), altura(A, A.hijoDrcho(n)));
    }
}