#pragma once
class C_Joystick {
private:
	bool Update();	// false si no actualizo
public:
	void Conectar();
	void Actualizar();

	int Joy_X		= 0;
	int Joy_Y		= 0;
	int Joy_Z		= 0;
	//
	int Throttle	= 0;
	int Rotor_Small = 0;
	int Rotor_Big	= 0;
	//
	int Slide = 0;
	//
	int POV1 = 0;
	//
	int Button[39] = { 0 };

};

