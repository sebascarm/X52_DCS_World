#pragma once
#include <thread>			//Para hilos (multiproceso)

#include "Funciones.h"
#include <vector>

using namespace std;

int Botones[39];
int POV1 = -2;
int ROT_Small = -2;
bool ROT_Small_Presionado = false;
int ROT_Big = -2;
bool ROT_Big_Presionado = false;
int SLIDE = -2;
bool SLIDE_Presionado = false;

void Th_Actualizar();
void Cargar();
void Cargar_Frame2();
void Procedimiento();
int ObtenerControl(string dBoton);
int ID_Control(string Nombre, int &Modo);
string ID_Tecla(string Nombre, int Modo);
void Cargar_Nombres(int Modo);

int Boton_pressed = -1;

string Tecla_1 = "";
string Tecla_2 = "";
string Tecla_3 = "";
string Tecla_pressed1 = "";
string Tecla_pressed2 = "";
string Tecla_pressed3 = "";

std::vector <int> vIDBoton;
std::vector <string> vNombre;
std::vector <string> vTecla;
std::vector <string> vNombre2;
std::vector <string> vTecla2;
std::vector <string> vNombre3;
std::vector <string> vTecla3;

std::vector <string> vPNombre;



void Recepcion_Tecla(int ASCII) {
	string Text;
	if (ASCII == 8) Text = "DELETE";
	else if (ASCII == 13) Text = "ENTER";
	else if (ASCII == 33) Text = "PGUP";
	else if (ASCII == 34) Text = "PGDN";
	else if (ASCII == 35) Text = "END";
	else if (ASCII == 36) Text = "HOME";
	else if (ASCII == 37) Text = "LEFT";
	else if (ASCII == 38) Text = "UP";
	else if (ASCII == 39) Text = "RIGHT";
	else if (ASCII == 40) Text = "DOWN";
	else if (ASCII == 45) Text = "INSERT";
	else if (ASCII == 46) Text = "SUPR";
	else if (ASCII == 160) Text = "SHIFT";
	else if (ASCII == 162) Text = "CTRL";
	else  Text = (char)ASCII;
	Tecla_1 = Tecla_2;
	Tecla_2 = Tecla_3;
	Tecla_3 = Text;
	Tecla_pressed1 = Tecla_3;
	Tecla_pressed2 = Tecla_2 + " " + Tecla_3;
	Tecla_pressed3 = Tecla_1 + " " + Tecla_2 + " " + Tecla_3;
	string tmp = "PRESSED: " + Tecla_pressed3 + "\n";
	OutputDebugString(tmp.c_str());
}

void Conectar() {
	
	Cargar();
	
	
	if (!X52.Conectar()) {
		Mensaje->Create("Información", "Control no conectado");
	}
	else {
		Teclado.SetHook();
		Teclado.Assign_Event_Hook(Recepcion_Tecla);
		Joystick.Conectar();
		for (int i = 0; i < 39; i++) Botones[i] = -1;
		// Ejecutar proceso de lectura
		thread Th_Actualizar(Th_Actualizar);
		Th_Actualizar.detach();
	}

}
void Test() {
	X52.Led(1, ESTADO::VERDE);
}

void Apagar() {
	
}
void Iniciar() {
	Procedimiento();
}

void Modo1() {
	Cargar_Nombres(1);
}

void Modo2() {
	Cargar_Nombres(2);
}
void Modo3() {
	Cargar_Nombres(3);
}

void MostrarWaypoints() {
	Frame2->Show();
}


//******************************************************************//
//**** ASIGNACION DE EVENTOS									****//
//******************************************************************//

void  Eventos() {
	Boton_Conectar->Assign_Event_Click(Conectar);
	Boton_Apagar->Assign_Event_Click(Apagar);
	Boton_Encender->Assign_Event_Click(Test);
	Boton_Iniciar->Assign_Event_Click(Iniciar);
	Boton_Modo1->Assign_Event_Click(Modo1);
	Boton_Modo2->Assign_Event_Click(Modo2);
	Boton_Modo3->Assign_Event_Click(Modo3);
	Boton_Waypoints->Assign_Event_Click(MostrarWaypoints);
}


//******************************************************************//
//**** Configuracion de objetos									****//
//******************************************************************//

void Configurar_objetos() {
	Frame2->Hide();
	Text_F2->Set_Font("Consolas");
	Cargar_Frame2();
	Teclado.SetHook();  // no se porque es necesario aca
	Lista->Set_Font("Consolas");
	Cargar();
	Shape_Modo1->Set_BackColor(RGB(100, 100, 100));
	Shape_Modo2->Set_BackColor(RGB(100, 100, 100));
	Shape_Modo3->Set_BackColor(RGB(100, 100, 100));
	
}

void Cargar_Frame2() {
	string tmp ="";
	string text = "";
	ARCHIVO3->Load("Waypoints.cfg");
	while (ARCHIVO3->Read_Line(tmp)) {
		Text_F2->Add_Line(tmp);
	}
}

void Cargar_Nombres(int Modo) {
	int Elementos = vIDBoton.size();
	int Id_Boton;
	string Nombre;
	string tmp;
	int Longitud;
	string Espacio;
	for (int i = 0; i < Elementos; i++){
		Id_Boton = vIDBoton[i];
		if (Modo == 1) {
			Shape_Modo1->Set_BackColor(RGB(250, 0, 0));
			Shape_Modo2->Set_BackColor(RGB(100, 100, 100));
			Shape_Modo3->Set_BackColor(RGB(100, 100, 100));
			Nombre = vNombre[i];
			Control[Id_Boton].Cambiar_ColorNombre(RGB(150, 0, 0));
		} else if (Modo == 2) {
			Shape_Modo1->Set_BackColor(RGB(100, 100, 100));
			Shape_Modo2->Set_BackColor(RGB(250, 0, 250));
			Shape_Modo3->Set_BackColor(RGB(100, 100, 100));
			Nombre = vNombre2[i];
			if (vNombre[i] != vNombre2[i]) Control[Id_Boton].Cambiar_ColorNombre(RGB(150, 0, 150));
			
		} else if (Modo == 3) {
			Shape_Modo1->Set_BackColor(RGB(100, 100, 100));
			Shape_Modo2->Set_BackColor(RGB(100, 100, 100));
			Shape_Modo3->Set_BackColor(RGB(0, 0, 250));
			Nombre = vNombre3[i];
			if (vNombre2[i] != vNombre3[i]) Control[Id_Boton].Cambiar_ColorNombre(RGB(0, 0, 250));
		}

		if (Nombre != "") {
			Control[Id_Boton].Nombre(Nombre);
		}
	}
}

void Cargar() {

	int ID_Control;
	string Dato_Boton;
	string Dato_Nombre;
	string Dato_Nombre2;
	string Dato_Nombre3;
	string Dato_Tecla;
	string Dato_Tecla2;
	string Dato_Tecla3;
	std::vector <string> vDatos;
	ARCHIVO->Load("Control.cfg");
	while (ARCHIVO->Read_LineVec(vDatos, '|')) {
		if (vDatos[0] != "") {
			Dato_Boton  = vDatos[0];
			Dato_Nombre = vDatos[2];
			Dato_Tecla  = vDatos[3];
			
			Dato_Nombre2= vDatos[4];
			Dato_Tecla2 = vDatos[5];

			Dato_Nombre3 = vDatos[6];
			Dato_Tecla3 = vDatos[7];

			ID_Control = ObtenerControl(Dato_Boton);
			
			vIDBoton.push_back(ID_Control);
			
			vNombre.push_back(Dato_Nombre);
			vTecla.push_back(Dato_Tecla);

			if (Dato_Nombre2 == "") {
				// si esta vacio cargamos el del modo 1
				vNombre2.push_back(Dato_Nombre); vTecla2.push_back(Dato_Tecla);
			} else {
				vNombre2.push_back(Dato_Nombre2);vTecla2.push_back(Dato_Tecla2);
			}
			
			if (Dato_Nombre3 == "") {
				// si esta vacio cargamos el del modo 2 o 1
				if (Dato_Nombre2 == "") { vNombre3.push_back(Dato_Nombre); vTecla3.push_back(Dato_Tecla); }
				else {vNombre3.push_back(Dato_Nombre2);	vTecla3.push_back(Dato_Tecla2);	}
			}
			else { vNombre3.push_back(Dato_Nombre3);vTecla3.push_back(Dato_Tecla3);}

			//Control[ID_Control].Nombre(Dato_Nombre);
			
		}
	}
	Cargar_Nombres(1);

	string Procedimiento;
	ARCHIVO2->Load("Config.cfg");
	while (ARCHIVO2->Read_LineVec(vDatos, '|')) {
		if (vDatos[0] != "") {
			Procedimiento = vDatos[0];
			Dato_Nombre = vDatos[1];
			
			Lista->Add_Line(Procedimiento);
			vPNombre.push_back(Dato_Nombre);
		}
	}
	
}

int ModoActual = 1;
int Modo = 1;
void Procedimiento() {
	int Elementos =vPNombre.size();
	int Id;
	string Tecla;
	string Elemento;
	bool Esperar = true;
	for (int i = 0; i < Elementos; i++)	{
		Lista->Set_Row(i);
		Elemento	= vPNombre[i];
		ModoActual = Modo;
		Id = ID_Control(Elemento, Modo);
		if (Modo != ModoActual) {
			Cargar_Nombres(Modo);
		}

		if (Id != -1) {
			Tecla = ID_Tecla(Elemento, Modo);
			Control[Id].Flash();
			Esperar = true;
			while (Esperar) {
				if (Boton_pressed == Id) Esperar = false;
				else if (Tecla != "") {
					if ((Tecla == Tecla_pressed1) |
						(Tecla == Tecla_pressed2) |
						(Tecla == Tecla_pressed3))
						Esperar = false;
				}
				Sleep(100);
			}
			Control[Id].Flash_Stop();
			Sleep(500);
			Control[Id].Pintar();
		}
	}
	
	
}

int ID_Control(string Nombre, int &Modo) {
	int Elementos = vNombre.size();
	int Id;
	if (Modo == 1) {
		//Buscamos en MODO 1
		for (int i = 0; i < Elementos; i++) {
			if (vNombre[i] == Nombre) {Id = vIDBoton[i];return Id;}
		}
		//Buscamos en MODO 2
		for (int i = 0; i < Elementos; i++) {
			if (vNombre2[i] == Nombre) {Modo = 2;Id = vIDBoton[i];return Id;}
		}
		//Buscamos en MODO 3
		for (int i = 0; i < Elementos; i++) {
			if (vNombre3[i] == Nombre) {Modo = 3;Id = vIDBoton[i];return Id;}
		}
	}
	if (Modo == 2) {
		//Buscamos en MODO 2
		for (int i = 0; i < Elementos; i++) {
			if (vNombre2[i] == Nombre) { Id = vIDBoton[i]; return Id; }
		}
		//Buscamos en MODO 3
		for (int i = 0; i < Elementos; i++) {
			if (vNombre3[i] == Nombre) { Modo = 3; Id = vIDBoton[i]; return Id; }
		}
		//Buscamos en MODO 1
		for (int i = 0; i < Elementos; i++) {
			if (vNombre[i] == Nombre) { Modo = 1; Id = vIDBoton[i]; return Id; }
		}
	}
	if (Modo == 3) {
		//Buscamos en MODO 3
		for (int i = 0; i < Elementos; i++) {
			if (vNombre3[i] == Nombre) { Id = vIDBoton[i]; return Id; }
		}
		//Buscamos en MODO 1
		for (int i = 0; i < Elementos; i++) {
			if (vNombre[i] == Nombre) { Modo = 1; Id = vIDBoton[i]; return Id; }
		}
		//Buscamos en MODO 2
		for (int i = 0; i < Elementos; i++) {
			if (vNombre2[i] == Nombre) { Modo = 2; Id = vIDBoton[i]; return Id; }
		}
	}

	string tmp = "Elemento no encontrado: " + Nombre;
	OutputDebugString(tmp.c_str());
	return -1;
}

string ID_Tecla(string Nombre, int Modo) {
	int Elementos = vNombre.size();
	string Tecla;
	for (int i = 0; i < Elementos; i++) {
		if (Modo == 1) {
			if (vNombre[i] == Nombre) {
				Tecla = vTecla[i];
				string tmp = "TECLA ESPERADA M1: " + Tecla + "\n";
				OutputDebugString(tmp.c_str());
				return Tecla;
			}
		} else if (Modo == 2) {
			if (vNombre2[i] == Nombre) {
				Tecla = vTecla2[i];
				string tmp = "TECLA ESPERADA M2: " + Tecla + "\n";
				OutputDebugString(tmp.c_str());
				return Tecla;
			}
		} else if (Modo == 3) {
			if (vNombre3[i] == Nombre) {
				Tecla = vTecla3[i];
				string tmp = "TECLA ESPERADA M3: " + Tecla + "\n";
				OutputDebugString(tmp.c_str());
				return Tecla;
			}
		}
	}
	string tmp = "Elemento Tecla no encontrado: " + Nombre;
	OutputDebugString(tmp.c_str());
	return "";
}

int ObtenerControl(string dBoton) {
	int ID;
	string bot = dBoton.substr(3, 3);
	Funciones::Trim(bot);
	ID = Funciones::To_Integer(bot);
	return ID;
}

void Th_Actualizar() {
	while (true) {
		Joystick.Actualizar();
		for (int i = 0; i < 39; i++) {
			if (Botones[i] != Joystick.Button[i]) {
				Botones[i] = Joystick.Button[i];
				if (Botones[i] == 128) {
					Boton_pressed = i;
					Control[i].Press();
				}
				else {
					Control[i].Release();
				}
			}
		}
		if (POV1 != Joystick.POV1) {
			POV1 = Joystick.POV1;
			switch (POV1) {
			case 0:
				Boton_pressed = 39;
				Control[39].Press(); Control[40].Release(); Control[41].Release(); Control[42].Release();
				break;
			case 9000:
				Boton_pressed = 40;
				Control[39].Release(); Control[40].Press(); Control[41].Release(); Control[42].Release();
				break;
			case 18000:
				Boton_pressed = 41;
				Control[39].Release(); Control[40].Release(); Control[41].Press(); Control[42].Release();
				break;
			case 27000:
				Boton_pressed = 42;
				Control[39].Release(); Control[40].Release(); Control[41].Release(); Control[42].Press();
				break;
			default:
				Control[39].Release(); Control[40].Release(); Control[41].Release(); Control[42].Release();
				break;
			}
		}
		if ((ROT_Small > Joystick.Rotor_Small + 800) | (ROT_Small < Joystick.Rotor_Small - 800)) {
			ROT_Small = Joystick.Rotor_Small;
			ROT_Small_Presionado = true;
			Boton_pressed = 43;
			Control[43].Press();
		}
		else if (ROT_Small_Presionado) {
			Control[43].Release();
			ROT_Small_Presionado = false;
		}
		if ((ROT_Big > Joystick.Rotor_Big + 800) | (ROT_Big < Joystick.Rotor_Big - 800)) {
			ROT_Big = Joystick.Rotor_Big;
			ROT_Big_Presionado = true;
			Boton_pressed = 44;
			Control[44].Press();
		}
		else if (ROT_Big_Presionado) {
			Control[44].Release();
			ROT_Big_Presionado = false;
		}
		if ((SLIDE > Joystick.Slide + 500) | (SLIDE < Joystick.Slide - 500)) {
			SLIDE = Joystick.Slide;
			SLIDE_Presionado = true;
			Boton_pressed = 45;
			Control[45].Press();
		}
		else if (SLIDE_Presionado) {
			Control[45].Release();
			SLIDE_Presionado = false;
		}

		Sleep(10);
	}
}