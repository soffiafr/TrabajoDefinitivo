#ifndef MEDICO_H
#define MEDICO_H

#include <string>
using namespace std;

class Medico {
public:
    string nombre;
    string especialidad;
    int id;
    bool disponibilidad;

    Medico(string nombre, int id, string especialidad, bool disponibilidad);
    void asignarEspecialidad(string nuevaEspecialidad);
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
    void leerMedico() const;
};

#endif