#include "SimCity.h"


simCity::simCity(const Mapa& _mapa) :
        _mapa(_mapa),
        _turno(0),
        _popularidad(0),
        _casas(),
        _comercios(),
        _unidos(),
        _huboConstruccion(false){}

simCity &simCity::operator=(const simCity aCopiar) {
    this->_mapa = aCopiar._mapa;
    this->_turno = aCopiar._turno;
    this->_popularidad = aCopiar._popularidad;
    this->_casas = aCopiar._casas;
    this->_comercios = aCopiar._comercios;
    this->_unidos = aCopiar._unidos;
    this->_huboConstruccion = aCopiar._huboConstruccion;

    return *this;
}

//-----------------------------------------------------------------------------------------

void simCity::agregarCasa(Casilla c) {
    _casas.insert(make_pair(c, 0));
    _huboConstruccion = true;
}

//-----------------------------------------------------------------------------------------

void simCity::agregarComercio(Casilla c) {
    _comercios.insert(make_pair(c, 0));
    _huboConstruccion = true;
}

//-----------------------------------------------------------------------------------------

void simCity::avanzarTurno() {

    _turno = _turno + 1;
    _huboConstruccion = false;

    //Creo los dicc a los que les voy a sumar 1 y reemplazarlos en el original
    map<Casilla, Nat> casasSC = _casas;
    map<Casilla, Nat> comerciosSC = _comercios;


    //Actualizo por los comercios con distancia Manhattan menor a 3
    this->actualizarPorManhattan(casasSC, comerciosSC);

    //Creo los nuevos map de casas y comercios.
    for(auto i = _unidos.begin(); i != _unidos.end(); i++){
        agregarConstruccionesUnidas(*(*i), casasSC, comerciosSC);
    }

    //Actualizo sumando 1 Nivel
    this->actualizarSumandoTurno(casasSC, comerciosSC);

    _casas = casasSC;
    _comercios = comerciosSC;
}

void simCity::actualizarSumandoTurno(map<Casilla, Nat>& casas, map<Casilla, Nat> &comercios) const {

    //Actualizo casas
    for(auto it = casas.begin(); it != casas.end(); it++){
        casas[it->first] = it->second + 1;
    }

    //Actualizo comercios
    for(auto it2 = comercios.begin(); it2 != comercios.end(); it2++){
        comercios[it2->first] = it2->second + 1;
    }

}

//-----------------------------------------------------------------------------------------

void simCity::unir(simCity* sc2) {


    //Agrego el puntero del sc2 a los unidos del sc1
    _unidos.push_back(sc2);


    //actualizo turno
    if(_turno < sc2->_turno){
        _turno = sc2->_turno;
    }

    //actualizo popularidad
    _popularidad = _popularidad + sc2->_popularidad + 1;

    //actualizo huboConstruccion
    if(sc2->_huboConstruccion){
        _huboConstruccion = true;
    }


}

//-----------------------------------------------------------------------------------------

set<int> simCity::riosHorizontales() const {

    set<int> hsFinal = _mapa.horizontales();

    for(auto it = _unidos.begin(); it != _unidos.end(); it++){
        unionHorizontales(*(*it), hsFinal);
    }
    return hsFinal;
}

void simCity::unionHorizontales(const simCity sc, set<int>& hsFinal) const {

    set<int> hs = sc._mapa.horizontales();

    for(auto it = hs.begin(); it != hs.end(); it++) {
        hsFinal.insert(*it);
    }

    for(auto i = sc._unidos.begin(); i != sc._unidos.end(); i++){
        unionHorizontales(*(*i), hsFinal);
    }

}

set<int> simCity::riosVerticales() const {
    set<int> vsFinal = _mapa.verticales();

    for(auto it = _unidos.begin(); it != _unidos.end(); it++){
        unionVerticales(*(*it), vsFinal);
    }

    return vsFinal;
}

void simCity::unionVerticales(const simCity sc, set<int>& vsFinal) const {

    set<int> vs = sc._mapa.verticales();

    for(auto it = vs.begin(); it != vs.end(); it++) {
        vsFinal.insert(*it);
    }

    for(auto i = sc._unidos.begin(); i != sc._unidos.end(); i++){
        unionVerticales(*(*i), vsFinal);
    }

}

set<Casilla> simCity::casas() const {

    map<Casilla, Nat> casasOriginales = _casas;
    map<Casilla, Nat> comerciosOriginales = _comercios;

    this->actualizarPorManhattan(casasOriginales, comerciosOriginales);

    // Actualizo las casas y comercios.
    for(auto i = _unidos.begin(); i != _unidos.end(); i++){
        agregarConstruccionesUnidas(*(*i), casasOriginales, comerciosOriginales);
    }


    // Me quedo solamente con las keys, es decir con las casillas
    set<Casilla> casasFinal;
    for(auto it = casasOriginales.begin(); it != casasOriginales.end(); it++){
        casasFinal.insert(it->first);
    }

    return casasFinal;
}

//-----------------------------------------------------------------------------------------

set<Casilla> simCity::comercios() const {
    map<Casilla, Nat> comerciosOriginales = _comercios;
    map<Casilla, Nat> casasOriginales = _casas;

    this->actualizarPorManhattan(casasOriginales, comerciosOriginales);

    for(auto i = _unidos.begin(); i != _unidos.end(); i++){
        agregarConstruccionesUnidas(*(*i), casasOriginales, comerciosOriginales);
    }

    set<Casilla> comerciosFinal;
    for(auto it = comerciosOriginales.begin(); it != comerciosOriginales.end(); it++){
        comerciosFinal.insert(it->first);
    }

    return comerciosFinal;
}



void simCity::agregarConstruccionesUnidas(const simCity sc, map<Casilla, Nat>& casas, map<Casilla, Nat>& comercios) const {


    map<Casilla, Nat> casasSC = sc._casas;
    map<Casilla, Nat> comerciosSC = sc._comercios;
    this->actualizarPorManhattan(casasSC, comerciosSC);

    for(auto it = casasSC.begin(); it != casasSC.end(); it++){

        if(casas.count(it->first) == 0 && comercios.count(it->first) == 0){
            casas[it->first] = it->second;
        }else{
            if(comercios.count(it->first) != 0){
                //Quito la casa del dicc comercios.
                comercios.erase(it->first);
                casas[it->first] = it->second;
            }else{
                //Si la casa del unido es de mayor nivel que la casa original sobreescribo.
                if(it->second > casas[it->first]){
                    casas[it->first] = it->second;
                }
            }

        }
    }

    for(auto it = comerciosSC.begin(); it != comerciosSC.end(); it++){

        if(casas.count(it->first) == 0 && comercios.count(it->first) == 0){
            comercios[it->first] = it->second;
        }else{
            if(comercios.count(it->first) != 0){
                //Si la casa del unido es de mayor nivel que la casa original lo sobreescribe
                if(it->second > comercios[it->first]){
                    comercios[it->first] = it->second;
                }
            }
        }
    }

    this->actualizarPorManhattan(casas, comercios);

    //-----------------------------------------------------

    //Llamo a la recursion
    if(sc._unidos.size() != 0){
        for(auto i = sc._unidos.begin(); i != sc._unidos.end(); i++){
            agregarConstruccionesUnidas(*(*i), casas, comercios);
        }
    }
}


void simCity::actualizarPorManhattan(map<Casilla, Nat> casas, map<Casilla, Nat> &comercios) const{
    for(auto it = comercios.begin(); it != comercios.end(); it++){
        Nat maxNivelCercano = 0;
        for(auto it2 = casas.begin(); it2 != casas.end(); it2++){
            if (it2->second > it->second &&
                ((abs(it->first.first - it2->first.first)+abs(it->first.second - it2->first.second)) <= 3) &&
                it2->second > maxNivelCercano){
                maxNivelCercano = it2->second;
            }
        }
        if(maxNivelCercano > 0){
            it->second = maxNivelCercano;
        }
    }
}

Nat simCity::nivel(Casilla c) const {

    //Creo los dicc de las casas y los comercios
    map<Casilla, Nat> casasSC = _casas;
    map<Casilla, Nat> comerciosSC = _comercios;

    //Actualizo los comercios originales
    this->actualizarPorManhattan(casasSC, comerciosSC);

    //Agrego las casas y comercios de las uniones
    for(auto i = _unidos.begin(); i != _unidos.end(); i++){
        agregarConstruccionesUnidas(*(*i), casasSC, comerciosSC);
    }

    //Recorro los dicc buscando si existe una construccion en la casilla
    for(auto it = casasSC.begin(); it != casasSC.end(); it++){
        if(it->first == c){
            return it->second;
        }
    }

    for(auto it = comerciosSC.begin(); it != comerciosSC.end(); it++){
        if(it->first == c){
            return it->second;
        }
    }
    return 0;

}

//-----------------------------------------------------------------------------------------

bool simCity::huboConstruccion() const {
    return _huboConstruccion;
}

//-----------------------------------------------------------------------------------------

Nat simCity::popularidad() const {
    return _popularidad;
}

//-----------------------------------------------------------------------------------------

Nat simCity::antiguedad() const {
    return _turno;
}

//-----------------------------------------------------------------------------------------