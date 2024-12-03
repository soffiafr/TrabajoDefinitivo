// TrabajoDefinitivo.cpp: define el punto de entrada de la aplicación.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;

// paciente
class Paciente {
public:
    string nombre;
    int id;
    string fechaIngreso;
    vector <string> historialClinico;

    Paciente(string nombre, int id, string fechaIngreso)
        : nombre(nombre), id(id), fechaIngreso(fechaIngreso) {
    }

    //  información del paciente
    void informacionPaciente() {
        cout << "Paciente: " << nombre << endl;
        cout << "ID: " << id << endl;
        cout << "Fecha de Ingreso: " << fechaIngreso << endl;
    }

    // acciones
};

// medico
class Medico {
public:
    string nombre;
    string especialidad;
    int id;
    bool disponibilidad;

    Medico(string nombre, int id, string especialidad, bool disponibilidad)
        : nombre(nombre), id(id), especialidad(especialidad), disponibilidad(disponibilidad) {
    }

    // información del medico
    void informacionMedico() {
        cout << "Medico: " << nombre << endl;
        cout << "ID: " << id << endl;
        cout << "Especialidad: " << especialidad << endl;
        cout << "Disponibilidad: " << (disponibilidad ? "Si" : "No") << endl;
    }

    // acciones
};

// cita
class Cita {
public:
    int id;
    Paciente* paciente;
    Medico* medico;
    string fecha;
    int urgencia;

    Cita(int id, Paciente* paciente, Medico* medico, string fecha, int urgencia)
        : id(id), paciente(paciente), medico(medico), fecha(fecha), urgencia(urgencia) {
    }

    // acciones
};

// servicio
class Servicio {
public:
    string servicio;
    double costo;
    string descripcion;

    Servicio(string servicio, double costo, string descripcion)
        : servicio(servicio), costo(costo), descripcion(descripcion) {
    }

    // acciones
};

// clase archivos!


int main() {

    // ejemplo para compilar

    Paciente p1("Raquel Gonzalez", 12345, "15-3-2008");
    Medico m1("Dra. Hugo Sanchez", 1001, "Pediatria", true);

    cout << "Datos del paciente:" << endl;
    p1.informacionPaciente();

    cout << endl;

    cout << "Datos del medico:" << endl;
    m1.informacionMedico();



    return 0;
}