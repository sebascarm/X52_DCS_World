#pragma once
#include "WinApi.h"
#include "C_X52.h"

enum class COLOR {
	APAGADO,
	VERDE,
	ROJO,
	AMARILLO
};

enum class ESTILO {
	REDONDO,
	RECTANGULO,
	MINI
};

class C_Control {
private:
	Win_Shape* Boton = New_Shape();
	Win_Label* Etiqueta = New_Label();
	Win_Shape* Linea = New_Shape();


	int Ex = 0;
	int Ey = 0;
	int Lx = 0;
	int Ly = 0;
	int Lancho =  0;
	int Lalto  = 0;
	int Medio = 10;

	C_X52* pX52;
	int Led;
	
	void Th_Flash();
	bool FlashOn = false;
public:
	void Create(Win_Frame* pFrame, C_X52* pX52, int Led, 
		COLOR Color, 
		string Texto, int x, int y, int Label_x=80, int Label_y=0, 
		ESTILO Estilo = ESTILO::REDONDO);
	void Cambiar_ColorNombre(COLORREF Color);
	void Nombre(string Texto);
	void Press();
	void Release();
	void Pintar();
	void Flash();
	void Flash_Stop();
	COLORREF ColorNombre = RGB(0, 0, 0);
	ESTILO Estilo = ESTILO::REDONDO;
	COLOR Color = COLOR::APAGADO;
	string Texto;
};

