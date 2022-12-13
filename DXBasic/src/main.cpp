#include "core/core.h"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reasonForCall, LPVOID res) {
    g_module = hmod;
    switch (reasonForCall) {
    case DLL_PROCESS_ATTACH: {
        core::dll::attach();
    } break;
    case DLL_PROCESS_DETACH: {
        core::dll::detach();
    } break;
    }
    return TRUE;
}