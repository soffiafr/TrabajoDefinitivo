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

#endif