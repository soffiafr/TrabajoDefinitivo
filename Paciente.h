#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>
using namespace std;

class Paciente {
public:
    string nombre;
    int id;
    string fechaIngreso;
    vector<string> historialClinico;

    Paciente(string nombre, int id, string fechaIngreso);
    void modificarDatos(string nuevoNombre, string nuevaFechaIngreso);
    void agregarHistorial(string registro);
    void leerPaciente() const;
};

#endif

