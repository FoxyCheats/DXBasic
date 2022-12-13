#pragma once
#include <vector>

enum class eAmmoSpecialType : int32_t {
	None,
	ArmorPiercing,
	Explosive,
	FMJ,
	HollowPoint,
	Incendiary,
	Tracer
};
enum class eDamageType : int32_t {
	Unknown,
	None,
	Melee,
	Bullet,
	_0xC5403EC0,
	Explosive,
	Fire,
	_0xA869C908,
	Fall,
	_0xCAE075C0,
	Electric,
	BarbedWire,
	FireExtinguisher,
	Smoke,
	WaterCannon,
	_0x1C8E59AE
};
enum class eFireType : int32_t {
	None,
	Melee,
	InstantHit,
	DelayedHit,
	ProjectTile,
	VolumetricParticle
};
enum class eWheelSlot : int32_t {
	Pistol,
	SMG,
	Rifle,
	Sniper,
	UnarmedMelee,
	ShotGun,
	Heavy,
	Throwable
};
enum poolTypes : uint16_t {
	vehT = 1,
	pedT = 2,
	objT = 4,
	pckpT = 8,
	camT = 16
};
enum class eThreadState : uint32_t {
	running,
	sleeping,
	killed,
	paused,
	breakpoint
};
enum class eGameState : int32_t {
	Invalid = -1,
	Playing,
	Died,
	Arrested,
	FailedMission,
	LeftGame,
	Respawn,
	InMPCutscene
};
class FriendInfo;
class FriendList;
class FriendRegistry;
class CNonPhysicalPlayerData;
class CBaseModelInfo;
class CNavigation;
class CHandlingData;
class CAutomobile;
class AimingInfo;
class CItemInfo;
class CWeaponInfo;
class CPedWeaponManager;
class CPedFactory;
class CPed;
class CPlayerInfo;
class CNetGamePlayer;
class CNetworkPlayerMgr;
class CScriptedGameEvent;
class CNetworkIncrementStatEvent;
class ScInfo;
class GtaThread;
class CPickup;
class CPickupHandle;
class CPickupList;
class CPickupInterface;
class CObject;
class CObjectHandle;
class CObjectList;
class CObjectInterface;
class CPedHandle;
class CPedList;
class CPedInterface;
class CVehicleHandle;
class CVehicleList;
class CVehicleInterface;
class CReplayInterface;
class CNetworkObjectMgr;
class CUpdateFxnEventVtbl;
namespace rage {
	struct vector2;
	struct vector3;
	struct vector4;
	class netLoggingInterface;
	class nonPhysicalPlayerDataBase;
	union netAddress;
	class rlGamerInfo;
	class rlGamerInfoBase;
	class netPlayer;
	class netPlayerMgrBase;
	class fwDrawData;
	class netObject;
	class fwEntity;
	class datBitBuffer;
	class netGameEvent;
	struct entTask;
	template <typename T>
	class atArray;
	class scrProgram;
	class scrProgramTableEntry;
	class scrProgramTable;
	class scriptId;
	class scriptHandlerObject;
	class scriptResource;
	class scriptHandler;
	class scriptHandlerNetComponent;
	class scrThreadContext;
	class tlsContext;
	class scrThread;
	class rlGamerHandle;
	class rlSessionInfo;
	class rlSessionByGamerTaskResult;
	class rlPresenceEventInviteAccepted;
	class netSyncTree;
	class netSyncTreeNode;
	class netObject;
	class netObjectMgrBase;
	namespace netConnection {
		class InFrame;
	}
	class CEntity;
	class CDynamicEntity;
	class CPhysical;
	class datBase {
	public:
		virtual ~datBase() = default;
	};
	class pgBase;
	template <typename T, typename Base = datBase>
	class atDNode : public Base {
	public:
		T m_data;
		void* m_unk;
		atDNode<T, Base>* m_next;
	};
	template <typename Node>
	class atDList {
	public:
		Node* m_head;
		Node* m_tail;
	};
}