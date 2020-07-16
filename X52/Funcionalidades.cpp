#include "Funcionalidades.h"



#include <WinApi.h>

#include "C_Control.h"
#include "C_Joystick.h"

#include "Archivo.h"
#include "Funciones.h"


using namespace std;

// Variables globales
int Botones[39];
int POV1 = -2;
int ROT_Small = -2;
bool ROT_Small_Presionado = false;
int ROT_Big = -2;
bool ROT_Big_Presionado = false;
int SLIDE = -2;
bool SLIDE_Presionado = false;



string Tecla_1 = "";
string Tecla_2 = "";
string Tecla_3 = "";
string Tecla_pressed1 = "";
string Tecla_pressed2 = "";
string Tecla_pressed3 = "";

std::vector <int> vIDBoton;
std::vector <string> vNombre[6];
std::vector <string> vTecla[6];

std::vector <string> vPNombre_Proc;

int ModoActual = 0;
int Modo = 0;

bool ESPERAR = true;		// Estado de Espera
int FILA = 0;				// Fila del listbox

int Boton_pressed = -1;

// elementos externos
extern Win_MessageBox* Mensaje;
extern Win_Shape* Shape_Modo[6];
extern Win_ListBox* Lista;
extern Win_TextBox* Text_Esperando;
extern Win_TextBox* Text_Recibido;

extern C_Control Control[50];

extern Archivo* ARCHIVO;
extern Archivo* ARCHIVO2;

extern C_Joystick Joystick;

void Cargar() {
	int ID_Control;
	string Dato_Boton;
	string Dato_Nombre[6];
	string Dato_Tecla[6];
		
	std::vector <string> vDatos;
	

	ARCHIVO->Load("Control.cfg");
	while (ARCHIVO->Read_LineVec(vDatos, '|')) {
		if (vDatos[0] != "") {
			int CantDatos = vDatos.size();
			Dato_Boton = vDatos[0];
			Dato_Nombre[0] = vDatos[2];		Dato_Tecla[0]  = vDatos[3];
			Dato_Nombre[1] = vDatos[4];		Dato_Tecla[1]  = vDatos[5];
			Dato_Nombre[2] = vDatos[6];		Dato_Tecla[2]  = vDatos[7];
			if (CantDatos > 8)  Dato_Nombre[3] = vDatos[8];	 if (CantDatos > 9)  Dato_Tecla[3] = vDatos[9];
			if (CantDatos > 10) Dato_Nombre[4] = vDatos[10]; if (CantDatos > 11) Dato_Tecla[4] = vDatos[11];
			if (CantDatos > 12) Dato_Nombre[5] = vDatos[12]; if (CantDatos > 13) Dato_Tecla[5] = vDatos[13];
			

			ID_Control = ObtenerControl(Dato_Boton);
			vIDBoton.push_back(ID_Control);
			
			for (int i = 0; i < 6; i++) {
				if (Dato_Nombre[i] == "") {
					vNombre[i].push_back(vNombre[i - 1].back());
					vTecla[i].push_back(vTecla[i - 1].back());
				} else {
				vNombre[i].push_back(Dato_Nombre[i]);
				vTecla[i].push_back(Dato_Tecla[i]);
				}
			}

		}
	}
	Cargar_Nombres(0);
	Cargar_Procedimiento("Arranque");
	
}

void Control_Tecla_Especial() {
	if (Tecla_pressed2 == "SHIFT F1")	   Cargar_Nombres(1);
	else if (Tecla_pressed2 == "SHIFT F2") Cargar_Nombres(2);
	else if (Tecla_pressed2 == "SHIFT F3") Cargar_Nombres(3);
	else if (Tecla_pressed2 == "SHIFT F4") Cargar_Nombres(3);
	else if (Tecla_pressed2 == "SHIFT F5") Cargar_Nombres(3);
	else if (Tecla_pressed2 == "SHIFT F6") Cargar_Nombres(3);

}

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
	else if (ASCII == 112) Text = "F1";
	else if (ASCII == 113) Text = "F2";
	else if (ASCII == 114) Text = "F3";
	else if (ASCII == 115) Text = "F4";
	else if (ASCII == 116) Text = "F5";
	else if (ASCII == 117) Text = "F6";
	else if (ASCII == 118) Text = "F7";
	else if (ASCII == 119) Text = "F8";
	else if (ASCII == 120) Text = "F9";
	else if (ASCII == 121) Text = "F10";
	else if (ASCII == 122) Text = "F11";
	else if (ASCII == 123) Text = "F12";
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
	Text_Recibido->Set_Text(Tecla_pressed3);
	//tmp = "ASCII: " + to_string(ASCII) + "\n";
	//OutputDebugString(tmp.c_str());
	Control_Tecla_Especial();		// Revisamos si se presiona una tecla especial
}

void Cargar_Nombres(int Modo) {
	
	int Elementos = vIDBoton.size();
	int Id_Boton;
	string Nombre;
	string tmp;
	int Longitud;
	string Espacio;
	for (int i = 0; i < Elementos; i++) {
		Id_Boton = vIDBoton[i];
		// Todos gris
		for (int j = 0; j < 6; j++) {
			if (Modo != j) Shape_Modo[j]->Set_BackColor(RGB(100, 100, 100));
		}
		//Pintado
		if (Modo == 0) {
			Shape_Modo[Modo]->Set_BackColor(RGB(250, 0, 0));
			Control[Id_Boton].Cambiar_ColorNombre(RGB(150, 0, 0));
		}
		else if (Modo == 1) {
			Shape_Modo[Modo]->Set_BackColor(RGB(250, 0, 250));
			if (vNombre[0][i] != vNombre[1][i]) Control[Id_Boton].Cambiar_ColorNombre(RGB(150, 0, 150));
		}
		else if (Modo == 2) {
			Shape_Modo[Modo]->Set_BackColor(RGB(0, 0, 250));
			if (vNombre[1][i] != vNombre[2][i]) Control[Id_Boton].Cambiar_ColorNombre(RGB(0, 0, 250));
		}
		else if (Modo == 3) {
			Shape_Modo[Modo]->Set_BackColor(RGB(0, 0, 150));
			if (vNombre[2][i] != vNombre[3][i]) Control[Id_Boton].Cambiar_ColorNombre(RGB(80, 80, 150));
		}
		else if (Modo == 4) {
			Shape_Modo[Modo]->Set_BackColor(RGB(150, 0, 150));
			if (vNombre[3][i] != vNombre[4][i]) Control[Id_Boton].Cambiar_ColorNombre(RGB(0, 0, 150));
		}
		else if (Modo == 5) {
			Shape_Modo[Modo]->Set_BackColor(RGB(150, 0, 0));
			if (vNombre[4][i] != vNombre[5][i]) Control[Id_Boton].Cambiar_ColorNombre(RGB(0, 0, 150));
		}

		Nombre = vNombre[Modo][i];
		if (Nombre != "") {
			Control[Id_Boton].Nombre(Nombre);
		}
	}
	
}

void Cargar_Procedimiento(string Nombre_Proc) {
	string NArchivo = Nombre_Proc + ".cfg";
	string Procedimiento, Dato_Nombre;
	std::vector <string> vDatos;
	if (!ARCHIVO2->Load(NArchivo)) {
		Mensaje->Create("Información", "No existe el archivo de configuración");
	}
	else {
		Lista->Clear();			// Vaciar Lista 
		vPNombre_Proc.clear();	// Vaciar procedimiento
		while (ARCHIVO2->Read_LineVec(vDatos, '|')) {
			if (vDatos[0] != "") {
				Procedimiento = vDatos[0];
				Dato_Nombre = vDatos[1];
				Lista->Add_Line(Procedimiento);
				vPNombre_Proc.push_back(Dato_Nombre);
			}
		}
	}
}




void Procedimiento() {
	int Elementos = vPNombre_Proc.size();
	int Id;
	string Tecla;
	string Elemento;
	string tmp;

	FILA = 0;
	Lista->Set_Row(FILA);
	while (FILA < Elementos) {
		Lista->Set_Row(FILA);
		Elemento = vPNombre_Proc[FILA];
		ModoActual = Modo;
		Id = ID_Control(Elemento, Modo);		// Boton Esperado
		if (Modo != ModoActual) {
			Cargar_Nombres(Modo);
		}

		if (Id != -1) {
			Tecla = ID_Tecla(Elemento, Modo);	// Tecla = Tecla Esperada
			Control[Id].Flash();
			if (Tecla == "") {
				tmp = "BOTON MODO " + to_string(Modo) + ": " + to_string(Id) + "\n";
			} else {
				tmp = "TECLA MODO " + to_string(Modo) + ": " + Tecla + "\n";
			}
			OutputDebugString(tmp.c_str());
			Text_Esperando->Set_Text(tmp);

			ESPERAR = true;
			while (ESPERAR) {
				if (Tecla == "") {
					if (Boton_pressed == Id) {	// Boton esperado apretado
						Boton_pressed = -1;
						ESPERAR = false;
						FILA += 1;
					}
				} else {
					if ((Tecla == Tecla_pressed1) |				// Tecla esperada apretada
						(Tecla == Tecla_pressed2) |
						(Tecla == Tecla_pressed3)) {
						Tecla_pressed1 = ""; Tecla_pressed2 = ""; Tecla_pressed3 = "";
						ESPERAR = false;
						FILA += 1;
					}
				}
				Sleep(50);
			}
			Control[Id].Flash_Stop();
			Sleep(500);
			Control[Id].Pintar();
		}
	}
}




int ID_Control(string Nombre, int& Modo) {
	int Elementos = vNombre[0].size();
	int Id;
	
	// Buscamos en el modo actual
	for (int i = 0; i < Elementos; i++) {
		if (vNombre[Modo][i] == Nombre) { 
			Id = vIDBoton[i]; 
			return Id; }
	}
	// si no retorno buscamos en los proximos modos
	for (int mod = Modo + 1; mod < 6; mod++) {
		for (int i = 0; i < Elementos; i++) {
			if (vNombre[mod][i] == Nombre) { 
				Modo = mod; 
				Id = vIDBoton[i]; 
				return Id; 
			}
		}
	}
	// si no retorno buscamos en los modos iniciales
	for (int mod = 0; mod < Modo; mod++) {
		for (int i = 0; i < Elementos; i++) {
			if (vNombre[mod][i] == Nombre) { 
				Modo = mod; 
				Id = vIDBoton[i]; 
				return Id; }
		}
	}

	string tmp = "Elemento BOTON no encontrado: " + Nombre + "\n";
	OutputDebugString(tmp.c_str());
	return -1;
}



string ID_Tecla(string Nombre, int Modo) {
	int Elementos = vNombre[0].size();
	string Tecla;
	
	for (int i = 0; i < Elementos; i++) {
		if (vNombre[Modo][i] == Nombre) {
			Tecla = vTecla[Modo][i];
			return Tecla;
		}
	}
	
	string tmp = "Elemento Tecla no encontrado: " + Nombre + "\n";
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
	int Boton_Ant = -1;
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

		if (Boton_Ant != Boton_pressed) {
			Boton_Ant = Boton_pressed;
			if (Boton_pressed != -1) {
				string tmp = "BOTON: " + to_string(Boton_pressed);
				Text_Recibido->Set_Text(tmp);
			}
		}

		Sleep(10);
	}
}