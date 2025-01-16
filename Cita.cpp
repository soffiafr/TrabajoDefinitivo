#include "Cita.h"
#include <iostream>
#include <algorithm>

Cita::Cita(int id, Paciente* paciente, Medico* medico, string fecha, int urgencia)
    : id(id), paciente(paciente), medico(medico), fecha(fecha), urgencia(urgencia) {
}

Cita Cita::fromJSON(const nlohmann::json& j, std::vector<Paciente>& pacientes, std::vector<Medico>& medicos) {
    int id = j["id"];
    std::string fecha = j["fecha"];
    int urgencia = j["urgencia"];
    int pacienteId = j["paciente_id"];
    int medicoId = j["medico_id"];

    Paciente* paciente = nullptr;
    for (auto& p : pacientes) {
        if (p.id == pacienteId) {
            paciente = &p;
            break;
        }
    }

    Medico* medico = nullptr;
    for (auto& m : medicos) {
        if (m.id == medicoId) {
            medico = &m;
            break;
        }
    }

    if (paciente && medico) {
        return Cita(id, paciente, medico, fecha, urgencia);
    }
    else {
        throw std::runtime_error("Paciente o médico no encontrado.");
    }
}


nlohmann::json Cita::toJSON() const {
    nlohmann::json j;
    j["id"] = id;
    j["fecha"] = fecha;
    j["urgencia"] = urgencia;
    j["paciente_id"] = paciente->id;
    j["medico_id"] = medico->id; 
    return j;
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

bool Cita::validarDisponibilidadMedico(const Medico* medico, const string& fecha, const vector<Cita>& citas) {
    for (const auto& cita : citas) {
        if (cita.medico == medico && cita.fecha == fecha) {
            cout << "El médico " << medico->nombre << " ya tiene una cita programada para la fecha " << fecha << ".\n";
            return false;
        }
    }
    return true;
}