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
    void modificarDatos(string nuevoNombre, string nuevaFechaIngreso) {
        this->nombre = nuevoNombre;
        this->fechaIngreso = nuevaFechaIngreso;
    }

    void agregarHistorial(string registro) {
        historialClinico.push_back(registro);
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
    void asignarEspecialidad(string nuevaEspecialidad) {
        especialidad = nuevaEspecialidad;
    }

    void cambiarDisponibilidad(bool nuevaDisponibilidad) {
        disponibilidad = nuevaDisponibilidad;
    }

    const void leerMedico() {
        cout << "Medico: " << nombre << ", ID: " << id << ", especialidad: " << especialidad << ", disponibilidad: " << (disponibilidad ? "Si" : "No") << endl;
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
    void modificarCita(string nuevaFecha, int nuevaUrgencia) {
        fecha = nuevaFecha;
        urgencia = nuevaUrgencia;
    }

    const void leerCita() {
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
    void leerServicio() const {
        cout << "Servicio: " << servicio << ", costo: " << costo << ", descripción: " << descripcion << endl;
    }
};

// --- funciones principales de las clases ---

// mostrar las opciones principales del programa
void menu () {
    cout << "\nGestion del hospital\n";
    cout << "1. Gestionar pacientes\n";
    cout << "2. Gestionar medicos\n";
    cout << "3. Gestionar citas\n";
    cout << "4. Gestionar servicios\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}

// crear, leer, actualizar, eliminar y agregar historial a los pacientes
void gestionarPacientes(vector<Paciente>& pacientes) {
    int opcion, id;
    string nombre, fechaIngreso, registro;

    do {
        cout << "\nGestion de pacientes\n";
        cout << "1. Crear paciente\n2. Leer pacientes\n3. Actualizar paciente\n4. Eliminar aciente\n5. Agregar historial del paciente\n0. Volver\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nombre: "; cin >> nombre;
            cout << "ID: "; cin >> id;
            cout << "Fecha de ingreso: "; cin >> fechaIngreso;
            pacientes.push_back(Paciente(nombre, id, fechaIngreso));
            cout << "Paciente creado correctamente.\n";

            break;

        case 2:
            for (auto& p : pacientes) p.leerPaciente();

            break;

        case 3:
            cout << "Modificar datos del paciente: "; cin >> id;
            for (auto& p : pacientes) {
                if (p.id == id) {
                    cout << "Nuevo nombre: "; cin >> nombre;
                    cout << "Nueva fecha de ingreso: "; cin >> fechaIngreso;
                    p.modificarDatos(nombre, fechaIngreso);
                    cout << "Datos actualizados correctamente.\n";
                }
            }
            break;

        case 4:
            cout << "Eliminar paciente: "; cin >> id;
            pacientes.erase(remove_if(pacientes.begin(), pacientes.end(),
                [id](const Paciente& p) { return p.id == id; }), pacientes.end());
            cout << "Paciente eliminado.\n";

            break;

        case 5:
            cout << "ID del paciente: "; cin >> id;
            for (auto& p : pacientes) {
                if (p.id == id) {
                    cout << "Agregar historial: "; cin >> registro;
                    p.agregarHistorial(registro);
                }
            }
            break;
        }
    } while (opcion != 0);
}


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
        case 2: cout << "Gestion de medicos aun no implementada.\n"; break;
        case 3: cout << "Gestion de citas aun no implementada.\n"; break;
        case 4: cout << "Gestion de servicios aun no implementada.\n"; break;
        case 5: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Error, opcion invalida.\n";
        }
    } while (opcion != 5);
    
    return 0;
}