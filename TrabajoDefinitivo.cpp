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
        case 5: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Error, opcion invalida.\n";
        }
    } while (opcion != 5);

    return 0;
}

// Falta el guardado de datos.
// Modificar faltas de ortigrafía
// En modificar, que si no existe medico, cita o paciente que lo diga -> 'No existe medico/cita/paciente con es ID, introduzca un ID valido.'