#pragma once

#include <string>

void Cargar();					// Carga inicial de variables del control y procedimiento 1
void Cargar_Nombres(int Modo);	// Cargar objetos del grafico de joystick
void Cargar_Procedimiento(std::string Nombre_Proc);	// Cargar procedimiento

void Recepcion_Tecla(int ASCII);
void Control_Tecla_Especial();



void Procedimiento();

int ID_Control(std::string Nombre, int& Modo);
std::string ID_Tecla(std::string Nombre, int Modo);
int ObtenerControl(std::string dBoton); 
void Th_Actualizar();