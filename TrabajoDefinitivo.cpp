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
        case 5: generarReportes(citas, pacientes, medicos); break;
        case 6: exportarDatosJSON(pacientes, medicos, citas, servicios, "hospital.json"); break;
        case 7: importarDatosJSON(pacientes, medicos, citas, servicios); break;
        case 8: {
            string nombreArchivoOriginal = "hospital.json";
            realizarBackup(nombreArchivoOriginal); break;
        }
        case 9: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Error, opcion invalida.\n";
        }
    } while (opcion != 9);

    return 0;
}