#include "Mapa.h"

Mapa::Mapa(const set<int>& hs, const set<int>& vs) : _horizontales(hs),_verticales(vs){}

Mapa &Mapa::operator=(const Mapa aCopiar) {
    this->_horizontales = aCopiar._horizontales;
    this->_verticales = aCopiar._verticales;

    return *this;
}

set<int> Mapa::horizontales() const{
    return _horizontales;
}

set<int> Mapa::verticales() const{
    return _verticales;
}
