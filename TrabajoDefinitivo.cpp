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
    }

    void bajaPaciente() {
        nombre = "Paciente eliminado";
    }

    void modificarDatos(string nuevoNombre) {
        this->nombre = nuevoNombre;
    }

    void agregarHistorial(string registro) {
        this->historialClinico.push_back(registro);
    }

    void leerPaciente() {
        cout << "Paciente: " << nombre << ", ID: " << id << ", fecha de ingreso: " << fechaIngreso << endl;
        cout << "Historial clinico: ";
        for (const auto& h : historialClinico) {
            cout << h << ", ";
        }
        cout << endl;
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
    void altaMedico(vector<Medico>& medicos) {
        medicos.push_back(*this);
        cout << "Medico " << this->nombre << " dado de alta con ID " << this->id << "." << endl;
    }

    void bajaMedico() {
        nombre = "Medico eliminado";
    }

    void asignarEspecialidad(string nuevaEspecialidad) {
        especialidad = nuevaEspecialidad;
    }

    void listarMedicos() const {
        cout << "Medico: " << nombre << ", especialidad: " << especialidad
            << ", disponibilidad: " << (disponibilidad ? "Disponible" : "No disponible") << endl;
    }

    void leerMedico() {
        cout << "Medico: " << nombre << ", ID: " << id << ", especialidad: " << especialidad << endl;
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
    }

    void leerCita() {
        cout << "Cita ID: " << id << " entre " << paciente->nombre << " y " << medico->nombre
            << ", fecha: " << fecha << ", urgencia: " << urgencia << endl;
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
        cout << "Servicio: " << servicio << ", costo: $" << costo
            << ", descripcion: " << descripcion << endl;
    }

    void leerServicio() const {
        cout << "Servicio: " << servicio << ", costo: " << costo << ", descripción: " << descripcion << endl;
    }
};


int main() {

    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;
    vector<Servicio> servicios;

        // objetos
        Paciente p1("Lorenzo Perez", 1, "15/03/2017");
        Medico m1("Dra. Sanchez", 1234, "Cardiologia", true);
        Servicio s1("Rayos X", 150.75, "Examen radiologico.");
        pacientes.push_back(p1);
        medicos.push_back(m1);
        servicios.push_back(s1);

        // citas
        Cita c1(101, &pacientes[0], &medicos[0], "6/04/2017", 2);
        Cita c2(102, &pacientes[0], &medicos[0], "3/04/2017", 1);
        Cita c3(103, &pacientes[0], &medicos[0], "1/05/2017", 3);
        citas.push_back(c1);
        citas.push_back(c2);
        citas.push_back(c3);

        // leer las citas
        cout << "Citas:" << endl;
        for (auto& cita : citas) {
            cita.leerCita();
        }

        // ordenar las citas por fecha
        Cita::ordenarPorFecha(citas);
        cout << "\nCitas ordenadas por fecha:" << endl;
        for (auto& cita : citas) {
            cita.leerCita();
        }

        // ordenar las citas por urgencia
        Cita::ordenarPorUrgencia(citas);
        cout << "\nCitas ordenadas por urgencia:" << endl;
        for (auto& cita : citas) {
            cita.leerCita();
        }

        return 0;
}