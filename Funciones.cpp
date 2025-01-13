#include "Funciones.h"
#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "Servicio.h"
#include <iostream>
#include <algorithm>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

void menu() {
    cout << "\nGestion del hospital\n";
    cout << "1. Gestionar pacientes\n";
    cout << "2. Gestionar medicos\n";
    cout << "3. Gestionar citas\n";
    cout << "4. Gestionar servicios\n";
    cout << "5. Exportar datos\n";
    cout << "6. Importar datos\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}

void gestionarPacientes(std::vector<Paciente>& pacientes) {
    int opcion, id;
    string nombre, fechaIngreso, registro;

    do {
        cout << "\nGestion de pacientes\n";
        cout << "1. Crear paciente\n2. Leer pacientes\n3. Actualizar paciente\n4. Eliminar paciente\n5. Agregar historial del paciente\n0. Volver\nOpcion: ";
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
            cout << "ID del paciente: "; cin >> id;
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
            cout << "Agregar historial: ";
            cin.ignore();
            getline(cin, registro); // ingresar palabras no solo numeros
            for (auto& p : pacientes) {
                if (p.id == id) {
                    p.agregarHistorial(registro);
                    cout << "Historial agregado correctamente.\n";
                }
            }
            break;
        }
    } while (opcion != 0);
}

void gestionarMedicos(std::vector<Medico>& medicos) {
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
            cout << "ID del medico: "; cin >> id;
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
            cout << "ID del medico: "; cin >> id;
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

void gestionarCitas(std::vector<Cita>& citas, std::vector<Paciente>& pacientes, std::vector<Medico>& medicos) {
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
            cout << "ID de la cita: "; cin >> id;
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

void gestionarServicios(vector<Servicio>& servicios, vector<Paciente>& pacientes, vector<Medico>& medicos) {
    int opcion;
    string nombre, descripcion;
    double costo;

    do {
        cout << "\nGestion de servicios\n";
        cout << "1. Crear servicio\n2. Leer servicios\n3. Eliminar servicio\n0. Volver\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int pacienteId, medicoId;
            Paciente* paciente = nullptr;
            Medico* medico = nullptr;

            cout << "Nombre del servicio: ";
            cin >> nombre;

            cout << "Costo: ";
            cin >> costo;

            cout << "Descripcion: ";
            cin.ignore();
            getline(cin, descripcion);

            cout << "ID del paciente: ";
            cin >> pacienteId;
            for (auto& p : pacientes) {
                if (p.id == pacienteId) {
                    paciente = &p;
                    break;
                }
            }

            if (!paciente) {
                cout << "No existe paciente con ese ID. No se puede crear el servicio.\n";
                break;
            }

            cout << "ID del médico: ";
            cin >> medicoId;
            for (auto& m : medicos) {
                if (m.id == medicoId) {
                    medico = &m;
                    break;
                }
            }

            if (!medico) {
                cout << "No existe médico con ese ID. No se puede crear el servicio.\n";
                break;
            }

            servicios.push_back(Servicio(nombre, costo, descripcion));
            cout << "Servicio creado correctamente para el paciente " << paciente->nombre
                << " y realizado por el médico " << medico->nombre << ".\n";

            break;
        }

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

// exportar datos a json
void exportarDatosJSON(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, const std::vector<Cita>& citas, const std::vector<Servicio>& servicios, const std::string& archivo) {
    json j;

    for (const auto& p : pacientes) {
        j["pacientes"].push_back(p.toJSON());
    }

    for (const auto& m : medicos) {
        j["medicos"].push_back(m.toJSON());
    }

    for (const auto& c : citas) {
        j["citas"].push_back(c.toJSON());
    }

    for (const auto& s : servicios) {
        j["servicios"].push_back(s.toJSON());
    }

    // guardar datos
    std::ofstream archivoSalida(archivo);
    if (archivoSalida.is_open()) {
        archivoSalida << j.dump(4);
        archivoSalida.close();
        std::cout << "Datos exportados correctamente a " << archivo << "\n";
    }
    else {
        std::cerr << "No se pudo abrir el archivo para exportar los datos.\n";
    }
}

// importar datos desde json
void importarDatosJSON(
    std::vector<Paciente>& pacientes,
    std::vector<Medico>& medicos,
    std::vector<Cita>& citas,
    std::vector<Servicio>& servicios,
    const std::string& archivo)
{
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para importar los datos.\n";
        return;
    }

    json j;
    try {
        archivoEntrada >> j;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al leer el archivo: " << e.what() << "\n";
        return;
    }

    // limpiar datos
    pacientes.clear();
    medicos.clear();
    citas.clear();
    servicios.clear();

    // importar clases
    // pacientes
    if (j.contains("pacientes")) {
        for (const auto& p : j["pacientes"]) {
            try {
                pacientes.push_back(Paciente::fromJSON(p));
            }
            catch (const std::exception& e) {
                std::cerr << "Error al importar paciente: " << e.what() << "\n";
            }
        }
    }

    // medicos
    if (j.contains("medicos")) {
        for (const auto& m : j["medicos"]) {
            try {
                medicos.push_back(Medico::fromJSON(m));
            }
            catch (const std::exception& e) {
                std::cerr << "Error al importar medico: " << e.what() << "\n";
            }
        }
    }

    // servicios
    if (j.contains("servicios")) {
        for (const auto& s : j["servicios"]) {
            try {
                servicios.push_back(Servicio::fromJSON(s));
            }
            catch (const std::exception& e) {
                std::cerr << "Error al importar servicio: " << e.what() << "\n";
            }
        }
    }

    // citas
    if (j.contains("citas")) {
        for (const auto& c : j["citas"]) {
            try {
                citas.push_back(Cita::fromJSON(c, pacientes, medicos));
            }
            catch (const std::exception& e) {
                std::cerr << "Error al importar cita: " << e.what() << "\n";
            }
        }
    }

    std::cout << "Datos importados correctamente desde " << archivo << ".\n";
}