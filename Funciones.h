#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "Servicio.h"
#include <vector>

void menu();
void gestionarPacientes(vector<Paciente>& pacientes);
void gestionarMedicos(vector<Medico>& medicos);
void gestionarCitas(vector<Cita>& citas, vector<Paciente>& pacientes, vector<Medico>& medicos);
void gestionarServicios(vector<Servicio>& servicios, vector<Paciente>& pacientes, vector<Medico>& medicos);
void generarReportes(const std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos);

// json
void exportarDatosJSON(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, const std::vector<Cita>& citas, const std::vector<Servicio>& servicios, const std::string& archivo);
void importarDatosJSON(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas, std::vector<Servicio>& servicios);

// backup
void realizarBackup(const std::string& nombreArchivoOriginal);

#endif