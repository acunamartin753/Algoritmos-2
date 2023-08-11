#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
}

template <class T>
void Conjunto<T>::destruir(Nodo* n) {
if(n!= nullptr){
    destruir(n->izq);
    destruir(n->der);
    delete n;
    }
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
    _raiz = nullptr;
}


template <class T>
bool Conjunto<T>::perteneceAux(Nodo* n, const T& clave) const {

    bool res = false;

    if(n != nullptr){
        if (n->valor==clave){
            res = true;
        } else if (n->valor<clave){
            res = perteneceAux(n->der, clave);
        } else {
            res = perteneceAux(n->izq, clave);
        }
    }

    return res;

}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {

    return perteneceAux(_raiz, clave);
}



template <class T>
void Conjunto<T>::insertar(const T& clave) {

    if(!pertenece(clave)){
        insertarAux(_raiz, clave);
    }

}

template <class T>
void Conjunto<T>::insertarAux(Nodo* &n, const T& clave) {

    if(n == nullptr){
        n = new Nodo(clave);
    }else if(clave<n->valor){
        insertarAux(n->izq,clave);
    }else{
        insertarAux(n->der,clave);
    }

}

template <class T>
void Conjunto<T>::removerAux(Nodo* &n, const T& clave) {
    if (n->valor == clave) {
        if (esHoja(n)) {
            delete n;
            n = nullptr;

        } else if (tieneSoloUnHijo(n)) {
            if (tieneHijoDerecho(n)) {
                n->valor = n->der->valor;
                if(tieneHijoIzquierdo(n->der)){
                    n->izq = n->der->izq;
                    n->der->izq = nullptr;
                }
                removerAux(n->der, n->der->valor);
            } else {
                n->valor = n->izq->valor;
                if(tieneHijoDerecho(n->izq)){
                    n->der = n->izq->der;
                    n->izq->der = nullptr;
                }
                removerAux(n->izq, n->izq->valor);
            }
        } else {
            const T& sucesor = minimoAux(n->der);
            n->valor = sucesor;
            removerAux(n->der, sucesor);
        }
    }else if (n->valor < clave) {
        removerAux(n->der, clave);
    } else {
        removerAux(n->izq, clave);
    }
}


template <class T>
void Conjunto<T>::remover(const T& clave) {

    if(pertenece(clave)){
        removerAux(_raiz,clave);
    }
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::encontrar(Nodo* n, const T& clave) const {

    Nodo* res = n;

    if (n->valor!=clave) {

        if (n->valor < clave) {
            res = encontrar(n->der, clave);
        } else {
            res = encontrar(n->izq, clave);
        }

    }
    return res;

}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::encontrarPadre(Nodo* n, const T& clave) const {

    Nodo* res = n;
    if (n->der->valor!=clave && n->izq->valor!=clave) {

        if (n->valor < clave) {
            res = encontrarPadre(n->der, clave);
        } else {
            res = encontrarPadre(n->izq, clave);
        }

    }
    return res;
}


template<class T>
const T &Conjunto<T>::buscarDerecha(Conjunto::Nodo * n) const {
    Nodo* ptrPadre = encontrarPadre(_raiz, n->valor);
    if(ptrPadre->izq->valor==n->valor){
        return ptrPadre->valor;
    }else{
        buscarDerecha(ptrPadre);
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {

    Nodo* ptrClave = encontrar(_raiz, clave);
    Nodo* ptrPadre = encontrarPadre(_raiz, clave);
    if(!esVacio(ptrClave->der)){
        return minimoAux(ptrClave->der);
    }else{
        if(ptrPadre->izq->valor==clave){
            return ptrPadre->valor;
        }else{
            return buscarDerecha(ptrPadre);
        }
    }
}


template <class T>
const T& Conjunto<T>::minimoAux(Nodo* n) const {

    while(n->izq!= nullptr){
        n=n->izq;
    }
    return n->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {

    return minimoAux(_raiz);
}

template <class T>
const T& Conjunto<T>::maximo() const {

    return maximoAux(_raiz);
}

template <class T>
const T& Conjunto<T>::maximoAux(Nodo* n) const {

    while(n->der!= nullptr){
        n=n->der;
    }
    return n->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinalAux(Nodo* n) const {
    unsigned int res = 0;
    if(n != nullptr){
        res = 1 + cardinalAux(n->izq) + cardinalAux(n->der);
    }
    return res;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinalAux(_raiz);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template<class T>
bool Conjunto<T>::esHoja(Conjunto::Nodo* n) {
     return (cardinalAux(n->izq) + cardinalAux(n->der))==0;
}

template<class T>
bool Conjunto<T>::tieneSoloUnHijo(Conjunto::Nodo* n) {
    return (n->izq == nullptr || n->der == nullptr) && !esHoja(n);
}

template<class T>
bool Conjunto<T>::esVacio(Conjunto::Nodo* n) {
    return n== nullptr;
}


template<class T>
bool Conjunto<T>::tieneHijoDerecho(Conjunto::Nodo* n) {
    return (n->der != nullptr);
}


template<class T>
bool Conjunto<T>::tieneHijoIzquierdo(Conjunto::Nodo* n) {
    return (n->izq != nullptr);
}



