#include "Servicio.h"
#include <iostream>

Servicio::Servicio(string servicio, double costo, string descripcion)
    : servicio(servicio), costo(costo), descripcion(descripcion) {
}

void Servicio::leerServicio() const {
    cout << "Servicio: " << servicio << ", costo: " << costo << ", descripción: " << descripcion << endl;
}