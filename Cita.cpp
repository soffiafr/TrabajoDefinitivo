#include "Cita.h"
#include <iostream>
#include <algorithm>

Cita::Cita(int id, Paciente* paciente, Medico* medico, string fecha, int urgencia)
    : id(id), paciente(paciente), medico(medico), fecha(fecha), urgencia(urgencia) {
}

void Cita::modificarCita(string nuevaFecha, int nuevaUrgencia) {
    fecha = nuevaFecha;
    urgencia = nuevaUrgencia;
}

void Cita::leerCita() const {
    cout << "Cita ID: " << id << " entre " << paciente->nombre << " y " << medico->nombre
        << ", fecha: " << fecha << ", urgencia: " << urgencia << endl;
}

void Cita::ordenarPorFecha(vector<Cita>& citas) {
    sort(citas.begin(), citas.end(), [](Cita& a, Cita& b) { return a.fecha < b.fecha; });
}

void Cita::ordenarPorUrgencia(vector<Cita>& citas) {
    sort(citas.begin(), citas.end(), [](Cita& a, Cita& b) { return a.urgencia > b.urgencia; });
}