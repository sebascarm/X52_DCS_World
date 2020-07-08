#include "C_Control.h"
#include <thread>			//Para hilos (multiproceso)

void C_Control::Create(Win_Frame* pFrame, C_X52* pX52, int Led , 
	COLOR Color,
	string Texto, int x, int y, int Label_x, int Label_y, 
	ESTILO Estilo){
	
	this->pX52 = pX52;
	this->Led = Led;
	this->Texto = Texto;
	Ex = x + Label_x;
	this->Estilo = Estilo;
	if (Estilo == ESTILO::REDONDO) {
		Boton->Create(pFrame, S_Style::S_CIRCLE, x, y, 20, 20);
		Ey = y + Label_y;
		Ly = y + 10;
	} else  if (Estilo == ESTILO::RECTANGULO) {
		Boton->Create(pFrame, S_Style::S_RECTANGLE, x, y, 20, 10);
		Ey = y + Label_y;
		Ly = y + 5;
	} else {
		Boton->Create(pFrame, S_Style::S_CIRCLE, x, y, 10, 10);
		Medio = 5;
		Ey = y + Label_y;
		Ly = y + 5;
	}
	Lalto = Ey - y;
	if (x == Ex) {
		Lx = x + Medio;
		Lancho = 0;
	} else if (x < Ex) {
		Lx = x + (Medio * 2);
		Lancho = Ex - x - (Medio * 2);
	} else {
		Lx = x - 1;
		Lancho = Ex - x;
	}
	Etiqueta->Create(pFrame, Texto, Ex, Ey, 150);
	Etiqueta->Set_BackColor(RGB(200, 200,200));
	Linea->Create(pFrame, S_Style::S_LINE, Lx, Ly, Lancho, Lalto);
	Linea->Set_Color(RGB(10, 160, 10));
	
	this->Color = Color;

}

void C_Control::Cambiar_ColorNombre(COLORREF Color){
	ColorNombre = Color;
	Etiqueta->Set_TextColor(ColorNombre);
}



void C_Control::Nombre(string Texto) {
	this->Texto = Texto;
	Etiqueta->Set_Text(Texto);
}

void C_Control::Press(){
	Boton->Set_BackColor(RGB(0, 250, 0));
}

void C_Control::Release(){
	Boton->Set_BackColor(RGB(100, 100, 100));
}

void C_Control::Pintar(){
	ESTADO Estado;
	if (Color == COLOR::APAGADO) Estado = ESTADO::APAGADO;
	else if (Color == COLOR::ROJO) Estado = ESTADO::ROJO;
	else if (Color == COLOR::VERDE) Estado = ESTADO::VERDE;
	else Estado = ESTADO::AMARILLO;

	pX52->Led(Led, Estado);
}



void C_Control::Flash() {
	FlashOn = true;
	thread Th_Flash([this] {Th_Flash(); });
	Th_Flash.detach();
	
}
void C_Control::Flash_Stop() {
	FlashOn = false;
	thread Th_Flash([this] {Th_Flash(); });
	Th_Flash.detach();

}

void C_Control::Th_Flash() {
	while (FlashOn) {
		pX52->Led(Led, ESTADO::ROJO);
		Boton->Set_BackColor(RGB(250, 0, 0));
		Sleep(500);
		pX52->Led(Led, ESTADO::APAGADO);
		Boton->Set_BackColor(RGB(100, 100, 100));
		Sleep(500);
	}
}