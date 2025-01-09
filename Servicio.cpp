#include "Servicio.h"
#include <iostream>

Servicio::Servicio(string servicio, double costo, string descripcion)
    : servicio(servicio), costo(costo), descripcion(descripcion) {
}

json Servicio::toJSON() const {
    return { {"servicio", servicio}, {"costo", costo}, {"descripcion", descripcion} };
}

Servicio Servicio::fromJSON(const json& j) {
    return Servicio(j["servicio"], j["costo"], j["descripcion"]);
}

void Servicio::leerServicio() const {
    cout << "Servicio: " << servicio << ", costo: " << costo << ", descripción: " << descripcion << endl;
}