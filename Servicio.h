#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Servicio {
public:
    string servicio;
    double costo;
    string descripcion;

    Servicio(string servicio, double costo, string descripcion);
    json toJSON() const;
    static Servicio fromJSON(const json& j);
    void leerServicio() const;
};

#endif
