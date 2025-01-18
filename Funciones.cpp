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
    cout << "5. Generar reportes\n";
    cout << "6. Exportar datos\n";
    cout << "7. Importar datos\n";
    cout << "8. Realizar backup\n";
    cout << "9. Salir\n";
    cout << "Seleccione una opcion: ";
}

void gestionarPacientes(std::vector<Paciente>& pacientes) {
    int opcion, id;
    string nombre, fechaIngreso, registro;
    bool enfermedadCronica;

    do {
        cout << "\nGestion de pacientes\n";
        cout << "1. Crear paciente\n2. Leer pacientes\n3. Actualizar paciente\n4. Eliminar paciente\n5. Agregar historial del paciente\n0. Volver\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nombre: "; cin >> nombre;
            cout << "ID: "; cin >> id;
            cout << "Fecha de ingreso (YYYY-MM-DD): "; cin >> fechaIngreso;
            cout << "¿Tiene alguna enfermedad cronica? Pulse 1 para si o 0 para no): "; cin >> enfermedadCronica;
            pacientes.push_back(Paciente(nombre, id, fechaIngreso, enfermedadCronica));
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
                    cout << "Nueva fecha de ingreso (YYYY-MM-DD): "; cin >> fechaIngreso;
                    cout << "Nueva enfermedad: "; cin >> enfermedadCronica;
                    p.modificarDatos(nombre, fechaIngreso, enfermedadCronica);
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
            cout << "Fecha (YYYY-MM-DD): "; cin >> fecha;
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
                if (medico->disponibilidad) {
                    citas.push_back(Cita(citas.size() + 1, paciente, medico, fecha, urgencia));
                    cout << "Cita creada correctamente.\n";
                }
                else {
                    cout << "Medico no disponible.\n";
                }
            }
            else {
                cout << "Paciente o medico no encontrado.\n";
            }
            break;
        }
        case 2: {
            int subopcion;
            cout << "1. Citas ordenadas por fecha\n2. Citas ordenadas por urgencia\n3. Mostrar sin ordenar\nOpcion: ";
            cin >> subopcion;

            if (subopcion == 1) {
                Cita::ordenarPorFecha(citas);
                cout << "Citas ordenadas por fecha:\n";
            }
            else if (subopcion == 2) {
                Cita::ordenarPorUrgencia(citas);
                cout << "Citas ordenadas por urgencia:\n";
            }

            for (auto& c : citas) {
                c.leerCita();
            }
            break;
        }
        case 3: {
            cout << "ID de la cita: "; cin >> id;
            bool citaEncontrada = false;
            for (auto& c : citas) {
                if (c.id == id) {
                    cout << "Nueva fecha (YYYY-MM-DD): "; cin >> fecha;
                    cout << "Nueva urgencia (1 a 5): "; cin >> urgencia;
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

void generarReportes(const std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos) {
    int opcion;

    do {
        cout << "\nReportes disponibles:\n";
        cout << "1. Listado de pacientes atendidos en un rango de fechas\n2. Citas pendientes por medico o especialidad\n3. Reporte de pacientes con enfermedades cronicas\n0. Volver\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string fechaInicio, fechaFin;
            cout << "Fecha de inicio (YYYY-MM-DD): ";
            cin >> fechaInicio;
            cout << "Fecha de fin (YYYY-MM-DD): ";
            cin >> fechaFin;

            cout << "\nPacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";
            for (const auto& cita : citas) {
                if (cita.fecha >= fechaInicio && cita.fecha <= fechaFin) {
                    cout << "- " << cita.paciente->nombre << " (ID: " << cita.paciente->id << ")\n";
                }
            }
            break;
        }
        case 2: {
            int medicoId;
            cout << "ID del medico o ingrese -1 para listar por especialidad: ";
            cin >> medicoId;

            if (medicoId != -1) {
                cout << "\nCitas pendientes para el medico con ID " << medicoId << ":\n";
                for (const auto& cita : citas) {
                    if (cita.medico->id == medicoId) {
                        cout << "- Paciente: " << cita.paciente->nombre << ", fecha: " << cita.fecha << ", urgencia: " << cita.urgencia << "\n";
                    }
                }
            }
            else {
                string especialidad;
                cout << "Ingrese la especialidad: ";
                cin.ignore();
                getline(cin, especialidad);

                cout << "\nCitas pendientes para la especialidad " << especialidad << ":\n";
                for (const auto& cita : citas) {
                    if (cita.medico->especialidad == especialidad) {
                        cout << "- Paciente: " << cita.paciente->nombre << ", medico: " << cita.medico->nombre << ", fecha: " << cita.fecha << "\n";
                    }
                }
            }
            break;
        }
        case 3: {
            cout << "\nPacientes con enfermedades cronicas:\n";
            for (const auto& paciente : pacientes) {
                if (paciente.enfermedadCronica) {
                    cout << "- " << paciente.nombre << " (ID: " << paciente.id << ")\n";
                }
            }
            break;
        }
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
    std::vector<Servicio>& servicios)

{
    int opcion;
    std::string archivo;

    std::cout << "Seleccione la fuente de datos a importar\n1. Importar desde hospital.json\n2. Importar desde un archivo de backup\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    if (opcion == 1) {
        archivo = "hospital.json";
    }
    else if (opcion == 2) {
        
        // archivos en la carpeta backup
        std::vector<std::string> archivosBackup;
        for (const auto& entry : std::filesystem::directory_iterator("backups")) {
            if (entry.is_regular_file()) {
                archivosBackup.push_back(entry.path().string());
            }
        }

        if (archivosBackup.empty()) {
            std::cout << "No hay archivos de backup disponibles.\n";
            return;
        }

        std::cout << "Archivos de backup disponibles:\n";
        for (size_t i = 0; i < archivosBackup.size(); ++i) {
            std::cout << i + 1 << ". " << archivosBackup[i] << "\n";
        }
        std::cout << "Seleccione un archivo de backup: ";
        int seleccion;
        std::cin >> seleccion;

        if (seleccion > 0 && seleccion <= archivosBackup.size()) {
            archivo = archivosBackup[seleccion - 1];
        }
        else {
            std::cout << "Opción no válida.\n";
            return;
        }
    }
    else {
        std::cout << "Opción no válida.\n";
        return;
    }

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

void realizarBackup(const std::string& nombreArchivoOriginal) {
    try {
        // crear la carpeta si no existe
        std::string carpetaBackup = "backups";
        std::filesystem::create_directory(carpetaBackup);

        // nombre del archivo de backup con fecha y hora
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H-%M-%S", now);

        std::string nombreArchivoBackup = carpetaBackup + "/backup_" + std::string(timestamp) + ".json";

        std::filesystem::copy(nombreArchivoOriginal, nombreArchivoBackup);

        std::cout << "Backup realizado correctamente en: " << nombreArchivoBackup << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al realizar el backup: " << e.what() << std::endl;
    }
}