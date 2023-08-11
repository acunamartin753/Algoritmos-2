#include "Servidor.h"


//-----------------------------------------------------------------------------------------

Servidor::Servidor(){
    string_map<registro>* nuevoSimcities  = new string_map<registro>();
    simCities = *nuevoSimcities;

    delete nuevoSimcities;
}

//-----------------------------------------------------------------------------------------

Servidor::registro::registro() : simcity(Mapa({},{})),modif(true){}

Servidor::registro::registro(const simCity& _simcity) : simcity(_simcity),modif(true){}

Servidor::registro &Servidor::registro::operator=(const Servidor::registro aCopiar) {
    this->simcity = aCopiar.simcity;
    this->modif = aCopiar.modif;

    return *this;
}

//-----------------------------------------------------------------------------------------

void Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales) {

    Mapa* mapa_sim = new Mapa(horizontales, verticales);
    simCity* nuevoSim = new simCity(*mapa_sim);
    registro* nuevoRegistro = new registro(*nuevoSim);


    simCities.insert(make_pair(j, *nuevoRegistro));
    delete mapa_sim;
    delete nuevoSim;
    delete nuevoRegistro;
}

//-----------------------------------------------------------------------------------------

void Servidor::agregarCasa(Jugador j, Casilla c) {
    simCity* sc = &(simCities.at(j).simcity);
    sc->agregarCasa(c);
}

//-----------------------------------------------------------------------------------------

void Servidor::agregarComercio(Jugador j, Casilla c) {
    simCity* sc = &(simCities.at(j).simcity);
    sc->agregarComercio(c);
}

//-----------------------------------------------------------------------------------------


void Servidor::avanzarTurno(Jugador j) {

    simCity* sc = &(simCities.at(j).simcity);
    sc->avanzarTurno();

    /*

    sc.turno = sc.turno + 1;
    sc.huboConstruccion = false;

    //Creo los dicc a los que les voy a sumar 1 y reemplazarlos en el original
    map<Casilla, Nat> casasSC = sc.casas;
    map<Casilla, Nat> comerciosSC = sc.comercios;


    //Actualizo por los comercios con distancia Manhattan menor a 3
    this->actualizarPorManhattan(casasSC, comerciosSC);

    //Creo los nuevos map de casas y comercios.
    for(auto i = sc.unidos.begin(); i != sc.unidos.end(); i++){
        agregarConstruccionesUnidas(*(*i), casasSC, comerciosSC);
    }

    //Actualizo sumando 1 Nivel
    this->actualizarSumandoTurno(casasSC, comerciosSC);

    sc.casas = casasSC;
    sc.comercios = comerciosSC;

    registro* registroAct = new registro();
    registroAct->simcity = sc;
    simCities.insert(make_pair(j, *registroAct));
    delete registroAct;
    */
}

//-----------------------------------------------------------------------------------------

void Servidor::unir(Jugador j1, Jugador j2) {
    simCity* sc1 = &(simCities.at(j1).simcity);
    simCity* sc2 = &(simCities.at(j2).simcity);
    sc1->unir(sc2);
    registro* r1 = &(simCities.at(j2));
    r1->modif = false;
}

//-----------------------------------------------------------------------------------------

set<int> Servidor::riosHorizontales(Jugador j) const {

    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->riosHorizontales());

}

//-----------------------------------------------------------------------------------------

set<int> Servidor::riosVerticales(Jugador j) const {

    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->riosVerticales());
}

//-----------------------------------------------------------------------------------------

set<Casilla> Servidor::casas(Jugador j) const{

    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->casas());
}

//-----------------------------------------------------------------------------------------

set<Casilla> Servidor::comercios(Jugador j) const {

    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->comercios());
}

//-----------------------------------------------------------------------------------------

Nat Servidor::nivel(Jugador j, Casilla c) const {

    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->nivel(c));
}

//-----------------------------------------------------------------------------------------

bool Servidor::huboConstruccion(Jugador j) const {

    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->huboConstruccion());
}

//-----------------------------------------------------------------------------------------

Nat Servidor::popularidad(Jugador j) const {
    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->popularidad());
}

//-----------------------------------------------------------------------------------------

Nat Servidor::antiguedad(Jugador j) const {
    const simCity* sc = &(simCities.at(j).simcity);
    return (sc->antiguedad());
}

//-----------------------------------------------------------------------------------------








