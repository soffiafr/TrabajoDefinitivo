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
        this->historialClinico.push_back(historial);
        cout << "Paciente, " << this->nombre << ", dado de alta." << endl;
    }

    void bajaPaciente() {
        cout << "Paciente, " << this->nombre << ", con ID " << this->id << ", dado de baja." << endl;
    }

    void modificarDatos(string nuevoNombre) {
        this->nombre = nuevoNombre;
        cout << "Datos del paciente actualizados a: " << this->nombre << endl;
    }

    void agregarHistorial(string registro) {
        this->historialClinico.push_back(registro);
        cout << "Registro agregado al historial de " << this->nombre << "." << endl;
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
        cout << "Medico, " << this->nombre << ", registrado con ID " << this->id << "." << endl;
    }

    void bajaMedico() {
        cout << "Medico, " << this->nombre << ", eliminado del sistema." << endl;
    }

    void asignarEspecialidad(string nuevaEspecialidad) {
        especialidad = nuevaEspecialidad;
        cout << "Especialidad de " << this->nombre << " actualizada a " << this->especialidad << "." << endl;
    }

    void listarMedicos() const {
        cout << "Medico: " << this->nombre << ", Especialidad: " << this->especialidad
            << ", Disponibilidad: " << (this->disponibilidad ? "Disponible" : "No disponible") << endl;
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
        cout << "Cita asignada entre " << this->paciente->nombre << " y " << this->medico->nombre
            << " el " << this->fecha << " con urgencia nivel " << this->urgencia << "." << endl;
    }

    void cancelarCita() {
        cout << "Cita cancelada entre " << this->paciente->nombre << " y " << this->medico->nombre << "." << endl;
    }

    void modificarCita(string nuevaFecha, int nuevaUrgencia) {
        this->fecha = nuevaFecha;
        this->urgencia = nuevaUrgencia;
        cout << "Cita modificada para el " << this->fecha << " con urgencia nivel " << urgencia << "." << endl;
    }

    static void ordenarPorFecha(vector<Cita>& citas) {
        // algoritmo (sort) para ordenar elementos en un rango definido
        sort(citas.begin(), citas.end(), [](Cita& a, Cita& b) {
            return a.fecha < b.fecha;
            });
    }

    static void ordenarPorUrgencia(vector<Cita>& citas) {
        // algoritmo (sort) para ordenar elementos en un rango definido
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
        cout << "Servicio: " << this->servicio << ", costo: $" << this->costo
            << ", descripcion: " << this->descripcion << endl;
    }
};


int main() {

        Paciente p1("Lorenzo Perez", 1, "15/03/2017");
        Medico m1("Dra. Sanchez", 1234, "Cardiologia", true);

        p1.altaPaciente("Sin antecedentes.");
        m1.altaMedico();

        Cita c1(101, &p1, &m1, "6/04/2017", 2);
        c1.asignarCita();

        Servicio s1("Rayos X", 150.75, "Examen radiologico.");
        s1.listarServicios();

        return 0;
}