#include "core/core.h"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reasonForCall, LPVOID res) {
    switch (reasonForCall) {
    case DLL_PROCESS_ATTACH: {
        g_module = hmod;
        core::dll::attach();
    } break;
    case DLL_PROCESS_DETACH: {
        core::dll::detach();
    } break;
    }
    return TRUE;
}
