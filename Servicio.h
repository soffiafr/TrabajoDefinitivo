#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>
using namespace std;

class Servicio {
public:
    string servicio;
    double costo;
    string descripcion;

    Servicio(string servicio, double costo, string descripcion);
    void leerServicio() const;
};

#endif
