#ifndef MEDICO_H
#define MEDICO_H

#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Medico {
public:
    string nombre;
    string especialidad;
    int id;
    bool disponibilidad;

    Medico(string nombre, int id, string especialidad, bool disponibilidad);
    json toJSON() const;
    static Medico fromJSON(const json& j);
    void asignarEspecialidad(string nuevaEspecialidad);
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
    void leerMedico() const;
};

#endif