template<typename T>
string_map<T>::Nodo::Nodo(): siguientes(256, nullptr), definicion(nullptr) {};

template <typename T>
string_map<T>::string_map(): raiz(nullptr), _size(0), claves_(){};

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;

} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {

    //destruir(this->raiz);
    // falta destruir los nodos de this??
    ///aca estaba el problema....           duda, despues preguntar??
    this->raiz = nullptr;
    this->_size = 0;
    this->claves_.clear(); //elimino los elementos

    for(string c :d.claves_){
        T signi = d.at(c);
        this->insert(make_pair(c,signi));
    }

    return *this;
}


template <typename T>
void string_map<T>::destruir(Nodo* actual) {
    /*
    vector<Nodo*> h = actual->siguientes;
    for (int i = 0; i <h.size() ; ++i) {
        if(h[i] != nullptr){
            destruir(h[i]);
        }
    }*/

    for (Nodo* e: actual->siguientes) {
        if(e != nullptr){
            destruir(e);
        }
    }
    if(actual->definicion != nullptr){
        delete actual->definicion;
    }
    delete actual;


}
template <typename T>
string_map<T>::~string_map(){  //destructor
    if(raiz != nullptr){
        destruir(raiz);
    }

}

template <typename T>
void string_map<T>::insert(const pair<string, T>  & tupla) {
    /*necesito ver primero si la clave esta definida
    creo otra funcion???? si T != nullptr despues de encontrar el ultimo caracter entonces la clave esta definida
     ya hay una funcion definida count
     */
    claves_.insert(tupla.first); //agrego una clave al conjunto

    if(raiz == nullptr){
        Nodo* x = new Nodo();
        raiz = x;
    }

    Nodo* aux = raiz;
    for (int i = 0; i <tupla.first.size() ; ++i) {
        int caracter = int(tupla.first[i]);
        if(aux->siguientes[caracter] == nullptr){

            Nodo *x = new Nodo();
            aux->siguientes[caracter] = x;
            aux = x;
        }else{

            aux = aux->siguientes[caracter];

        }
    }
    //me tengo que fijar si ya esta definida....  ---terminado
    if(aux->definicion != nullptr){
        *(aux->definicion) = tupla.second;
    }else{
        T* p = new T();
        *p = tupla.second;
        aux->definicion = p;
        _size = _size +1; // pues no esta definida
    }

}

template <typename T>
int string_map<T>::count(const string& clave) const{
    // primero hacer esta funcion y la otra empty
    // si esta definido me entrega 1... y 0 si es falso
    if(empty()){
        return 0;
    }
    Nodo* aux = raiz;
    for (int i = 0; i <clave.size() ; ++i) { //si esta definido entonces por lo menos tiene que terminar el ciclo
        int caracter = int(clave[i]);
        if (aux->siguientes[caracter] != nullptr){ /// o sea me fijo si esta definido
            aux = aux->siguientes[caracter];
        }else{
            return 0;
        }
    }
    //algo tengo que hacer aca... el aux donde va a apuntar??
    // me tengo que fijar que la T* definicion es o no nullptr
    //tengo a aux apuntando al ultimos caracter
    if(aux->definicion != nullptr){
        return 1;
    }

    return 0;

}


template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* aux = raiz;
    for (int i = 0; i <clave.size() ; ++i) {
        int caracter = int(clave[i]);
        aux = aux->siguientes[caracter];

    }

    return *aux->definicion;

}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* aux = raiz;
    for (int i = 0; i <clave.size() ; ++i) {
        int caracter = int(clave[i]);
        aux = aux->siguientes[caracter];

    }

    return *aux->definicion;

}
template <typename T>
T& string_map<T>::operator[](const string& clave){
    //es optativa... asi que no lo hago
}
template <typename T>
int string_map<T>::cantNodos(Nodo *actual) {
    int  k = 0;

    for (int i = 0; i <actual->siguientes.size() ; ++i) {
        if(actual->siguientes[i]!= nullptr){

            k++;
        }
    }
    return k;
}

template <typename T>
void string_map<T>::erase(const string& claves) {
    // 6/17/22         la parte en la que uso el vector la puedo reemplazar por una tupla<nodo, int>

    claves_.erase(claves); //elimino una clave del conjunto

    string  clave = claves;
    Nodo* actual = raiz;
    vector<pair<Nodo*, int>> aux;  // necesito guardar el ultimo nodo que no tengo que eliminar

    aux.push_back(make_pair(actual,int(clave[0]))); // o sea que por lo menos voy a tener un elemento
    for (int i = 0; i <clave.size() ; ++i) {
        int caracter = int(clave[i]);

        if((actual->definicion != nullptr or cantNodos(actual) >1) and actual != raiz){

            aux.push_back(make_pair(actual, caracter));
        }


        actual = actual->siguientes[caracter];
    }

    //elimino la definicion...
    delete actual->definicion;
    actual->definicion = nullptr;

    if(cantNodos(actual)==0){ //quiere decir que tengo que eliminar de abajo hacia arriba
        int carac = aux[aux.size()-1].second;
        Nodo* ultAeliminar = aux[aux.size()-1].first;

        Nodo* a = ultAeliminar->siguientes[carac];
        ultAeliminar->siguientes[carac] = nullptr;
        destruir(a); ///otra manera de eliminar


        /*
        Nodo* auxiliar = nullptr;
        while(a != nullptr){
            for (int i = 0; i <256 ; ++i) {
                if(a->siguientes[i] != nullptr){
                    auxiliar = a->siguientes[i];
                }
            }

            delete a;
            a = auxiliar;
            auxiliar = nullptr;

        }           */

    }
    _size = _size - 1;

}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    bool res = raiz == nullptr;
    return res;
}