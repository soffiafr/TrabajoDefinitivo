#include "Paciente.h"
#include <iostream>

Paciente::Paciente(string nombre, int id, string fechaIngreso, bool enfermedadCronica)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso), enfermedadCronica(enfermedadCronica){
}

json Paciente::toJSON() const {
    return { {"nombre", nombre}, {"id", id}, {"fechaIngreso", fechaIngreso}, {"historialClinico", historialClinico}, {"enfermedadCronica", enfermedadCronica} };
}

Paciente Paciente::fromJSON(const json& j) {
    Paciente p(j["nombre"], j["id"], j["fechaIngreso"], j["enfermedadCronica"]);
    p.historialClinico = j["historialClinico"].get<vector<string>>();
    return p;
}

void Paciente::modificarDatos(string nuevoNombre, string nuevaFechaIngreso, bool nuevaEnfermedadCronica) {
    this->nombre = nuevoNombre;
    this->fechaIngreso = nuevaFechaIngreso;
    this->enfermedadCronica = nuevaEnfermedadCronica;
}

void Paciente::agregarHistorial(string registro) {
    historialClinico.push_back(registro);
}

void Paciente::leerPaciente() const {
    cout << "Paciente: " << nombre;
    cout << ", ID: " << id;
    cout << ", fecha de ingreso: " << fechaIngreso;
    cout << ", enfermedad cronica: " << (enfermedadCronica ? "Si" : "No") << endl;
    cout << "Historial clinico: ";
    if (historialClinico.empty()) {
        cout << "No hay registros." << endl;
    }
    else {
        for (size_t i = 0; i < historialClinico.size(); ++i) {
            cout << historialClinico[i];
            if (i != historialClinico.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    cout << endl;
}