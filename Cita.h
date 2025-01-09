#ifndef CITA_H
#define CITA_H

#include "Paciente.h"
#include "Medico.h"
#include <string>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Cita {
public:
    int id;
    Paciente* paciente;
    Medico* medico;
    string fecha;
    int urgencia;

    Cita(int id, Paciente* paciente, Medico* medico, string fecha, int urgencia);
    json toJSON() const;
    static Cita fromJSON(const nlohmann::json& j, std::vector<Paciente>& pacientes, std::vector<Medico>& medicos);
    void modificarCita(string nuevaFecha, int nuevaUrgencia);
    void leerCita() const;
    static void ordenarPorFecha(vector<Cita>& citas);
    static void ordenarPorUrgencia(vector<Cita>& citas);
};

#endif
