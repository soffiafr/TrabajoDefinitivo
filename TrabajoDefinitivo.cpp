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

// crear, leer, actualizar, eliminar y agregar a los medicos
void gestionarMedicos(vector<Medico>& medicos) {
    int opcion, id;
    string nombre, especialidad;
    bool disponibilidad;

    do {
        cout << "\nGestion de medicos\n";
        cout << "1. Crear medico\n2. Leer medicos\n3. Actualizar medico\n4. Eliminar medico\n5. Cambiar disponibilidad\n0. Volver\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nombre: "; cin >> nombre;
            cout << "ID: "; cin >> id;
            cout << "Especialidad: "; cin >> especialidad;
            cout << "Disponibilidad (1 para disponible, 0 para no disponible): "; cin >> disponibilidad;
            medicos.push_back(Medico(nombre, id, especialidad, disponibilidad));
            cout << "Medico creado correctamente.\n";

            break;

        case 2:
            for (auto& m : medicos) m.leerMedico();

            break;

        case 3:
            cout << "Modificar medico: "; cin >> id;
            for (auto& m : medicos) {
                if (m.id == id) {
                    cout << "Nuevo nombre: "; cin >> nombre;
                    cout << "Nueva especialidad: "; cin >> especialidad;
                    cout << "Nueva disponibilidad (1 para disponible, 0 para no disponible): "; cin >> disponibilidad;
                    m.nombre = nombre;
                    m.especialidad = especialidad;
                    m.disponibilidad = disponibilidad;
                    cout << "Datos actualizados correctamente.\n";
                }
            }
            break;

        case 4:
            cout << "Eliminar medico: "; cin >> id;
            medicos.erase(remove_if(medicos.begin(), medicos.end(),
                [id](const Medico& m) { return m.id == id; }), medicos.end());
            cout << "Medico eliminado.\n";

            break;

        case 5:
            cout << "Cambiar disponibilidad de medico: "; cin >> id;
            for (auto& m : medicos) {
                if (m.id == id) {
                    cout << "Nueva disponibilidad (1 para disponible, 0 para no disponible): "; cin >> disponibilidad;
                    m.cambiarDisponibilidad(disponibilidad);
                    cout << "Disponibilidad cambiada correctamente.\n";
                }
            }
            break;
        }
    } while (opcion != 0);
}

// crear, leer, actualizar, eliminar y agregar a las citas
void gestionarCitas(vector<Cita>& citas, vector<Paciente>& pacientes, vector<Medico>& medicos) {
    int opcion, id;
    string fecha;
    int urgencia, pacienteId, medicoId;

    do {
        cout << "\nGestion de citas\n";
        cout << "1. Crear cita\n2. Leer citas\n3. Modificar cita\n4. Eliminar cita\n0. Volver\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            cout << "ID de paciente: "; cin >> pacienteId;
            cout << "ID de medico: "; cin >> medicoId;
            cout << "Fecha: "; cin >> fecha;
            cout << "Urgencia (1 a 5): "; cin >> urgencia;

            Paciente* paciente = nullptr;
            Medico* medico = nullptr;

            for (auto& p : pacientes) {
                if (p.id == pacienteId) paciente = &p;
            }
            for (auto& m : medicos) {
                if (m.id == medicoId) medico = &m;
            }

            if (paciente && medico) {
                citas.push_back(Cita(citas.size() + 1, paciente, medico, fecha, urgencia));
                cout << "Cita creada correctamente.\n";
            }
            else {
                cout << "Paciente o medico no encontrado.\n";
            }
            break;
        }
        case 2:
            for (auto& c : citas) c.leerCita();
            break;

        case 3: {
            cout << "Modificar cita: "; cin >> id;
            bool citaEncontrada = false;
            for (auto& c : citas) {
                if (c.id == id) {
                    cout << "Nueva fecha: "; cin >> fecha;
                    cout << "Nueva urgencia: "; cin >> urgencia;
                    c.modificarCita(fecha, urgencia);
                    cout << "Cita modificada correctamente.\n";
                    citaEncontrada = true;
                    break;
                }
            }
            if (!citaEncontrada) {
                cout << "Cita no encontrada.\n";
            }
            break;
        }
        case 4: {
            cout << "Eliminar cita: "; cin >> id;
            auto it = remove_if(citas.begin(), citas.end(),
                [id](const Cita& c) { return c.id == id; });
            if (it != citas.end()) {
                citas.erase(it, citas.end());
                cout << "Cita eliminada.\n";
            }
            else {
                cout << "Cita no encontrada.\n";
            }
            break;
        }
        }
    } while (opcion != 0);
}

// crear, leer, actualizar, eliminar y agregar a los servicios
void gestionarServicios(vector<Servicio>& servicios) {
    int opcion;
    string nombre, descripcion;
    double costo;

    do {
        cout << "\nGestion de servicios\n";
        cout << "1. Crear servicio\n2. Leer servicios\n3. Eliminar servicio\n0. Volver\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nombre del servicio: "; cin >> nombre;
            cout << "Costo: "; cin >> costo;
            cout << "Descripcion: "; cin >> descripcion;
            servicios.push_back(Servicio(nombre, costo, descripcion));
            cout << "Servicio creado correctamente.\n";

            break;

        case 2:
            for (auto& s : servicios) s.leerServicio();

            break;

        case 3:
            cout << "Eliminar servicio: "; cin >> nombre;
            servicios.erase(remove_if(servicios.begin(), servicios.end(),
                [&nombre](const Servicio& s) { return s.servicio == nombre; }), servicios.end());
            cout << "Servicio eliminado.\n";

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
        case 2: gestionarMedicos(medicos); break;
        case 3: gestionarCitas(citas, pacientes, medicos); break;
        case 4: gestionarServicios(servicios); break;
        case 5: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Error, opcion invalida.\n";
        }
    } while (opcion != 5);
    
    return 0;
}