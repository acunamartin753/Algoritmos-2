#include "Lista.h"
Lista::Nodo::Nodo(const int& elem): valor(elem), anterior(nullptr), siguiente(nullptr){};

Lista::Lista() {
    _primero = nullptr;
    _ultimo = nullptr;
    _longitud = 0;
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

void Lista::borrarTodo() {
    while(_primero != nullptr){
        Nodo* sigue = _primero->siguiente;
        delete _primero;
        _primero = sigue;
    }
    _ultimo = nullptr;
    _longitud = 0;
}

Lista::~Lista() {
    borrarTodo();
}

Lista& Lista::operator=(const Lista& aCopiar) {

    if(longitud()>0){
        borrarTodo();
    }
    Nodo* actual = aCopiar._primero;

    while(actual != nullptr){
        agregarAtras(actual->valor);
        actual =actual->siguiente;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo *nuevo = new Nodo(elem);

    if(_primero== nullptr){
        _primero = nuevo;
        _ultimo = nuevo;
    }else {
        nuevo->siguiente = _primero;
        _primero->anterior = nuevo;
        _primero = nuevo;
    }

    _longitud++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo *nuevo = new Nodo(elem);

    if(_ultimo==nullptr){
        _primero = nuevo;
        _ultimo = nuevo;
    }else {
        nuevo->anterior=_ultimo;
        _ultimo->siguiente = nuevo;
        _ultimo = nuevo;
    }

    _longitud++;
}

void Lista::eliminar(Nat i) {
    int iteracion = 0;
    Nodo* actual = _primero;

    while(iteracion != i){
        iteracion++;
        actual = actual->siguiente;
    }

    Nodo* antes= actual->anterior;
    Nodo* despues= actual->siguiente;

    delete actual;

    if(antes!= nullptr) {
        antes->siguiente = despues;
    } else {
        _primero = despues;
    }

    if(despues!=nullptr) {
        despues->anterior = antes;
    }else{
        _ultimo = antes;
    }

    _longitud--;
}

int Lista::longitud() const {
    return _longitud;
}

const int& Lista::iesimo(Nat i) const {
    int iteracion = 0;
    Nodo* actual = _primero;
    while(iteracion != i){
        iteracion++;
        actual = actual->siguiente;
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    int iteracion = 0;
    Nodo* actual = _primero;
    while(iteracion != i){
        iteracion++;
        actual = actual->siguiente;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    Nodo* actual = _primero;
    o << "Lista: ";
    while(actual != nullptr){
        o << actual->valor << ' ';
        actual = actual->siguiente;
    }
    o << endl;
}