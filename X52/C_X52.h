#pragma once
#include "WinApi.h"

enum class ESTADO {
	APAGADO,
	VERDE,
	ROJO,
	AMARILLO
};

class C_X52 {
	DWORD dwPage = 0;

public:
	bool Conectar();
	bool Conectado = false;
	ESTADO Boton_Estado[11]; // = { ESTADO::APAGADO };
	string Boton_Nombre[11] = { "" };
	string Boton_Alias[11] = { "" };
	void Led(int ID, ESTADO Estado = ESTADO::APAGADO);
	void Apagar();

};

