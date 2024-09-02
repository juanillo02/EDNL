#include "../Agen/agen.hpp"

typedef char T;

bool Similar(Agen<T>& A, Agen<T>& B)
{
    return SimilarRec(A, B, A.raiz(), B.raiz());
}

bool SimilarRec(Agen<T>& A, Agen<T>& B, Agen<T>::nodo na, Agen<T>::nodo nb)
{
    if(na == Agen<T>::NODO_NULO && nb == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else if((na == Agen<T>::NODO_NULO && nb != Agen<T>::NODO_NULO) || (na != Agen<T>::NODO_NULO && nb == Agen<T>::NODO_NULO))
    {
        if(A.hijoIzqdo(na) == Agen<T>::NODO_NULO && B.hijoIzqdo(nb) == Agen<T>::NODO_NULO)
        {
            return true;
        }
        else if(A.hijoIzqdo(na) != Agen<T>::NODO_NULO && B.hijoIzqdo(nb) != Agen<T>::NODO_NULO)
        {
            bool similar = false;
            Agen<T>::nodo aux = A.hijoIzqdo(na), aux2 = B.hijoIzqdo(nb);
            while(aux != Agen<T>::NODO_NULO && aux2 != Agen<T>::NODO_NULO)
            {
                similar = SimilarRec(A, B, aux, aux2);
                aux = A.hermDrcho(aux);
                aux2 = B.hermDrcho(aux2);
            }
            return similar;
        }
    }
}