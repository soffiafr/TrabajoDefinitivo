#include "Paciente.h"
#include <iostream>

Paciente::Paciente(string nombre, int id, string fechaIngreso)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso) {
}

json Paciente::toJSON() const {
    return { {"nombre", nombre}, {"id", id}, {"fechaIngreso", fechaIngreso}, {"historialClinico", historialClinico} };
}

Paciente Paciente::fromJSON(const json& j) {
    Paciente p(j["nombre"], j["id"], j["fechaIngreso"]);
    p.historialClinico = j["historialClinico"].get<vector<string>>();
    return p;
}

void Paciente::modificarDatos(string nuevoNombre, string nuevaFechaIngreso) {
    this->nombre = nuevoNombre;
    this->fechaIngreso = nuevaFechaIngreso;
}

void Paciente::agregarHistorial(string registro) {
    historialClinico.push_back(registro);
}

void Paciente::leerPaciente() const {
    cout << "Paciente: " << nombre << ", ID: " << id << ", fecha de ingreso: " << fechaIngreso << endl;
    cout << "Historial clinico: ";
    for (const auto& h : historialClinico) {
        cout << h << ", ";
    }
    cout << endl;
}