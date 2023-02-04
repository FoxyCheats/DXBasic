#include "util.h"
#include "fiber/fiber.h"
#include "rage/classes.h"
#include "memory/pointers.h"

namespace util {
	namespace network {
		CNetGamePlayer* getNetPlyrViaConId(uint8_t conId) {
			if (auto cNetworkPlayerMgr = *g_pointers.m_networkPlayerMgr; cNetworkPlayerMgr) {
				if (auto& cNetGamePlayer = cNetworkPlayerMgr->m_player_list[conId]; cNetGamePlayer && cNetGamePlayer->IsConnected()) {
					return cNetGamePlayer;
				}
			}
			return nullptr;
		}
		CNetGamePlayer* getNetPlyrViaPeerAddress(uint64_t peerAddress) {
			if (auto cNetworkPlayerMgr = *g_pointers.m_networkPlayerMgr; cNetworkPlayerMgr) {
				for (uint16_t i{ cNetworkPlayerMgr->m_player_count }; i; --i) {
					if (auto cNetGamePlayer = getNetPlyrViaConId(i); cNetGamePlayer && cNetGamePlayer->IsConnected()) {
						if (auto rlGamerInfo = cNetGamePlayer->GetGamerInfo()) {
							if (rlGamerInfo->m_peer_address == peerAddress) {
								return cNetGamePlayer;
							}
						}
					}
				}
			}
			return nullptr;
		}
		CNetGamePlayer* getNetPlyrViaPeer(uint64_t peerId) {
			if (auto cNetworkPlayerMgr = *g_pointers.m_networkPlayerMgr; cNetworkPlayerMgr) {
				for (auto& cNetGamePlayer : cNetworkPlayerMgr->m_player_list) {
					if (cNetGamePlayer && cNetGamePlayer->IsConnected()) {
						if (auto rlGamerInfo = cNetGamePlayer->GetGamerInfo(); rlGamerInfo)
							if (rlGamerInfo->m_platform_data == peerId)
								return cNetGamePlayer;
					}
				}
			}
			return nullptr;
		}
		bool isSessionActive() {
			return player::g_entityHandle != -1 && player::g_networkHandle && player::g_networkHandle->IsConnected();
		}
	}
	namespace entity {
		Entity getEntityFromHandle(rage::CEntity* handle) {
			if (handle)
				return g_pointers.m_pointerToHandle(handle);
			return NULL;
		}
		rage::CEntity* getCEntityFromHandle(Entity handle) {
			if (handle)
				return g_pointers.m_handleToPointer(handle);
			return nullptr;
		}
	}
	namespace player {
		Player getLocalPlayerHandle() {
			if (auto cNetGamePlayer = getLocalCNetGamePlayer(); cNetGamePlayer && network::isSessionActive()) {
				return static_cast<Player>(cNetGamePlayer->m_player_id);
			}
			return -1;
		}
		CNetGamePlayer* getLocalCNetGamePlayer() {
			if (auto cNetworkPlayerMgr = *g_pointers.m_networkPlayerMgr; cNetworkPlayerMgr) {
				if (auto cNetGamePlayer = cNetworkPlayerMgr->m_local_net_player; cNetGamePlayer && cNetGamePlayer->IsConnected()) {
					return cNetGamePlayer;
				}
			}
			return nullptr;
		}
		CPlayerInfo* getLocalCPlayerInfo() {
			return ped::g_handle->m_player_info;
		}
		void tick() {
			g_handle = getLocalCPlayerInfo();
			g_entityHandle = getLocalPlayerHandle();
			g_networkHandle = getLocalCNetGamePlayer();
		}
	}
	namespace ped {
		CPed* getLocalCPed() {
			if (auto& cPedFactory = *g_pointers.m_pedFactory; cPedFactory) {
				if (auto& cPed = cPedFactory->m_local_ped; cPed) {
					return cPed;
				}
			}
			return nullptr;
		}
		Ped getLocalPedHandle() {
			if (auto cPed = getLocalCPed(); cPed)
				return entity::getEntityFromHandle(cPed);
			return NULL;
		}
		void tick() {
			g_handle = getLocalCPed();
			g_entityHandle = getLocalPedHandle();
		}
	}
	namespace vehicle {
		CVehicle* getLocalCVehicle() {
			return ped::g_handle->m_vehicle;
		}
		Vehicle getLocalVehicleHandle() {
			return entity::getEntityFromHandle(vehicle::g_handle);
		}
		void tick() {
			g_handle = getLocalCVehicle();
			g_entityHandle = getLocalVehicleHandle();
		}
	}
	void onTick() {
		while (true) {
			ped::tick();
			player::tick();
			vehicle::tick();
			fibers::fiber::cur()->wait();
		}
	}
}