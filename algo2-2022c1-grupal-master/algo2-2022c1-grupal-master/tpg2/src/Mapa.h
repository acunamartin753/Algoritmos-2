#ifndef TP_SIMCITY_MAPA_H
#define TP_SIMCITY_MAPA_H

#include "Tipos.h"
#include <string>
#include <utility>
#include <set>


class Mapa{
public:
    Mapa(const set<int>& hs, const set<int>& vs);

    Mapa& operator=(const Mapa aCopiar);

    set<int> horizontales() const;

    set<int> verticales() const;

private:
    set<int> _horizontales;
    set<int> _verticales;

};


#endif //TP_SIMCITY_MAPA_H
