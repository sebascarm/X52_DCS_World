#include "C_KeyboardHook.h"
#include "Funciones.h"

#include <windows.h>
#include <string>

using namespace std;

HHOOK _hook_keyboard;
KBDLLHOOKSTRUCT kbdStruct;

void Function_Hook_Empty(int ASCII);
void (*Function_Hook)(int ASCII) = &Function_Hook_Empty;

LRESULT __stdcall HookCallbackKeyboard(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
        if (wParam == WM_KEYDOWN) {
            char c = MapVirtualKey(kbdStruct.vkCode, 2);
            int ASCII = kbdStruct.vkCode;
            Function_Hook(ASCII);
        }
    }
    return CallNextHookEx(_hook_keyboard, nCode, wParam, lParam);
}

void C_KeyboardHook::SetHook(){
if (!(_hook_keyboard = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallbackKeyboard, NULL, 0)))  {
    OutputDebugString("Error al instalar hook sobre el teclado");
    }
}

void C_KeyboardHook::Assign_Event_Hook(void(*Function)(int ASCII)){
    Function_Hook = Function;
}


// No es necesario aparentemente
void C_KeyboardHook::Start() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        Sleep(10);
    }
    //return msg.wParam;

}


//*********************************************
//*** FUNCION POR DEFECTO SIN DEFINIR		***
//*********************************************
void Function_Hook_Empty(int ASCII) {
    //Debug de mensajes
    OutputDebugString("KEBOARD HOOK - EVENT NOT DEFINED\n");
}
