#ifndef TP_SIMCITY_SIMCITY_H
#define TP_SIMCITY_SIMCITY_H

#include "Tipos.h"
#include "Mapa.h"
#include <string>
#include <utility>
#include <set>


class simCity{
public:
    simCity(const Mapa& _mapa);

    simCity& operator=(const simCity aCopiar);

    void agregarCasa(Casilla c);

    void agregarComercio(Casilla c);

    void avanzarTurno();

    void unir(simCity* sc2);

    set<int> riosHorizontales() const;

    set<int> riosVerticales() const;

    set<Casilla> casas() const;

    set<Casilla> comercios() const;

    Nat nivel(Casilla c) const;

    bool huboConstruccion() const;

    Nat popularidad() const;

    Nat antiguedad() const;

private:

    Mapa _mapa;
    Nat _turno;
    Nat _popularidad;
    map<Casilla, Nat> _casas;
    map<Casilla, Nat> _comercios;
    list<simCity*> _unidos;
    bool _huboConstruccion;


    void actualizarSumandoTurno(map<Casilla, Nat>& casas, map<Casilla, Nat>& comercios) const;

    void unionHorizontales(const simCity sc, set<int>& horizontales) const;

    void unionVerticales(const simCity sc, set<int>& verticales) const;

    void agregarConstruccionesUnidas(const simCity sc, map<Casilla, Nat>& casas, map<Casilla, Nat>& comercios) const;

    void actualizarPorManhattan(map<Casilla, Nat> casas, map<Casilla, Nat>& comercios) const;


};


#endif //TP_SIMCITY_SIMCITY_H
