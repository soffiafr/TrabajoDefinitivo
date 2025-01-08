#include "Medico.h"
#include <iostream>

Medico::Medico(string nombre, int id, string especialidad, bool disponibilidad)
    : nombre(nombre), id(id), especialidad(especialidad), disponibilidad(disponibilidad) {
}

void Medico::asignarEspecialidad(string nuevaEspecialidad) {
    especialidad = nuevaEspecialidad;
}

void Medico::cambiarDisponibilidad(bool nuevaDisponibilidad) {
    disponibilidad = nuevaDisponibilidad;
}

void Medico::leerMedico() const {
    cout << "Medico: " << nombre << ", ID: " << id << ", especialidad: " << especialidad << ", disponibilidad: " << (disponibilidad ? "Si" : "No") << endl;
}