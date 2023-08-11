template <typename T>
string_map<T>::string_map(){
raiz= nullptr;
_size=0;
_claves={};
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {

    for(string clave : d._claves){
        T significado = d.at(clave);
        insert(make_pair(clave,significado));
    }

    return *this;
}

template <typename T>
string_map<T>::~string_map(){

    set<string> claves = _claves;
    for(string clave : claves){
        erase(clave);
    }
    delete raiz;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>  & tupla) {

    if(raiz == nullptr){
        Nodo* n = new Nodo();
        raiz = n;
    }

    Nodo* aux = raiz;
    for (int i = 0; i <tupla.first.size(); i++) {
        int caracter = int(tupla.first[i]);
        if(aux->siguientes[caracter] == nullptr){
            Nodo *n = new Nodo();
            aux->siguientes[caracter] = n;
            aux = n;
        }else{
            aux = aux->siguientes[caracter];
        }
    }

    if(aux->definicion != nullptr){
        *(aux->definicion) = tupla.second;
    }else{
        T* p = new T();
        *p = tupla.second;
        aux->definicion = p;
        _size = _size + 1;
        _claves.insert(tupla.first);
    }

}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{

    if(empty()){
        return 0;
    }

    Nodo* aux = raiz;

    for(int i=0;i<clave.size();i++){
        int caracter = int(clave[i]);
        if(aux->siguientes[caracter] == nullptr){
            return 0;
        }
        aux = aux->siguientes[caracter];
    }
    if(aux->definicion!= nullptr){
        return 1;
    }else{
        return 0;
    }

}

template <typename T>
const T& string_map<T>::at(const string& clave) const {

    Nodo* aux = raiz;

    for(int i=0;i<clave.size();i++){
        int caracter = int(clave[i]);
        aux = aux->siguientes[caracter];
    }
    return *aux->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {

    Nodo* aux = raiz;

    for(int i=0;i<clave.size();i++){
        int caracter = int(clave[i]);
        aux = aux->siguientes[caracter];
    }
    return *aux->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {

    eraseAux(raiz,clave);
    _claves.erase(clave);
}

template <typename T>
void string_map<T>::eraseAux(Nodo* n, const string& clave) {

    if(clave.size()==0){
        delete n->definicion;   
        n->definicion = nullptr;
        _size = _size - 1;
    }else{
        eraseAux(n->siguientes[int(clave[0])], clave.substr(1,clave.size()));
        if(esHoja(n->siguientes[int(clave[0])]) && n->siguientes[int(clave[0])]->definicion == nullptr){
            delete n->siguientes[int(clave[0])];
            n->siguientes[int(clave[0])] = nullptr;
        }
    }
}



template <typename T>
int string_map<T>::size() const{

    return _size;
}

template <typename T>
bool string_map<T>::empty() const{

    return _size == 0;
}

template <typename T>
bool string_map<T>::esHoja(Nodo* n){

    for(int i=0;i<n->siguientes.size();i++){
        if(n->siguientes[i]!= nullptr){
            return false;
        }
    }
    return true;
}

