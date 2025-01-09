#include "Funciones.h"
#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "Servicio.h"
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;
    vector<Servicio> servicios;

    int opcion;
    do {
        menu();
        cin >> opcion;
        switch (opcion) {
        case 1: gestionarPacientes(pacientes); break;
        case 2: gestionarMedicos(medicos); break;
        case 3: gestionarCitas(citas, pacientes, medicos); break;
        case 4: gestionarServicios(servicios, pacientes, medicos); break;
        case 5: exportarDatosJSON(pacientes, medicos, citas, servicios, "hospital.json"); break;
        case 6: importarDatosJSON(pacientes, medicos, citas, servicios, "hospital.json"); break;
        case 7: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Error, opcion invalida.\n";
        }
    } while (opcion != 7);

    return 0;
}