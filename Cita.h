#ifndef CITA_H
#define CITA_H

#include "Paciente.h"
#include "Medico.h"
#include <string>
#include <vector>
using namespace std;

class Cita {
public:
    int id;
    Paciente* paciente;
    Medico* medico;
    string fecha;
    int urgencia;

    Cita(int id, Paciente* paciente, Medico* medico, string fecha, int urgencia);
    void modificarCita(string nuevaFecha, int nuevaUrgencia);
    void leerCita() const;
    static void ordenarPorFecha(vector<Cita>& citas);
    static void ordenarPorUrgencia(vector<Cita>& citas);
};

#endif
