#ifndef AGEN_HPP
#define AGEN_HPP
#include <cassert>

template <typename T> class Agen {
struct celda; // DeclaraciÃ³n adelantada privada
public:
    typedef celda* nodo;
    static const nodo NODO_NULO;
    Agen(); // Constructor
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHermDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHermDrcho(nodo n);
    void eliminarRaiz();
    const T& elemento(nodo n) const; // Lectura en Agen const
    T& elemento(nodo n); // Lectura/escritura en Agen no-const
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hermDrcho(nodo n) const;
    Agen(const Agen<T>& a); // Ctor. de copia
    Agen<T>& operator =(const Agen<T>& a); // AsignaciÃ³n de Ã¡rboles
    ~Agen(); // Destructor
private:
    struct celda {
        T elto;
        nodo padre, hizq, heder;
        celda(const T& e, nodo p = NODO_NULO): elto(e),
        padre(p), hizq(NODO_NULO), heder(NODO_NULO) {}
    };
    nodo r; // nodo raÃ­z del Ã¡rbol
    void destruirNodos(nodo& n);
    nodo copiar(nodo n);
};

/* DefiniciÃ³n del nodo nulo */
template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(nullptr);

/*--------------------------------------------------------*/
/* MÃ©todos pÃºblicos */
/*--------------------------------------------------------*/
template <typename T>
inline Agen<T>::Agen() : r(NODO_NULO) {}

template <typename T>
inline void Agen<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO); // Ãrbol vacÃ­o.
    r = new celda(e);
}

template <typename T>
inline void Agen<T>::insertarHermDrcho(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n != r); // n no es la raÃ­z.
    nodo hedrcho = n->heder; // Hermano drcho. actual
    n->heder = new celda(e, n->padre);
    n->heder->heder = hedrcho; // El actual hermano drcho. se convierte
    // en hermano drcho. del nuevo.
}

template <typename T>
inline void Agen<T>::eliminarHijoIzqdo(nodo n)
{
    nodo hizqdo;
    assert(n != NODO_NULO);
    hizqdo = n->hizq;
    assert(hizqdo != NODO_NULO); // Existe hijo izqdo.
    assert(hizqdo->hizq == NODO_NULO); // Hijo izqdo. es hoja.
    // El hermano drcho. pasa a ser el nuevo hijo izqdo.
    n->hizq = hizqdo->heder;
    delete hizqdo;
}

template <typename T>
inline void Agen<T>::eliminarHermDrcho(nodo n)
{
    nodo hedrcho;
    assert(n != NODO_NULO);
    hedrcho = n->heder;
    assert(hedrcho != NODO_NULO); // Existe hermano drcho.
    assert(hedrcho->hizq == NODO_NULO); // Hermano drcho. es hoja.
    // El hermano del hermano se convierte en el
    // nuevo hermano drcho. de n.
    n->heder = hedrcho->heder;
    delete hedrcho;
}

template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(r != NODO_NULO); // Ãrbol no vacÃ­o.
    assert(r->hizq == NODO_NULO); // La raÃ­z es hoja.
    delete(r);
    r = NODO_NULO;
}
template <typename T>
inline const T& Agen<T>::elemento(nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline T& Agen<T>::elemento(nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return r;
}

template <typename T>
typename Agen<T>::nodo Agen<T>::padre(nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::hijoIzqdo(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::hermDrcho(nodo n) const
{
    assert(n != NODO_NULO);
    return n->heder;
}

template <typename T>
inline Agen<T>::Agen(const Agen<T>& A)
{
    r = copiar(A.r); // Copiar raÃ­z y descendientes.
}

template <typename T>
Agen<T>& Agen<T>::operator =(const Agen<T>& A)
{
    if (this != &A) // Evitar autoasignaciÃ³n.
    {
        this->~Agen(); // Vaciar el Ã¡rbol.
        r = copiar(A.r); // Copiar raÃ­z y descendientes.
    }
    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    destruirNodos(r); // Vaciar el Ã¡rbol.
}

/*--------------------------------------------------------*/
/* MÃ©todos privados */
/*--------------------------------------------------------*/
// Destruye un nodo y todos sus descendientes
template <typename T>
void Agen<T>::destruirNodos(nodo& n)
{
    if (n != NODO_NULO)
    {
        if (n->hizq != NODO_NULO)
        { // Destruir hermanos del hijo izqdo.
            nodo hedrcho = n->hizq->heder;
            while (hedrcho != NODO_NULO)
            {
                n->hizq->heder = hedrcho->heder;
                destruirNodos(hedrcho);
                hedrcho = n->hizq->heder;
            }
            destruirNodos(n->hizq); // Destruir el hijo izqdo.
        }
        delete(n);
        n = NODO_NULO;
    }
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Agen<T>::nodo Agen<T>::copiar(nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto); // Copiar n.
        if (n->hizq != NODO_NULO) { // n tiene descendientes.
            m->hizq = copiar(n->hizq); // Copiar primer subÃ¡rbol.
            m->hizq->padre = m;
            // Copiar el resto de subÃ¡rboles.
            nodo hijo = m->hizq; // Ãšltimo subÃ¡rbol copiado.
            nodo hedrcho = n->hizq->heder; // Siguiente subÃ¡rbol a copiar
            while (hedrcho != NODO_NULO) {
                hijo = hijo->heder = copiar(hedrcho);
                hijo->padre = m;
                hedrcho = hedrcho->heder;
            }
        }
    }
    return m;
}

#endif

/*ESPECIFICACION AGEN*/

/*
Agen()
Â·Post: Construye un Ã¡rbol vacÃ­o.

void insertarRaiz (const T& e)
Â·Pre: El Ã¡rbol estÃ¡ vacÃ­o.
Â·Post: Inserta el nodo raÃ­z de A cuyo contenido serÃ¡ e. 

void insertarHijoIzqdo(nodo n, const T& e)
Â·Pre: n es un nodo del Ã¡rbol.
Â·Post: Inserta el elemento e como hijo izquierdo del nodo n. Si ya existe hijo 
izquierdo, Ã©ste se convierte en el hermano derecho del nuevo nodo.

void insertarHermDrcho(nodo n, const T& e)
Â·Pre: n es un nodo del Ã¡rbol y no es el nodo raÃ­z.
Â·Post: Inserta el elemento e como hermano derecho del nodo n del Ã¡rbol. 
Si ya existe hermano derecho, Ã©ste se convierte en el hermano derecho 
del nuevo nodo.

void eliminarHijoIzqdo(nodo n)
Â·Pre: n es un nodo del Ã¡rbol. Existe hijoIzqdo(n) y es una hoja.
Â·Post: Destruye el hijo izquierdo del nodo n. El segundo hijo, si existe, 
se convierte en el nuevo hijo izquierdo de n. 

void eliminarHermDrcho(nodo n)
Â·Pre: n es un nodo del Ã¡rbol. Existe hermDrcho(n) y es una hoja.
Â·Post: Destruye el hermano derecho del nodo n. El siguiente hermano 
se convierte en el nuevo hermano derecho de n. 

void eliminarRaiz()
Â·Pre: El Ã¡rbol no estÃ¡ vacÃ­o y raiz() es una hoja.
Â·Post: Destruye el nodo raÃ­z. El Ã¡rbol queda vacÃ­o.

const T& elemento(nodo n) const
const T& elemento(nodo n)
Â·Pre: n es un nodo del Ã¡rbol.
Â·Post: Devuelve el elemento del nodo n.

nodo raiz() const
Â·Post: Devuelve el nodo raÃ­z del Ã¡rbol. Si el Ã¡rbol estÃ¡ vacÃ­o, devuelve NODO_NULO. 

nodo padre(nodo n) const
Â·Pre: n es un nodo del Ã¡rbol.
Â·Post: Devuelve el padre del nodo n. Si n es el nodo raÃ­z, devuelve NODO_NULO. 

nodo hijoIzqdo(nodo n) const
Â·Pre: n es un nodo del Ã¡rbol.
Â·Post: Devuelve el hijo izquierdo del nodo n. Si no existe, devuelve NODO_NULO. 

nodo hermDrcho(nodo n) const
Â·Pre: n es un nodo del Ã¡rbol.
Â·Post: Devuelve el hermano derecho del nodo n. Si no existe, devuelve 
NODO_NULO.*/