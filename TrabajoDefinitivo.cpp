// TrabajoDefinitivo.cpp: define el punto de entrada de la aplicación.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
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

    // acciones
    void altaPaciente(string historial) {
        historialClinico.push_back(historial);
        cout << "Paciente " << nombre << " dado de alta." << endl;
    }

    void bajaPaciente() {
        cout << "Paciente " << nombre << " con ID " << id << " dado de baja." << endl;
    }

    void modificarDatos(string nuevoNombre) {
        nombre = nuevoNombre;
        cout << "Datos del paciente actualizados a: " << nombre << endl;
    }

    void agregarHistorial(string registro) {
        historialClinico.push_back(registro);
        cout << "Registro agregado al historial de " << nombre << "." << endl;
    }

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

    // acciones
    void altaMedico() {
        cout << "Médico " << nombre << " registrado con ID " << id << "." << endl;
    }

    void bajaMedico() {
        cout << "Médico " << nombre << " eliminado del sistema." << endl;
    }

    void asignarEspecialidad(string nuevaEspecialidad) {
        especialidad = nuevaEspecialidad;
        cout << "Especialidad de " << nombre << " actualizada a " << especialidad << "." << endl;
    }

    void listarMedicos() const {
        cout << "Médico: " << nombre << ", Especialidad: " << especialidad
            << ", Disponibilidad: " << (disponibilidad ? "Disponible" : "No disponible") << endl;
    }
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
    void asignarCita() {
        cout << "Cita asignada entre " << paciente->nombre << " y " << medico->nombre
            << " el " << fecha << " con urgencia nivel " << urgencia << "." << endl;
    }

    void cancelarCita() {
        cout << "Cita cancelada entre " << paciente->nombre << " y " << medico->nombre << "." << endl;
    }

    void modificarCita(string nuevaFecha, int nuevaUrgencia) {
        fecha = nuevaFecha;
        urgencia = nuevaUrgencia;
        cout << "Cita modificada para el " << fecha << " con urgencia nivel " << urgencia << "." << endl;
    }

    static void ordenarPorFecha(vector<Cita>& citas) {
        sort(citas.begin(), citas.end(), [](Cita& a, Cita& b) {
            return a.fecha < b.fecha;
            });
    }

    static void ordenarPorUrgencia(vector<Cita>& citas) {
        sort(citas.begin(), citas.end(), [](Cita& a, Cita& b) {
            return a.urgencia > b.urgencia;
            });
    }
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
    void listarServicios() const {
        cout << "Servicio: " << servicio << ", Costo: $" << costo
            << ", Descripción: " << descripcion << endl;
    }
};

// clase archivos!


int main() {}