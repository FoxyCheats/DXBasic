#pragma once
#include "pch/pch.h"
#include "rage/classdefs.h"
#include "natives/types.h"

namespace util {
	namespace network {
		extern CNetGamePlayer* getNetPlyrViaConId(uint8_t conId);
		extern CNetGamePlayer* getNetPlyrViaPeerAddress(uint64_t peerAddress);
		extern CNetGamePlayer* getNetPlyrViaPeer(uint64_t peerId);
		extern bool isSessionActive();
	}
	namespace entity {
		extern Entity getEntityFromHandle(rage::CEntity* handle);
		extern rage::CEntity* getCEntityFromHandle(Entity handle);
	}
	namespace player {
		inline CPlayerInfo* g_handle{};
		inline CNetGamePlayer* g_networkHandle{};
		inline Player g_entityHandle{};
		extern Player getLocalPlayerHandle();
		extern CNetGamePlayer* getLocalCNetGamePlayer();
		extern CPlayerInfo* getLocalCPlayerInfo();
		extern void tick();
	}
	namespace ped {
		inline CPed* g_handle{};
		inline Ped g_entityHandle{};
		extern CPed* getLocalCPed();
		extern Ped getLocalPedHandle();
		extern void tick();
	}
	namespace vehicle {
		inline CVehicle* g_handle{};
		inline Vehicle g_entityHandle{};
		extern CVehicle* getLocalCVehicle();
		extern Vehicle getLocalVehicleHandle();
		extern void tick();
	}
	extern void onTick();
}