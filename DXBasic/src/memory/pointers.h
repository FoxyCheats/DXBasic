#pragma once
#include "pch/pch.h"
#include "rage/classdefs.h"
#include "memory/signature.h"
#include "rage/enums.h"
#include "natives/invoker/invoker.h"
#include "core/logger.h"

namespace rage {
	class scrNativeRegistration {
	public:
		uintptr_t m_nextReg1;
		uintptr_t m_nextReg2;
		void* m_handlers[7];
		uint32_t m_entries1;
		uint32_t m_entries2;
		uintptr_t m_hashes;
		inline scrNativeRegistration* getNext() {
			uintptr_t result;
			auto v5 = uintptr_t(&m_nextReg1); auto v12 = 2;
			auto v13 = v5 ^ m_nextReg2; auto v14 = (char*)&result - v5;
			do {
				*(DWORD*)&v14[v5] = static_cast<DWORD>(v13) ^ *(DWORD*)v5;
				v5 += 4; --v12;
			} while (v12);
			return (scrNativeRegistration*)result;
		}
		inline uint32_t getNum() {
			return static_cast<uint32_t>(((uintptr_t)&m_entries1) ^ m_entries1 ^ m_entries2);
		}
		inline uintptr_t getHash(uint32_t index) {
			auto naddr = 16 * index + uintptr_t(&m_nextReg1) + 0x54; auto v8 = 2;
			uintptr_t nResult; auto v11 = (char*)&nResult - naddr;
			auto v10 = naddr ^ *(DWORD*)(naddr + 8);
			do {
				*(DWORD*)&v11[naddr] = static_cast<DWORD>(v10 ^ *(DWORD*)(naddr));
				naddr += 4; --v8;
			} while (v8);
			return nResult;
		}
	};
	class scrNativeRegistrationTable {
	public:
		scrNativeRegistration* m_entries[0xFF];
		uint32_t m_unk;
		bool m_initialized;
	};
	class scrNativeCallContext;
	using scrNativeHandler = fnptr<void(scrNativeCallContext*)>;
}
namespace funcTypes {
	using scriptVirtualMachineT = int64_t(*)(void* stack, int64_t** globals, rage::scrProgram* program, rage::scrThreadContext* threadContext);
	using getNativeHandlerT = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable* _this, uint64_t translatedHash);
}
class pointers {
public:
	void scan();
public:
	funcTypes::scriptVirtualMachineT m_scriptVirtualMachine{};
	funcTypes::getNativeHandlerT m_getNativeHandler{};
public:
	CNetworkPlayerMgr** m_networkPlayerMgr{};
	CPedFactory** m_pedFactory{};
	rage::atArray<GtaThread*>* m_gtaThreads{};
	rage::scrNativeRegistrationTable* m_nativeRegistrationTable{};
	intptr_t** m_globals{};
	IDXGISwapChain** m_swapchain{};
	void* m_jmpRbxRegister{};
	HWND m_hwnd{};
};
inline pointers g_pointers{};