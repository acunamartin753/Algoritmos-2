#ifndef TP_SIMCITY_SERVIDOR_H
#define TP_SIMCITY_SERVIDOR_H

#include "string_map.h"
#include "Mapa.h"
#include "SimCity.h"
#include "Tipos.h"
#include <string>
#include <utility>
#include <set>

using namespace std;

class Servidor {
public:

    Servidor();

    void nuevaPartida(Jugador j, set<int> horizontales, set<int> verticales);

    void agregarCasa(Jugador j, Casilla c);

    void agregarComercio(Jugador j, Casilla c);

    void avanzarTurno(Jugador j);

    void unir(Jugador j1, Jugador j2);

    set<int> riosHorizontales(Jugador j) const;

    set<int> riosVerticales(Jugador j) const;

    set<Casilla> casas(Jugador j) const;

    set<Casilla> comercios(Jugador j) const;

    Nat nivel(Jugador j, Casilla c) const;

    bool huboConstruccion(Jugador j) const;

    Nat popularidad(Jugador j) const;

    Nat antiguedad(Jugador j) const;

private:

    struct registro{

        registro();

        registro(const simCity& _simcity);

        registro& operator=(const registro aCopiar);

        simCity simcity;
        bool modif;
    };

    //Servidor se representa con diccTrie(Clave,significado)
    //donde significado es tupla(simcity: SimCity, modif : Bool)

    string_map<registro> simCities;

};





#endif //TP_SIMCITY_SERVIDOR_H
