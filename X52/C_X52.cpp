#include "C_X52.h"

#include "DirectOutput.h"
#include <vector>

std::vector<void*> Devices;	// tiene que ser un static

void __stdcall Dev_Callback(void* hDevice, bool bAdded, void* pvContext) {
	OutputDebugString("DEVICE CALLBACK\n");
	if (bAdded) {
		Devices.push_back(hDevice);
		OutputDebugString("DEVICE ADD\n");
	}
	else {

	}
}
void __stdcall Enum_Callback(void* hDevice, void* pvContext) {
	//OutputDebugString("ENUM CALLBACK\n");
	Devices.push_back(hDevice);
}

void __stdcall Page_Callback(void* hDevice, DWORD dwPage, bool bActivated, void* pvContext) {
	//OutputDebugString("PAGE CALLBACK\n");
}

void __stdcall SoftButton_Callback(void* hDevice, DWORD dwButtons, void* pvContext) {
	//OutputDebugString("SOFT CALLBACK\n");
}

bool C_X52::Conectar() {
	const wchar_t* name = L"Test";
	DirectOutput_Initialize(name);
	void* pContext = nullptr;
	DirectOutput_RegisterDeviceCallback(*Dev_Callback, pContext);
	DirectOutput_Enumerate(*Enum_Callback, pContext);
	
	

	if (Devices.size() > 0) {
		DirectOutput_RegisterPageCallback(Devices[0], *Page_Callback, pContext);
		DirectOutput_RegisterSoftButtonCallback(Devices[0], *SoftButton_Callback, pContext);
		DirectOutput_AddPage(Devices[0], dwPage, L"TestPage", FLAG_SET_AS_ACTIVE);
		Conectado = true;
		return true;	// Conectado
	}
	else {
		Conectado = false;
		return false;	// No conectado
	}
	for (int i = 0; i < 11; i++){
		Boton_Estado[i] = ESTADO::APAGADO;
	}
	

}

void C_X52::Apagar() {
	for (int i = 0; i < 20; i++){
		DirectOutput_SetLed(Devices[0], dwPage, i, 0);
	}
}


void C_X52::Led(int ID, ESTADO Estado){
	if (ID > -1) {
		Boton_Estado[ID] = Estado;
		DWORD ElementoA = 0;
		DWORD ElementoB = 0;

		switch (Estado)
		{
		case ESTADO::APAGADO:
			ElementoA = 0; ElementoB = 0;
			break;
		case ESTADO::VERDE:
			ElementoA = 0; ElementoB = 1;
			break;
		case ESTADO::ROJO:
			if (ID == 3) { ElementoA = 1; ElementoB = 1; }
			else { ElementoA = 1; ElementoB = 0; }
			break;
		case ESTADO::AMARILLO:
			ElementoA = 1; ElementoB = 1;
			break;
		}

		if (Conectado) {
			if ((ID == 0) | (ID == 19)) {
				DirectOutput_SetLed(Devices[0], dwPage, ID, ElementoA);
			}
			else {
				DirectOutput_SetLed(Devices[0], dwPage, ID, ElementoA);
				DirectOutput_SetLed(Devices[0], dwPage, ID + 1, ElementoB);

			}
		}
	}
}