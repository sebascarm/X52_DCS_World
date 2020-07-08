#pragma once

#include "WinApi.h"
#include "Archivo.h"
#include "C_X52.h"
#include "C_Joystick.h"
#include "C_Control.h"
#include "C_KeyboardHook.h"

//******************************************************************//
//**** VARIABLES GLOBALES										****//
//******************************************************************//


//******************************************************************//
//**** OBJETOS GLOBALES											****//
//******************************************************************//
Archivo* ARCHIVO = New_File();
Archivo* ARCHIVO2 = New_File();
Archivo* ARCHIVO3 = New_File();

Win_Api*	WinApi = New_Api();
Win_Frame*	Frame1 = New_Frame();
Win_Menu*	Menu1 = New_Menu();
// Frame adicional
Win_Frame* Frame2 = New_Frame();
Win_Label* Label_F2 = New_Label();
Win_MultiLine *Text_F2 = New_MultiLine();

// Mensajes Generales
Win_MessageBox* Mensaje = New_MessageBox();
// Objetos			
Win_Button*	Boton_Conectar  = New_Button();
Win_Button*	Boton_Encender	= New_Button();
Win_Button*	Boton_Apagar	= New_Button();
Win_Button* Boton_Iniciar = New_Button();
Win_Button* Boton_Waypoints = New_Button();

Win_Label* Label_Modo1 = New_Label();
Win_Label* Label_Modo2 = New_Label();
Win_Label* Label_Modo3 = New_Label();

Win_Button* Boton_Modo1 = New_Button();
Win_Button* Boton_Modo2 = New_Button();
Win_Button* Boton_Modo3 = New_Button();

Win_Shape* Shape_Modo1 = New_Shape();
Win_Shape* Shape_Modo2 = New_Shape();
Win_Shape* Shape_Modo3 = New_Shape();

Win_Graphic* Grafico = New_Graphic();

Win_ListBox* Lista = New_ListBox();
// X52
C_X52 X52;
C_Joystick Joystick;
// Hoook
C_KeyboardHook Teclado;
// Controles del Joystic
C_Control Control[50];

//******************************************************************//
//**** CREAR OBJETOS											****//
//******************************************************************//
void CrearObjetos(HINSTANCE hInstance) {
	//Principal
	WinApi->Create(hInstance);
	Frame1->Create(WinApi, "DCS World Instructor", 0, 50, 1200, 600, true);
	Menu1->Create(Frame1, "Menú", { "Menu 1", "-", "Salir" });
	//Grupo1
	Boton_Conectar->Create(Frame1, "Conectar", 10, 10);
	Boton_Encender->Create(Frame1, "Encender", 80, 10);
	Boton_Apagar->Create(Frame1, "Apagar", 150, 10);
	Boton_Iniciar->Create(Frame1, "Iniciar", 300, 10);
	Boton_Waypoints->Create(Frame1, "Waypoints", 380, 10);
	
	Label_Modo1->Create(Frame1, "Arranque", 420, 40);
	Label_Modo2->Create(Frame1, "Luces", 420, 90);
	Label_Modo3->Create(Frame1, "Vuelo", 420, 140);
	
	Boton_Modo1->Create(Frame1, "Modo 1", 420, 56);
	Boton_Modo2->Create(Frame1, "Modo 2", 420, 106);
	Boton_Modo3->Create(Frame1, "Modo 3", 420, 156);
	
	Shape_Modo1->Create(Frame1, S_Style::S_RECTANGLE, 420, 80,60,10);
	Shape_Modo2->Create(Frame1, S_Style::S_RECTANGLE, 420, 130,60,10);
	Shape_Modo3->Create(Frame1, S_Style::S_RECTANGLE, 420, 180,60,10);
	
	// Frame adicional
	Frame2->Create(WinApi, "Info Adicional", 100, 100, 500, 500);
	Label_F2->Create(Frame2, "Procedimiento de carga de Waypoints y TCAN", 10, 10, 300);
	Text_F2->Create(Frame2, "", 10, 30, 480, 480);
	//


	Lista->Create(Frame1, 10, 40, 400, 500, false);
	

	//Graficos
	Grafico->Create(Frame1, "imagen.bmp", 500, 10);
	
	
	// Controles
	
	int x_ini = 945;
	int y_ini = 70;

	Control[0].Create(Frame1, &X52 , -1, COLOR::APAGADO, "Trigger", x_ini+50 , y_ini + 100,80,0,ESTILO::RECTANGULO);
	Control[1].Create(Frame1, &X52, 0, COLOR::VERDE, "Launch", x_ini, y_ini, 100, -30);
	Control[2].Create(Frame1, &X52, 1, COLOR::ROJO, "Fire A", x_ini+28, y_ini+5);
	Control[3].Create(Frame1, &X52, 3, COLOR::VERDE, "Fire B", x_ini + 26, y_ini + 32);
	Control[4].Create(Frame1, &X52, -1, COLOR::APAGADO, "Fire C", x_ini -40, y_ini + 42, - 100);
	
	Control[6].Create(Frame1, &X52, 5, COLOR::ROJO, "Fire D", x_ini - 218, y_ini + 123,40);
	Control[7].Create(Frame1, &X52, 7, COLOR::AMARILLO, "Fire E", x_ini - 234, y_ini + 90, 40);

	Control[8].Create(Frame1, &X52, 9, COLOR::VERDE, "Toggle 1", x_ini - 78, y_ini + 380, -80, 0, ESTILO::RECTANGULO);
	Control[9].Create(Frame1, &X52, 9, COLOR::VERDE, "Toggle 2", x_ini - 78, y_ini + 395, -80, 0, ESTILO::RECTANGULO);
	Control[10].Create(Frame1, &X52, 11, COLOR::VERDE, "Toggle 3", x_ini - 38, y_ini + 380, 0, -30, ESTILO::RECTANGULO);
	Control[11].Create(Frame1, &X52, 11, COLOR::VERDE, "Toggle 4", x_ini - 38, y_ini + 395, 0, 30, ESTILO::RECTANGULO);
	Control[12].Create(Frame1, &X52, 13, COLOR::VERDE, "Toggle 5", x_ini , y_ini + 380, 50, 0, ESTILO::RECTANGULO);
	Control[13].Create(Frame1, &X52, 13, COLOR::VERDE, "Toggle 6", x_ini , y_ini + 395, 50, 0, ESTILO::RECTANGULO);

	Control[14].Create(Frame1, &X52, -1, COLOR::APAGADO, "Sec Trigger", x_ini + 50, y_ini + 120, 80, 0, ESTILO::RECTANGULO);

	Control[19].Create(Frame1, &X52, 15, COLOR::VERDE, "POV-2", x_ini- 34, y_ini - 2, -40, -60, ESTILO::MINI);
	Control[20].Create(Frame1, &X52, 15, COLOR::VERDE, "POV-2", x_ini - 20, y_ini + 11, 30, -60, ESTILO::MINI);
	Control[21].Create(Frame1, &X52, 15, COLOR::VERDE, "POV-2", x_ini - 34, y_ini + 23, -120, 0, ESTILO::MINI);
	Control[22].Create(Frame1, &X52, 15, COLOR::VERDE, "POV-2", x_ini - 46, y_ini + 11, -120, -30, ESTILO::MINI);

	Control[23].Create(Frame1, &X52, -1, COLOR::APAGADO, "HAT", x_ini - 275, y_ini + 90, 0, -50, ESTILO::MINI);
	Control[24].Create(Frame1, &X52, -1, COLOR::APAGADO, "HAT", x_ini - 265, y_ini + 100, 20, -30, ESTILO::MINI);
	Control[25].Create(Frame1, &X52, -1, COLOR::APAGADO, "HAT", x_ini - 275, y_ini + 110, -100, 20, ESTILO::MINI);
	Control[26].Create(Frame1, &X52, -1, COLOR::APAGADO, "HAT", x_ini - 285, y_ini + 100, -120, 0, ESTILO::MINI);

	Control[30].Create(Frame1, &X52, 17, COLOR::AMARILLO, "Clutch", x_ini - 210, y_ini + 175,40);
	
	Control[31].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rudd Izq", x_ini - 289, y_ini + 390, -120, 0, ESTILO::RECTANGULO);
	Control[32].Create(Frame1, &X52, -1, COLOR::APAGADO, "Start/Stop", x_ini - 259, y_ini + 382, 0, -30, ESTILO::RECTANGULO);
	Control[33].Create(Frame1, &X52, -1, COLOR::APAGADO, "Reset", x_ini - 259, y_ini + 397, 0, 30, ESTILO::RECTANGULO);
	Control[34].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rudd Izq Up", x_ini - 289, y_ini + 380, -80, -30, ESTILO::RECTANGULO);
	Control[35].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rudd Izq Down", x_ini - 289, y_ini + 400, -80, 30, ESTILO::RECTANGULO);
	Control[36].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rudd Der Up", x_ini - 228, y_ini + 380, 40, -50, ESTILO::RECTANGULO);
	Control[37].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rudd Der Down", x_ini - 228, y_ini + 400, 40, 30, ESTILO::RECTANGULO);
	Control[38].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rudd Der", x_ini - 228, y_ini + 390, 40, -35, ESTILO::RECTANGULO);

	Control[39].Create(Frame1, &X52, -1, COLOR::APAGADO, "POV-1", x_ini + 4, y_ini+50, 60, 0, ESTILO::MINI);
	Control[40].Create(Frame1, &X52, -1, COLOR::APAGADO, "POV-1", x_ini + 14, y_ini + 60, 40, 15, ESTILO::MINI);
	Control[41].Create(Frame1, &X52, -1, COLOR::APAGADO, "POV-1", x_ini + 4, y_ini + 70, -30, 80, ESTILO::MINI);
	Control[42].Create(Frame1, &X52, -1, COLOR::APAGADO, "POV-1", x_ini + -6, y_ini + 60, -110, 10, ESTILO::MINI);

	Control[43].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rot Small", x_ini - 210, y_ini + 165, 40, -5, ESTILO::MINI);
	Control[44].Create(Frame1, &X52, -1, COLOR::APAGADO, "Rot Big", x_ini - 220, y_ini + 107, 40, 0, ESTILO::MINI);
	Control[45].Create(Frame1, &X52, -1, COLOR::APAGADO, "Slide", x_ini - 255, y_ini + 150, -80, 0, ESTILO::RECTANGULO);
}

