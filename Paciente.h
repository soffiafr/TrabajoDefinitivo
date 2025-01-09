#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Paciente {
public:
    string nombre;
    int id;
    string fechaIngreso;
    vector<string> historialClinico;

    Paciente(string nombre, int id, string fechaIngreso);
    json toJSON() const;
    static Paciente fromJSON(const json& j);
    void modificarDatos(string nuevoNombre, string nuevaFechaIngreso);
    void agregarHistorial(string registro);
    void leerPaciente() const;
};

#endif

