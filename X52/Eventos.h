#pragma once
#include <thread>			//Para hilos (multiproceso)


#include "Funciones.h"
#include <vector>

#include "Funcionalidades.h"

using namespace std;
extern int Botones[39];
extern bool ESPERAR;
extern int FILA;

void Cargar_Frame2();


extern std::vector <string> vPNombre_Proc;


void Conectar() {
	//Cargar();
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
	Teclado.UnHook();
}
void Iniciar() {
	Procedimiento();
}

void Modo0() {Cargar_Nombres(0);}
void Modo1() {Cargar_Nombres(1);}
void Modo2() {Cargar_Nombres(2);}
void Modo3() {Cargar_Nombres(3);}
void Modo4() {Cargar_Nombres(4);}
void Modo5() {Cargar_Nombres(5);}

void MostrarWaypoints() {
	Frame2->Show();
}

void BotonUp() {
	FILA -= 1;
	if (FILA == -1) FILA = 0;
	ESPERAR = false;
	Lista->Set_Row(FILA);
}
void BotonDown() {
	FILA += 1;
	if (FILA > vPNombre_Proc.size()) FILA -= 1;
	ESPERAR = false;
	Lista->Set_Row(FILA);
}
void BotonReset() {
	FILA  = 0;
	ESPERAR = false;
	Lista->Set_Row(FILA);
}


void Boton_CargarProc2() {
	Cargar_Procedimiento(Text_Proc2->Get_Text());
}

//******************************************************************//
//**** ASIGNACION DE EVENTOS									****//
//******************************************************************//

void  Eventos() {
	Boton_Conectar->Assign_Event_Click(Conectar);
	Boton_Apagar->Assign_Event_Click(Apagar);
	Boton_Encender->Assign_Event_Click(Test);
	Boton_Iniciar->Assign_Event_Click(Iniciar);
	Boton_Modo[0]->Assign_Event_Click(Modo0);
	Boton_Modo[1]->Assign_Event_Click(Modo1);
	Boton_Modo[2]->Assign_Event_Click(Modo2);
	Boton_Modo[3]->Assign_Event_Click(Modo3);
	Boton_Modo[4]->Assign_Event_Click(Modo4);
	Boton_Modo[5]->Assign_Event_Click(Modo5);
	Boton_Waypoints->Assign_Event_Click(MostrarWaypoints);
	Boton_Up->Assign_Event_Click(BotonUp);
	Boton_Down->Assign_Event_Click(BotonDown);
	Boton_Reset->Assign_Event_Click(BotonReset);
	Boton_Proc2->Assign_Event_Click(Boton_CargarProc2);
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
	
	for (int i = 0; i < 6; i++) {
		Shape_Modo[i]->Set_BackColor(RGB(100, 100, 100));
	}
	
	
	Cargar();
}

void Cargar_Frame2() {
	string tmp ="";
	string text = "";
	ARCHIVO3->Load("Waypoints.cfg");
	while (ARCHIVO3->Read_Line(tmp)) {
		Text_F2->Add_Line(tmp);
	}
}








