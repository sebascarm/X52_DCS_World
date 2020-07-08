//******************************************************************************************************************//
// CONFIGURACION APLICADA																							//
//******************************************************************************************************************//
// All Configuration // All Platform (La base es un Empty Proyect)													//
//																													//
// General	>	Dir Salida		> $(SolutionDir)Bin\																//
//			>	Dir Intermed	> $(SolutionDir)Tmp\																//
//			>	Nomb Destino	> $(ProjectName)		- (Release / 64 Bits)										//
//			>	Nomb Destino	> $(ProjectName)_d		- (Debug   / 64 Bits)										//
//			>	Nomb Destino	> $(ProjectName)_32		- (Release / 32 Bits)										//
//			>	Nomb Destino	> $(ProjectName)_32d	- (Debug   / 32 Bits)										//
//																													//
// Advanced >	Juego de caract	> Multibyte																			//
// C/C++	>	General			> Multi-Proc Compilation	> YES													//
//				Optimization	> Favor Size or Speed		> FAVOR FAST CODE										//
//				Preprocessor	> Prepr Definitions			> ....; NDEBUG(Solo en Release)	(Viene por defecto)		//
//				Code Generation > Runtime Library			> Multi - threaded(/ MT)  - Estatico(Solo en Release)	//
//								> Runtime Library			> DLL Multi - threaded(/ MTd) - Dinamico(Debug)	******	//
//								> Floating Point Model		> FAST													//
//			Languaje			> C++ Lang Standard			> LAST COMPILER											//
//																													//
// Linker	>	System			> SubSystem					> Windows												//
//******************************************************************************************************************//
// Plantilla con la configuración minima necesaria recomendada por chilli, se incuyen los directores de salida,		//
// especial para crear proyectos C++																				//
//******************************************************************************************************************//

//######################################################//
// PLANTILLA V 1.0										//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 24/05/2020                                           //
// Creacion                                             //
//######################################################//


#include <Windows.h>	//Obligatorio para DLL

//#include "WinApi.h"
#include "Frame.h"
//#include "Funciones.h"
#include "Eventos.h"

#pragma comment (lib, "DirectOutput.lib")

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "comctl32.lib")

#ifdef _DEBUG
#pragma comment (lib, "WinApi_d.lib")
#pragma comment (lib, "Funciones_d.lib")
#pragma comment (lib, "Archivo_d.lib")
#else
#pragma comment (lib, "WinApi.lib")
#pragma comment (lib, "Funciones.lib")
#pragma comment (lib, "Archivo.lib")
#endif

int CALLBACK WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpszCmdParam,
	_In_ int nCmdShow)
{
	CrearObjetos(hInstance);
	WinApi->Draw();

	Configurar_objetos();
	Eventos();

	WinApi->Loop();

}

