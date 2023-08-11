#include "aed2_Servidor.h"


aed2_Servidor::aed2_Servidor(){}


void aed2_Servidor::nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales) {
    servidor.nuevaPartida(j, horizontales, verticales);
}

void aed2_Servidor::agregarCasa(Jugador j, Casilla c) {
    servidor.agregarCasa(j, c);
}

void aed2_Servidor::agregarComercio(Jugador j, Casilla c) {
    servidor.agregarComercio(j, c);
}

void aed2_Servidor::avanzarTurno(Jugador j) {
    servidor.avanzarTurno(j);
}

void aed2_Servidor::unir(Jugador j1, Jugador j2) {
    servidor.unir(j1, j2);
}

set<int> aed2_Servidor::riosHorizontales(Jugador j) const {
    return servidor.riosHorizontales(j);
}

set<int> aed2_Servidor::riosVerticales(Jugador j) const {
    return servidor.riosVerticales(j);
}

set<Casilla> aed2_Servidor::casas(Jugador j) const {
    return servidor.casas(j);
}

set<Casilla> aed2_Servidor::comercios(Jugador j) const {
    return servidor.comercios(j);
}

Nat aed2_Servidor::nivel(Jugador j, Casilla c) const {
    return servidor.nivel(j, c);
}

bool aed2_Servidor::huboConstruccion(Jugador j) const {
    return servidor.huboConstruccion(j);
}

Nat aed2_Servidor::popularidad(Jugador j) const {
    return servidor.popularidad(j);
}

Nat aed2_Servidor::antiguedad(Jugador j) const {
    return servidor.antiguedad(j);
}
