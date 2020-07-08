#pragma once

class C_KeyboardHook{

public:
	void SetHook();
	void Start();	// Aparentemente no necesario
	// Asignar Eventos		
	void	Assign_Event_Hook(void(*Function)(int ASCII)); // Devuelve el codigo Ascii
};

