#pragma once
#include "classdefs.h"
#include "memory/pointers.h"
#include <cassert>
#define reintType(type, ...) reinterpret_cast<type>(__VA_ARGS__)
#define reintDeclType(type, ...) reinterpret_cast<decltype(type)>(__VA_ARGS__)
#define defAsVoid(def) reintType(void*, def)
#define defAsVoidPtr(def) reintType(void**, def)
#define defAsInt64(def) reintType(int64_t**, def)

namespace rage {
	struct vector2 { float x; float y; };
	struct vector3 { float x; float y; float z; };
	struct vector4 { float x; float y; float z; float w; };
	class netLoggingInterface {
	public:
	};
	class nonPhysicalPlayerDataBase {
	public:
		virtual ~nonPhysicalPlayerDataBase() = default;    // 0 (0x00)
		virtual void unk_0x08() = 0;                       // 1 (0x08)
		virtual void unk_0x10() = 0;                       // 2 (0x10)
		virtual void unk_0x18() = 0;                       // 3 (0x18)
		virtual void log(netLoggingInterface* logger) = 0; // 4 (0x20)
	};
	union netAddress {
		uint32_t m_packed; //0x0000
		struct {
			uint8_t m_field4; //0x0000
			uint8_t m_field3; //0x0001
			uint8_t m_field2; //0x0002
			uint8_t m_field1; //0x0003
		};
	};
	static_assert(sizeof(netAddress) == 0x04);
	class netSocketAddress {
	public:
		union netAddress m_ip; //0x0000
		uint16_t m_port; //0x0004
	};
	static_assert(sizeof(netSocketAddress) == 0x08);
	class rlGamerHandle {
	public:
		rlGamerHandle() : m_rockstar_id(NULL), m_platform(3) {}
		rlGamerHandle(uint64_t rockstar_id) : m_rockstar_id(rockstar_id), m_platform(3) {}
	public:
		uint64_t m_rockstar_id; //0x0000
		uint64_t m_platform; //0x0008
	public:
		bool deserialize(class datBitBuffer& buf);
		bool serialize(class datBitBuffer& buf);
	}; //Size: 0x0010
	static_assert(sizeof(rlGamerHandle) == 0x10);
	class rlGamerInfoBase {
	public:
		uint64_t m_peer_id; //0x0000
		rlGamerHandle m_gamer_handle; //0x0008
		char m_aes_key[32]; //0x0018
		uint8_t unk_0038; //0x0038
		netSocketAddress m_unk_address; //0x003C
		netSocketAddress m_relay_address; //0x0044
		netSocketAddress m_public_address; //0x004C
		netSocketAddress m_local_address;  //0x0054
		uint32_t unk_005C; //0x005C
	};
	static_assert(sizeof(rlGamerInfoBase) == 0x60);
	class rlGamerInfo : public rlGamerInfoBase {
	public:
		uint64_t m_peer_address; //0x0060
		uint64_t m_platform_data; //0x0068
		rlGamerHandle m_unk_gamer_handle; //0x0070
		uint32_t m_ros_privilege; //0x0080
		char m_name[20]; //0x0084
	}; //Size: 0x0098
	static_assert(sizeof(rlGamerInfo) == 0x98);
#pragma pack(push, 8)
	class netPlayer {
	public:
		virtual ~netPlayer();
		virtual void Reset();
		virtual bool IsConnected();
		virtual const char* GetName();
		virtual void _0x20();
		virtual bool IsNetworkHost();
		virtual rlGamerInfo* GetGamerInfo();
		virtual void _0x38();

		char pad_0008[8]; //0x0008
		class CNonPhysicalPlayerData* m_non_physical_player; //0x0010
		uint32_t m_msg_id; //0x0018
		char pad_001C[4]; //0x001C
		uint8_t m_active_id; //0x0020
		uint8_t m_player_id; //0x0021
		char pad_0022[3]; //0x0022
		uint16_t m_complaints; //0x0026
		char pad_0027[17]; //0x0028
		CNetGamePlayer* m_unk_net_player_list[10]; //0x0040
		uint32_t unk_0090; //0x0090
		uint64_t unk_0098; //0x0098
	}; //Size: 0x00A0
	static_assert(sizeof(netPlayer) == 0xA0);
#pragma pack(pop)
#pragma pack(push, 8)
	class netPlayerMgrBase {
	public:
		virtual ~netPlayerMgrBase();
		virtual void Initialize();
		virtual void Shutdown();
		virtual void unk_0x18();
		virtual class CNetGamePlayer* RawAddPlayer(void* a1, void* a2, void* a3, class rlGamerInfo* gamer_info, class CNonPhysicalPlayerData* non_physical_player_data);
		virtual void RemovePlayer(class CNetGamePlayer* net_game_player);
		virtual void UpdatePlayerListsForPlayer(class CNetGamePlayer* net_game_player);
		virtual class CNetGamePlayer* AddPlayer(void* a1, void* a2, void* a3, class rlGamerInfo* gamer_info, class CNonPhysicalPlayerData* non_physical_player_data);

		char pad_0008[8]; //0x0008
		uint64_t* m_network_bandwidth_manager; //0x0010
		char pad_0018[208]; //0x0018
		class CNetGamePlayer* m_local_net_player; //0x00E8
		char pad_00F0[144]; //0x00F0
		class CNetGamePlayer* m_player_list[32]; //0x0180
		uint16_t m_player_limit; //0x0280
		char pad_0282[10]; //0x0282
		uint16_t m_player_count; //0x028C
		char pad_0290[1618]; //0x0290
	}; //Size: 0x08E0
	static_assert(sizeof(netPlayerMgrBase) == 0x8E0);
#pragma pack(pop)
	class fwDrawData {
	public:
		char pad_0000[904]; //0x0000
		uint8_t m_primary_color; //0x0388
		char pad_0389[3]; //0x0389
		uint8_t m_pearlescent; //0x038C
		char pad_038D[3]; //0x038D
		uint8_t m_secondary_color; //0x0390
		char pad_0391[15]; //0x0391
		uint8_t m_neon_blue; //0x03A0
		uint8_t m_neon_green; //0x03A1
		uint8_t m_neon_red; //0x03A2
		char pad_03A3[15]; //0x03A3
		uint8_t m_spoiler; //0x03B2
		uint8_t m_bumper_front; //0x03B3
		uint8_t m_bumper_rear; //0x03B4
		uint8_t m_sideskirts; //0x03B5
		uint8_t m_exhaust; //0x03B6
		uint8_t m_frame; //0x03B7
		uint8_t m_grille; //0x03B8
		uint8_t m_hood; //0x03B9
		uint8_t m_fenders; //0x03BA
		uint8_t m_bullbars; //0x03BB
		uint8_t m_roof; //0x03BC
		char pad_03BD[3]; //0x03BD
		uint8_t m_ornaments; //0x03C0
		char pad_03C1[1]; //0x03C1
		uint8_t m_dail_design; //0x03C2
		uint8_t m_sunstrips; //0x03C3
		uint8_t m_seats; //0x03C4
		uint8_t m_steering_wheel; //0x03C5
		uint8_t m_column_shifter_levers; //0x03C6
		char pad_03C7[2]; //0x03C7
		uint8_t m_truck_beds; //0x03C9
		char pad_03CA[4]; //0x03CA
		uint8_t m_roll_cages; //0x03CE
		uint8_t m_skid_plate; //0x03CF
		uint8_t m_secondary_light_surrounds; //0x03D0
		uint8_t m_hood_accessories; //0x03D1
		uint8_t m_doors; //0x03D2
		uint8_t m_snorkel; //0x03D3
		uint8_t m_livery; //0x03D4
		char pad_03D5[1]; //0x03D5
		uint8_t m_engine; //0x03D6
		uint8_t m_brakes; //0x03D7
		uint8_t m_transmission; //0x03D8
		uint8_t m_horn; //0x03D9
		uint8_t m_suspension; //0x03DA
		uint8_t m_armor; //0x03DB
		char pad_03DC[1]; //0x03DC
		uint8_t m_turbo; //0x03DD
		char pad_03DE[3]; //0x03DE
		uint8_t m_xenon; //0x03E1
		uint8_t m_tire_design; //0x03E2
		char pad_03E3[16]; //0x03E3
		uint8_t m_truck_bed; //0x03F3
		char pad_03F4[5]; //0x03F4
		uint8_t m_wheel_color; //0x03F9
		char pad_03FA[5]; //0x03FA
		uint8_t m_window; //0x03FF
		char pad_0400[2]; //0x0400
		uint8_t m_neon_left; //0x0402
		uint8_t m_neon_right; //0x0403
		uint8_t m_neon_front; //0x0404
		uint8_t m_neon_rear; //0x0405
	}; //Size: 0x0406
	static_assert(sizeof(fwDrawData) == 0x406);
	template <typename T>
	class fwRefAwareBaseImpl : public T {
	private:
		void* m_ref; // 0x08
	};
	class fwRefAwareBase : public fwRefAwareBaseImpl<datBase> {};
	static_assert(sizeof(fwRefAwareBase) == 0x10);
	class fwExtension {
	public:
		virtual ~fwExtension() = default;
		virtual void unk_0x08() = 0;
		virtual void unk_0x10() = 0;
		virtual uint32_t get_id() = 0;
	}; //Size: 0x0008
	static_assert(sizeof(fwExtension) == 0x8);
	class fwExtensionContainer {
	public:
		fwExtension* m_entry; //0x0000
		fwExtensionContainer* m_next; //0x0008
	}; //Size: 0x0010
	static_assert(sizeof(fwExtensionContainer) == 0x10);
	class fwExtensibleBase : public fwRefAwareBase {
	public:
		virtual bool is_of_type(uint32_t hash) = 0;
		virtual uint32_t const& get_type() = 0;
		fwExtensionContainer* m_extension_container; // 0x0010
		void* m_extensible_unk; // 0x0018
		template <typename T>
		bool is_of_type() {
			static auto name = (typeid(T).name()) + 6; // Skip "class "
			static auto name_hash = joaat(name);
			return is_of_type(name_hash);
		}
	}; //Size: 0x0020
	static_assert(sizeof(fwExtensibleBase) == 0x20);
#pragma pack(push, 1)
	class fwEntity : public fwExtensibleBase {
	public:
		class CBaseModelInfo* m_model_info; //0x0020
		char pad_0028; //0x0028
		uint8_t m_entity_type;
		char pad_002A[2]; //0x002A
		uint8_t m_invisible; //0x002C
		char pad_002D[3]; //0x002D
		class CNavigation* m_navigation; //0x0030
		char pad_0038[16]; //0x0038
		class fwDrawData* m_draw_data; //0x0048
		char pad_0050[16]; //0x0050
		struct vector3 m_right; //0x0060
		char pad_006C[4]; //0x006C
		struct vector3 m_forward; //0x0070
		char pad_007C[4]; //0x007C
		struct vector3 m_up; //0x0080
		char pad_008C[4]; //0x008C
		struct vector3 m_position; //0x0090
		char pad_009C[4]; //0x009C
		uint64_t unk_00A0; //0x00A0
		uint32_t unk_00A8; //0x00A8
		uint32_t unk_00AC; //0x00AC
		uint32_t unk_00B0; //0x00B0
		char pad_00B4[4]; //0x00B4
		uint8_t unk_00B8; //0x00B8
	}; //Size: 0x00B9
	static_assert(sizeof(fwEntity) == 0xB9);
#pragma pack(pop)
	class datBitBuffer {
	public:
		datBitBuffer(uint8_t* data, uint32_t size) {
			m_data = data;
			m_bitOffset = 0;
			m_maxBit = size * 8;
			m_bitsRead = 0;
			m_curBit = 0;
			m_highestBitsRead = 0;
			m_flagBits = 0;
		}
		uint32_t GetPosition() {
			return m_bitsRead;
		}
		bool Seek(uint32_t bits) {
			if (bits >= 0) {
				uint32_t length = (m_flagBits & 1) ? m_maxBit : m_curBit;
				if (bits <= length) {
					m_bitsRead = bits;
				}
			}
			return false;
		}
		uint64_t ReadBits(size_t numBits) {
			auto const totalBits = (m_flagBits & 1) ? m_maxBit : m_curBit;
			if ((m_flagBits & 2) || m_bitsRead + numBits > totalBits)
				return 0;
			auto const bufPos = m_bitsRead + m_bitOffset;
			auto const initialBitOffset = bufPos & 0b111;
			auto const start = &m_data[bufPos / 8];
			auto const next = &start[1];
			auto result = (start[0] << initialBitOffset) & 0xff;
			for (auto i = 0; i < (numBits - 1) / 8; i++) {
				result <<= 8;
				result |= next[i] << initialBitOffset;
			}
			if (initialBitOffset)
				result |= next[0] >> (8 - initialBitOffset);
			m_bitsRead += numBits;
			if (m_bitsRead > m_highestBitsRead)
				m_highestBitsRead = m_bitsRead;
			return result >> ((8 - numBits) % 8);
		}
		int GetDataLength() {
			int leftoverBit = (m_curBit % 8) ? 1 : 0;
			return (m_curBit / 8) + leftoverBit;
		}
		/*bool WriteBool(bool integer) {
			return g_pointers.m_writeBitbufDword(this, integer, 1);
		}
		bool ReadBool(bool* integer) {
			return g_pointers.m_readBitbufBool(this, integer, 1);
		}
		bool ReadPeerId(uint64_t* integer) {
			auto senderPeerId = this->ReadBits(32); senderPeerId |= this->ReadBits(32) << 32;
			return senderPeerId != NULL;
		}
		bool ReadString(char* string, int bits) {
			return g_pointers.m_readBitbufString(this, string, bits);
		}
		bool WriteByte(uint8_t integer, int bits) {
			return g_pointers.m_writeBitbufDword(this, integer, bits);
		}
		bool ReadByte(uint8_t* integer, int bits) {
			uint32_t read;
			if (g_pointers.m_readBitbufDword(this, &read, bits)) {
				*integer = read;
				return true;
			}
			return false;
		}
		bool WriteWord(uint16_t integer, int bits) {
			return g_pointers.m_writeBitbufDword(this, integer, bits);
		}
		bool ReadWord(uint16_t* integer, int bits) {
			uint32_t read;
			if (g_pointers.m_readBitbufDword(this, &read, bits)) {
				*integer = read;
				return true;
			}
			return false;
		}
		bool WriteDword(uint32_t integer, int bits) {
			return g_pointers.m_writeBitbufDword(this, integer, bits);
		}
		bool ReadDword(uint32_t* integer, int bits) {
			return g_pointers.m_readBitbufDword(this, integer, bits);
		}
		bool WriteInt32(int32_t integer, int bits) {
			return g_pointers.m_writeBitbufInt32(this, integer, bits);
		}
		bool ReadInt32(int32_t* integer, int bits) {
			int32_t v8;
			int32_t v9;
			if (ReadDword((uint32_t*)&v8, 1u) && ReadDword((uint32_t*)&v9, bits - 1)) {
				*integer = v8 + (v9 ^ -v8);
				return true;
			}
			return false;
		}
		bool WriteQWord(uint64_t integer, int bits) {
			return g_pointers.m_writeBitbufQword(this, integer, bits);
		}
		bool ReadQWord(uint64_t* integer, int bits) {
			if (bits <= 32) {
				uint32_t v10;
				if (ReadDword(&v10, bits)) {
					*integer = v10;
					return true;
				}
			}
			else {
				uint32_t v10, v11;
				if (ReadDword(&v11, 32u) && ReadDword(&v10, bits - 32u)) {
					*integer = v11 | ((uint64_t)v10 << 32);
					return true;
				}
			}
			return false;
		}
		bool WriteInt64(int64_t integer, int bits) {
			return g_pointers.m_writeBitbufInt64(this, integer, bits);
		}
		bool ReadInt64(int64_t* integer, int bits) {
			uint32_t v8;
			uint64_t v9;
			if (ReadDword(&v8, 1u) && ReadQWord(&v9, bits - 1)) {
				*integer = v8 + (v9 ^ -(int64_t)v8);
				return true;
			}
			return false;
		}
		bool WriteArray(uint8_t* array, int size) {
			return g_pointers.m_writeBitbufArray(this, array, size, 0);
		}
		bool ReadArray(PVOID array, int size) {
			return g_pointers.m_readBitbufArray(this, array, size, 0);
		}*/
	public:
		uint8_t* m_data; //0x0000
		uint32_t m_bitOffset; //0x0008
		uint32_t m_maxBit; //0x000C
		uint32_t m_bitsRead; //0x0010
		uint32_t m_curBit; //0x0014
		uint32_t m_highestBitsRead; //0x0018
		uint8_t m_flagBits; //0x001C
	};
	class netGameEvent {
	public:
		virtual ~netGameEvent() = default;
		virtual const char* get_name() { return 0; };
		virtual bool is_in_scope(netPlayer* player) { return 0; };
		virtual bool time_to_resend(std::uint32_t time) { return 0; };
		virtual bool can_change_scope() { return 0; };
		virtual void prepare_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual void handle_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual bool decide(netPlayer* source_player, netPlayer* target_player) { return 0; };
		virtual void prepare_reply(datBitBuffer* buffer, netPlayer* reply_player) {};
		virtual void handle_reply(datBitBuffer* buffer, netPlayer* souce_player) {};
		virtual void prepare_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
		virtual void handle_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
	private:
		virtual void unk_0x60() {};
		virtual void unk_0x68() {};
		virtual void unk_0x70() {};
		virtual void unk_0x78() {};
	public:
		virtual bool operator==(netGameEvent const& other) { return 0; };
		virtual bool operator!=(netGameEvent const& other) { return 0; };
		virtual bool must_persist() { return 0; };
		virtual bool must_persist_when_out_of_scope() { return 0; };
		virtual bool has_timed_out() { return 0; };
		std::uint16_t m_id;          // 0x08
		bool m_requires_reply;       // 0x0A
	private:
		char m_padding1[0x05];       // 0x0B
	public:
		netPlayer* m_source_player;  // 0x10
		netPlayer* m_target_player;  // 0x18
		std::uint32_t m_resend_time; // 0x20
	private:
		std::uint16_t m_0x24;        // 0x24
		std::uint8_t m_0x26;         // 0x26
		std::uint8_t m_0x27;         // 0x27
		std::uint32_t m_0x28;        // 0x28
		char m_padding2[0x04];
	};
	template <typename T>
	class atArray {
	public:
		T* begin() { return m_data; }
		T* end() { return m_data + m_size; }
		const T* begin() const { return m_data; }
		const T* end() const { return m_data + m_size; }
		T* data() { return m_data; }
		const T* data() const { return m_data; }
		std::uint16_t size() const { return m_size; }
		std::uint16_t capacity() const { return m_capacity; }
		T& operator[](std::uint16_t index) { return m_data[index]; }
		const T& operator[](std::uint16_t index) const { return m_data[index]; }
	private:
		T* m_data;
		std::uint16_t m_size;
		std::uint16_t m_capacity;
	};
	class pgBase {
	public:
		virtual ~pgBase() = default;
	private:
		void* m_pgunk;
	};
	class scrProgram : public pgBase {
	public:
		std::uint8_t** m_code_blocks;  // 0x10
		std::uint32_t m_hash;          // 0x18
		std::uint32_t m_code_size;     // 0x1C
		std::uint32_t m_arg_count;     // 0x20
		std::uint32_t m_local_count;   // 0x24
		std::uint32_t m_global_count;  // 0x28
		std::uint32_t m_native_count;  // 0x2C
		void* m_local_data;            // 0x30
		std::int64_t** m_global_data;  // 0x38
		void** m_native_entrypoints;   // 0x40
		char m_padding6[0x10];         // 0x48
		std::uint32_t m_name_hash;     // 0x58
		char m_padding7[0x04];         // 0x5C
		const char* m_name;            // 0x60
		const char** m_strings_data;   // 0x68
		std::uint32_t m_strings_count; // 0x70
		char m_padding8[0x0C];         // 0x74
		bool is_valid() const {
			return m_code_size != 0;
		}
		std::uint32_t get_num_code_pages() const {
			return (m_code_size + 0x3FFF) >> 14;
		}
		std::uint32_t get_code_page_size(std::uint32_t page) const {
			auto num = get_num_code_pages();
			if (page < num) {
				if (page == num - 1)
					return m_code_size & 0x3FFF;
				return 0x4000;
			}
			return 0;
		}
		std::uint32_t get_full_code_size() const {
			auto numPages = get_num_code_pages();
			if (!numPages)
				return 0;
			if (numPages == 1)
				--numPages;
			return (numPages * 0x4000) + (m_code_size & 0x3FFF);
		}
		std::uint8_t* get_code_page(std::uint32_t page) const {
			return m_code_blocks[page];
		}
		std::uint8_t* get_code_address(std::uint32_t index) const {
			if (index < m_code_size)
				return &m_code_blocks[index >> 14][index & 0x3FFF];
			return nullptr;
		}
		const char* get_string(std::uint32_t index) const {
			if (index < m_strings_count)
				return &m_strings_data[index >> 14][index & 0x3FFF];
			return nullptr;
		}
		void** get_address_of_native_entrypoint(void* entrypoint) {
			for (std::uint32_t i = 0; i < m_native_count; ++i)
				if (m_native_entrypoints[i] == entrypoint)
					return m_native_entrypoints + i;
			return nullptr;
		}
	};
	class scrProgramTableEntry {
	public:
		scrProgram* m_program;     // 0x00
		char m_Pad1[0x04];         // 0x08
		uint32_t m_hash;           // 0x0C
	};
	class scrProgramTable {
	public:
		scrProgramTableEntry* m_data;    // 0x00
		char m_padding[0x10];            // 0x08
		std::uint32_t m_size;            // 0x18
		std::list<uint32_t> all_script_hashes() {
			std::list<uint32_t> hash;
			for (uint32_t i = 0; i < m_size; ++i)
				if (m_data[i].m_program != nullptr && m_data[i].m_program->m_name != nullptr)
					hash.push_back(m_data[i].m_hash);
			return hash;
		}
		std::list<std::string> all_script_names() {
			std::list<std::string> hash;
			for (uint32_t i = 0; i < m_size; ++i)
				if (m_data[i].m_program != nullptr && m_data[i].m_program->m_name != nullptr)
					hash.push_back(m_data[i].m_program->m_name);
			return hash;
		}
		scrProgram* find_script(uint32_t hash) {
			for (std::uint32_t i = 0; i < m_size; ++i)
				if (m_data[i].m_hash == hash)
					return m_data[i].m_program;
			return nullptr;
		}
		scrProgramTableEntry* begin() {
			return m_data;
		}
		scrProgramTableEntry* end() {
			return m_data + m_size;
		}
	};
	//Thread
	//Thread State
	enum class eThreadState : uint32_t {
		running,
		sleeping,
		killed,
		paused,
		breakpoint
	};
	//Thread
	class scrThreadContext {
	public:
		uint32_t m_thread_id; //0x0000
		uint32_t m_script_hash; //0x0004
		eThreadState m_state; //0x0008
		uint32_t m_instruction_pointer; //0x000C
		uint32_t m_frame_pointer; //0x0010
		uint32_t m_stack_pointer; //0x0014
		float m_timer_a; //0x0018
		float m_timer_b; //0x001C
		float m_timer_c; //0x0020
		char pad_0024[40]; //0x0024
		uint32_t m_stack_size; //0x004C
		uint32_t m_catch_instruction_pointer; //0x0050
		char pad_0054[84]; //0x0054
	}; //Size: 0x00A8
	static_assert(sizeof(scrThreadContext) == 0xA8);
	class scriptHandler;
	class scriptHandlerNetComponent;
	class tlsContext {
	public:
		char m_padding1[192]; // 0x0000
		void* m_tls_entry; // 0x00C0
		class sysMemAllocator* m_allocator; //0x00C8
		char pad_00D0[1912]; //0x00D0
		class scrThread* m_script_thread; //0x0848
		bool m_is_script_thread_active; //0x00850
		static tlsContext* get() { return *(tlsContext**)(__readgsqword(0x58)); }
		static tlsContext** getPointer() { return (tlsContext**)(__readgsqword(0x58)); }
	}; //Size: 0x0850
	static_assert(sizeof(tlsContext) == 0x858);
	class scrThread {
	public:
		virtual ~scrThread();                   //0 (0x00)
		virtual void reset(uint32_t script_hash, void* args, uint32_t arg_count);      //1 (0x08)
		virtual eThreadState run();                //2 (0x10)
		virtual eThreadState tick(uint32_t ops_to_execute);          //3 (0x18)
		virtual void kill();                 //4 (0x20)
		static scrThread** getPointer() {
			auto tls = uintptr_t(*(uintptr_t*)__readgsqword(0x58));
			return reinterpret_cast<scrThread**>(tls + offsetof(rage::tlsContext, m_script_thread));
		}
		static scrThread* get() {
			return rage::tlsContext::get()->m_script_thread;
		}
	public:
		scrThreadContext m_context; //0x0000
		void* m_stack; //0x00A8
		uint32_t unk_00B0; //0x00B0
		uint32_t m_arg_size; //0x00B4
		uint32_t m_arg_loc; //0x00B8
		uint32_t unk_00BC; //0x00BC - Some sort of arg
		const char* m_exit_message; //0x00C0
		uint32_t unk_00C8; //0x00C8
		char m_name[64]; //0x00D0
		scriptHandler* m_handler; //0x0110
		scriptHandlerNetComponent* m_net_component; //0x0118
	}; //Size: 0x0128
	static_assert(sizeof(scrThread) == 0x128);
	class sysMemAllocator {
	public:
		virtual ~sysMemAllocator() = 0;
		virtual void SetQuitOnFail(bool) = 0;
		virtual void* Allocate(size_t size, size_t align, int subAllocator) = 0;
		virtual void* TryAllocate(size_t size, size_t align, int subAllocator) = 0;
		virtual void Free(void* pointer) = 0;
		virtual void TryFree(void* pointer) = 0;
		virtual void Resize(void* pointer, size_t size) = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) const = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) = 0;
		virtual sysMemAllocator* GetPointerOwner(void* pointer) = 0;
		virtual size_t GetSize(void* pointer) const = 0;
		virtual size_t GetMemoryUsed(int memoryBucket) = 0;
		virtual size_t GetMemoryAvailable() = 0;
	public:
		static sysMemAllocator* UpdateAllocatorValue() {
			auto tls = rage::tlsContext::get();
			auto gtaTlsEntry = *reinterpret_cast<sysMemAllocator**>(uintptr_t(tls) + offsetof(rage::tlsContext, m_allocator));
			if (!gtaTlsEntry)
				tls->m_allocator = gtaTlsEntry;
			tls->m_tls_entry = (void*)gtaTlsEntry;
			return gtaTlsEntry;
		}
		static sysMemAllocator* get() {
			auto allocValue = rage::tlsContext::get()->m_allocator;
			if (!allocValue)
				allocValue = UpdateAllocatorValue();
			return allocValue;
		}
		static sysMemAllocator** getPointer() {
			auto tls = uintptr_t(*(uintptr_t*)__readgsqword(0x58));
			return reinterpret_cast<sysMemAllocator**>(tls + 0xC8);
		}
		static void* getEntry() {
			auto tls = uintptr_t(*(uintptr_t*)__readgsqword(0x58));
			return *reinterpret_cast<void**>(tls + offsetof(rage::tlsContext, m_tls_entry));
		}
		static void** getEntryPointer() {
			auto tls = uintptr_t(*(uintptr_t*)__readgsqword(0x58));
			return reinterpret_cast<void**>(tls + offsetof(rage::tlsContext, m_tls_entry));
		}
	};
	class scriptIdBase {
	public:
		virtual ~scriptIdBase() = default;                            // 0 (0x00)
		//Assumes the script thread's identity.
		virtual void assume_thread_identity(scrThread*) {};           // 1 (0x08)
		//Returns whether the hash of the script id is valid.
		virtual bool is_valid() {};                                   // 2 (0x10)
		//Gets the hash of the script id.
		virtual uint32_t* get_hash(uint32_t* out) {};                 // 3 (0x18)
		//Gets an unknown value from the script id.
		virtual std::uint32_t* get_hash2(std::uint32_t* out) {};      // 4 (0x20)
		//Gets the name of the script id.
		virtual const char* get_name() {};                            // 5 (0x28)
		//Serializes the script id from the buffer.
		virtual void deserialize(datBitBuffer* buffer) {};            // 6 (0x30)
		//Serializes the script id to the buffer.
		virtual void serialize(datBitBuffer* buffer) {};              // 7 (0x38)
		//Calculates some information with the position hash & instance id.
		virtual std::uint32_t _0x40() {};                             // 8 (0x40)
		//Calls _0x40 and returns it's value added to another value.
		virtual std::uint32_t _0x48() {};                             // 9 (0x48)
		//Logs some information about the script id.
		virtual void log_information(void* logger) {}; // 10 (0x50)
		//Copies the information of other to this object.
		virtual void copy_data(scriptIdBase* other) {}                // 11 (0x58)
		//Returns whether the other script id is equal.
		virtual bool operator==(scriptIdBase*) {};                    // 12 (0x60)
		virtual bool _0x68(void*) {};                                 // 13 (0x68)
	};
	//Id
	class scriptId : public scriptIdBase {
	public:
		uint32_t m_hash;          // 0x08
		char m_name[0x20];        // 0x0C
	};
	class scriptResource {
	public:
		virtual ~scriptResource() = default;
	};
	class scriptHandler {
	public:
		class atDScriptObjectNode : public atDNode<scriptHandlerObject*> {};
	public:
		virtual ~scriptHandler() = default;                                                                   //  0 (0x00)
		virtual bool _0x08() = 0;                                                                             //  1 (0x08)
		virtual void _0x10() = 0;                                                                             //  2 (0x10)
		virtual void cleanup_objects() = 0;                                                                   //  3 (0x18)
		virtual scriptId* _0x20() = 0;                                                                        //  4 (0x20)
		virtual scriptId* get_id() = 0;                                                                       //  5 (0x28)
		//Returns whether the script handler belongs to a networked script.
		virtual bool is_networked() = 0;                                                                      //  6 (0x30)
		//Initializes the network component for the script handler.
		virtual void init_net_component() = 0;                                                                //  7 (0x38)
		//Deletes the script handler's network component, if it exists.
		virtual void reset_net_component() = 0;                                                               //  8 (0x40)
		//Destroys the script handler.
		virtual bool destroy() = 0;                                                                           //  9 (0x48)
		//Adds the object to the script handler's list of objects.
		virtual void add_object(scriptHandlerObject*, bool is_network, bool is_network_and_scriptcheck) = 0; // 10 (0x50)
		//Something related to reservations.
		virtual void _0x58(void*) = 0;                                                                        // 11 (0x58)
		virtual void register_resource(scriptResource*, void*) = 0;                                           // 12 (0x60)
		virtual void _0x68() = 0;                                                                             // 13 (0x68)
		virtual void _0x70() = 0;                                                                             // 14 (0x70)
		virtual void _0x78() = 0;                                                                             // 15 (0x78)
		virtual void _0x80() = 0;                                                                             // 16 (0x80)
		virtual void _0x88() = 0;                                                                             // 17 (0x88)
		virtual void _0x90() = 0;                                                                             // 18 (0x90)
		virtual void _0x98() = 0;                                                                             // 19 (0x98)
	public:
		void* m_0x08;                                // 0x08
		void* m_0x10;                                // 0x10
		scrThread* m_script_thread;                  // 0x18
		atDList<atDScriptObjectNode> m_objects;      // 0x20
		scriptResource* m_resource_list_head;        // 0x30
		scriptResource* m_resource_list_tail;        // 0x38
		void* m_0x40;                                // 0x40
		scriptHandlerNetComponent* m_net_component;  // 0x48
		std::uint32_t m_0x50;                        // 0x50
		std::uint32_t m_0x54;                        // 0x54
		std::uint32_t m_0x58;                        // 0x58
		std::uint32_t m_0x60;                        // 0x5C
	};
	class scriptHandlerNetComponent {
	public:
		virtual ~scriptHandlerNetComponent() = default;
	public:
		scriptHandler* m_script_handler; // 0x08
	};
	class rlSessionInfo {
	public:
		uint64_t m_rockstar_id; //0x0000
		uint64_t m_session_token; //0x0008
		rlGamerInfoBase m_net_peer_address; //0x0010
	};
	static_assert(sizeof(rlSessionInfo) == 0x70);
	class rlSessionByGamerTaskResult {
	public:
		rlSessionByGamerTaskResult() : m_gamer_handle(NULL) {}
		rlGamerHandle m_gamer_handle;
		rlSessionInfo m_session_info;
	};
	class rlPresenceEventInviteAccepted {
	public:
		rlPresenceEventInviteAccepted(rlGamerInfo& gamerInfo, rlSessionInfo& sessionInfo, rlGamerHandle& gamerHandle) : m_gamer_info(gamerInfo), m_session_info(sessionInfo), m_gamer_handle(gamerHandle) {
			m_self = this;
		}

		void* m_vft; //0x0000
		rlPresenceEventInviteAccepted* m_self; //0x0008
		rlGamerInfo m_gamer_info; //0x0010
		rlSessionInfo m_session_info; //0x00A8
		rlGamerHandle m_gamer_handle; //0x0118
	};
	class netSyncTree {
	public:
		char pad_0000[48]; //0x0000
		class netSyncTreeNode* m_sync_tree_node; //0x0030
	}; //Size: 0x0038
	class netSyncTreeNode {
	public:
		char pad_0000[192]; //0x0000
		uint32_t m_player_model; //0x00C0
		uint32_t m_ped_model; //0x00C4
		uint32_t m_vehicle_model; //0x00C8
		char pad_00CC[84]; //0x00CC
		uint32_t m_pickup_model; //0x0120
		char pad_0124[44]; //0x0124
		uint32_t m_object_model; //0x0150
		char pad_0154[692]; //0x0154
	}; //Size: 0x0408
	class netObject {
	public:
		int16_t m_object_type; //0x0008
		int16_t m_object_id; //0x000A
		char pad_000C[61]; //0x000C
		int8_t m_owner_id; //0x0049
		int8_t m_control_id; //0x004A
		int8_t m_next_owner_id; //0x004B
		bool m_is_remote; //0x004C
		bool m_wants_to_delete; //0x004D
		char pad_004E[1]; //0x004E
		bool m_should_not_be_deleted; //0x004F
		char pad_0050[32]; //0x0050
		uint32_t m_players_acked; //0x0070
		char pad_0074[116]; //0x0074

		virtual ~netObject() = 0;
		virtual void mov1() = 0;
		virtual void mov2() = 0;
		virtual void m_8() = 0;
		virtual void m_10() = 0;
		virtual void m_18() = 0;
		virtual void* m_20() = 0;
		virtual void m_28() = 0;
		virtual netSyncTree* GetSyncTree() = 0;
		virtual void m_38() = 0;
		virtual void m_40() = 0;
		virtual void m_48() = 0;
		virtual void m_50() = 0;
		virtual void m_58() = 0;
		virtual void m_60() = 0;
		virtual void m_68() = 0;
		virtual void m_70() = 0;
		virtual void m_78() = 0;
		virtual CObject* GetGameObject() = 0;
		virtual void m_88() = 0;
		virtual void m_90() = 0;
		virtual void m_98() = 0;
		virtual int GetObjectFlags() = 0;
		virtual void m_A8() = 0;
		virtual void m_B0() = 0;
		virtual void m_B8() = 0;
		virtual void m_C0() = 0;
		virtual void m_C8() = 0;
		virtual int GetSyncFrequency() = 0;
		virtual void m_D8() = 0;
		virtual void m_E0() = 0;
		virtual void m_E8() = 0;
		virtual void m_F0() = 0;
		virtual void m_F8() = 0;
		virtual void Update() = 0;
		virtual bool m_108_1604() = 0; // added in 1604
		virtual void m_108() = 0;
		virtual void m_110() = 0;
		virtual void m_118() = 0;
		virtual void m_120() = 0;
		virtual void m_128() = 0;
		virtual void m_130() = 0;
		virtual void m_138() = 0;
		virtual void m_140() = 0;
		virtual void m_148() = 0;
		virtual void m_150() = 0;
		virtual bool m_158(void* player, int type, int* outReason) = 0;
		virtual void m_160() = 0;
		virtual bool m_168(int* outReason) = 0;
		virtual void m_170() = 0;
		virtual void m_178() = 0;
		virtual void m_180() = 0;
		virtual void m_188() = 0;
		virtual void m_190() = 0;
		virtual void m_198() = 0;
		virtual void m_1A0() = 0;
		virtual void m_1A8() = 0;
		virtual void m_1B0() = 0;
		virtual void m_1B8() = 0;
		virtual void m_1C0() = 0;
		virtual void m_1C8() = 0;
		virtual void m_1D0() = 0;
		virtual void m_1D8() = 0;
		virtual void m_1E0() = 0;
		virtual void m_1E8() = 0;
		virtual void m_1F0() = 0;
		virtual void m_1F8() = 0;
		virtual void m_200() = 0;
		virtual void m_208() = 0;
		virtual void m_210() = 0;
		virtual void m_218() = 0;
		virtual void m_220() = 0;
		virtual void m_228() = 0;
		virtual void m_230() = 0;
		virtual void m_238() = 0;
		virtual void m_240() = 0;
		virtual void m_248() = 0;
		virtual void m_250() = 0;
		virtual void m_258() = 0;
		virtual void m_260() = 0;
		virtual void m_268() = 0;
		virtual void m_270() = 0;
		virtual void m_278() = 0;
		virtual void m_280() = 0;
		virtual void m_288() = 0;
		virtual void m_290() = 0;
		virtual void m_298() = 0;
		virtual void m_2A0() = 0;
		virtual void m_2A8() = 0;
		virtual void m_2B0() = 0;
		virtual void m_2B8() = 0;
		virtual void m_2C0() = 0;
		virtual void m_2C8() = 0;
		virtual void m_2D0() = 0;
		virtual void m_2D8() = 0;
		virtual void m_2E0() = 0;
		virtual void m_2E8() = 0;
		virtual void m_2F0() = 0;
		virtual void m_2F8() = 0;
		virtual void m_300() = 0;
		virtual void m_308() = 0;
		virtual void m_310() = 0;
		virtual void m_318() = 0;
		virtual void m_320() = 0;
		virtual void UpdatePendingVisibilityChanges() = 0;
	};
	static_assert(sizeof(netObject) == 0xE8);
	class netObjectMgrBase {
	public:
		class atDNetObjectNode : public atDNode<netObject*> {};
	public:
		virtual ~netObjectMgrBase() = default;
		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(bool) = 0;
		virtual void AddEntity(void*, void*) = 0;
		virtual void UnregisterNetworkObject_(void* unk, bool force) = 0;
		virtual void UnregisterNetworkObject(netObject* object, int reason, bool force1, bool force2) = 0;
		virtual void ChangeOwner(netObject* object, CNetGamePlayer* player, int migrationType) = 0;
		virtual void HandleJoiningPlayer(CNetGamePlayer* player) = 0;
		virtual void HandleLeavingPlayer(CNetGamePlayer* player) = 0;
		virtual void _0x50(CNetGamePlayer* player) = 0;
		virtual void _0x58() = 0;
		virtual void RegisterNetworkObject(netObject* object) = 0;
		virtual void PackCloneCreate(netObject* object, CNetGamePlayer* player, datBitBuffer* buffer) = 0;
		virtual bool PackCloneRemove(netObject* object, CNetGamePlayer* player, bool) = 0;
		virtual void _0x78(netObject* object, void*) = 0;
		virtual void _0x80() = 0;
		virtual void _0x88() = 0;
		virtual const char* _0x90(int) = 0;
		virtual bool HandleCloneCreate(CNetGamePlayer* source, CNetGamePlayer* target, std::uint16_t object_type, std::uint16_t object_id, uint16_t object_flags, void*, std::uint32_t timestamp) = 0;
		virtual void HandleCloneCreateAck(CNetGamePlayer* source, CNetGamePlayer* target, std::uint16_t object_flags, uint32_t ack_code) = 0;
		virtual int HandleCloneSync(CNetGamePlayer* source, CNetGamePlayer* target, std::uint16_t object_type, std::uint16_t object_id, void*, std::uint16_t, std::uint32_t timestamp) = 0;
		virtual void HandleCloneSyncAck(CNetGamePlayer* source, CNetGamePlayer* target, void*, std::uint16_t objectId, uint32_t ack_code) = 0;
		virtual void HandleCloneRemove(CNetGamePlayer* source, CNetGamePlayer* target, std::uint16_t object_id, int) = 0;
		virtual void HandleCloneRemoveAck(CNetGamePlayer* source, CNetGamePlayer* target, std::uint16_t object_id, uint32_t ack_code) = 0;
		virtual void _0xC8() = 0;
	public:
		atDList<atDNetObjectNode> m_objects_owned_by_player[32];
	};
	#pragma pack(push, 8)
	class netConnectionPeer {
	public:
		netSocketAddress m_internal_address; //0x0000
		netSocketAddress m_external_address; //0x0008
		uint64_t m_peer_id; //0x0010
		uint32_t unk_0018; //0x0018
		uint16_t unk_001C; //0x001C
		uint8_t  m_platform; //0x001E
	}; //Size: 0x0020
	static_assert(sizeof(netConnectionPeer) == 0x20);
	#pragma pack(pop)
	namespace netConnection {
		#pragma pack(push, 8)
		class InFrame {
		public:
			virtual ~InFrame() = default;
			virtual void Destroy() = 0;
			virtual uint32_t GetId() = 0;
			virtual uint32_t GetPayloadSize() = 0;
			virtual bool IsChanneled() = 0;

			char pad_0008[56]; //0x0008
			uint32_t m_msg_id; //0x0040
			uint32_t m_connection_identifier; //0x0044
			InFrame* m_this; //0x0048
			uint32_t m_platform_data; //0x0050
			class netConnectionPeer m_net_connection_peer; //0x0054
			uint32_t m_length; //0x0078
			char pad_007C[4]; //0x007C
			void* m_data; //0x0080
			uint32_t unk_0088; //0x0088
			uint16_t unk_008C; //0x008C
			uint64_t unk_0090; //0x0090
			char pad_0098[32]; //0x0098
		}; //Size=0x00B8
		static_assert(sizeof(InFrame) == 0xB8);
		#pragma pack(pop)
	}
	class CEntity : public fwEntity {
	public:
		char pad_00B9[7]; //0x00B9
		uint32_t unk_00C0; //0x00C0
		uint32_t unk_00C4; //0x00C4
		uint32_t unk_00C8; //0x00C8
		uint32_t unk_00CC; //0x00CC
	}; //Size: 0x00D0
	static_assert(sizeof(CEntity) == 0xD0);
	class CDynamicEntity : public CEntity {
	public:
		class netObject* m_net_object; //0x00D0
		char pad_00D8[16]; //0x00D8
		uint64_t unk_00E8; //0x00E8
	}; //Size: 0x00F0
	static_assert(sizeof(CDynamicEntity) == 0xF0);
#pragma pack(push, 1)
	class CPhysical : public CDynamicEntity {
	public:
		char pad_00F0[144]; //0x00F0
		uint64_t unk_0180; //0x0180
		uint32_t m_damage_bits; //0x0188
		uint8_t m_hostility; //0x018C
		char pad_018D[3]; //0x018D
		uint8_t unk_0190; //0x0190
		char pad_0191[3]; //0x0191
		uint32_t unk_0194; //0x0194
		char pad_0198[232]; //0x0198
		float m_health; //0x0280
		float m_maxhealth; //0x0284
		uint64_t unk_0280; //0x0280
		char pad_02B0[72]; //0x0290
		uint64_t unk_02D8; //0x02D8
		uint64_t unk_02E0; //0x02E0
		uint32_t unk_02E8; //0x02E8
	}; //Size: 0x02EC
	static_assert(sizeof(CPhysical) == 0x2EC);
#pragma pack(pop)
}
#pragma pack(push, 1)
class FriendInfo {
public:
	char m_name[20]; //0x0000
	char pad_0014[36]; //0x0014
	uint64_t m_rockstar_id; //0x0038
	uint8_t unk_0x40; //0x0040
	char pad_0041[3]; //0x0041
	uint32_t m_friend_state; //0x0044
	char pad_0048[304]; //0x0048
	uint32_t m_is_joinable; //0x0178
	char pad_017C[4]; //0x017C
}; //Size: 0x0180
static_assert(sizeof(FriendInfo) == 0x180);
#pragma pack(pop)
class FriendList {
public:
	class FriendInfo m_data[250]; //0x0000
}; //Size: 0x17700
static_assert(sizeof(FriendList) == 0x17700);
#pragma pack(push, 4)
class FriendRegistry {
public:
	uint32_t m_friend_count; //0x0000
	char pad_0004[8]; //0x0004
	class FriendList* m_friends_list; //0x000C
}; //Size: 0x0014
static_assert(sizeof(FriendRegistry) == 0x14);
#pragma pack(pop)
class CNonPhysicalPlayerData : public rage::nonPhysicalPlayerDataBase {
public:
	std::int32_t  m_bubble_id; // 0x08
	std::int32_t  m_player_id; // 0x0C
	rage::vector3 m_position;  // 0x10
};
class CBaseModelInfo {
public:
	char pad_0000[0x18]; //0x0000
	uint32_t m_model; //0x0018
	char pad_001C[0x81]; //0x001C
	BYTE m_model_type; //0x009D
	char pad_009D[0x2A2]; //0x009E
	int32_t m_handling_type; //0x0340
}; //Size: 0x0344
static_assert(sizeof(CBaseModelInfo) == 0x344);
class CNavigation {
public:
	char pad_0000[32]; //0x0000
	float m_heading; //0x0020
	float m_heading2; //0x0024
	char pad_0028[8]; //0x0028
	rage::vector3 m_rotation; //0x0030
	char pad_003C[20]; //0x003C
	rage::vector3 m_position; //0x0054
}; //Size: 0x0060
static_assert(sizeof(CNavigation) == 0x5C);
#pragma pack(push, 4)
class CHandlingData {
public:
	char pad_0000[8]; //0x0000
	uint32_t m_model_hash; //0x0008
	float m_mass; //0x000C
	float m_initial_drag_coeff; //0x0010
	float m_downforce_multiplier; //0x0014
	float m_popup_light_rotation; //0x0018
	char pad_001C[4]; //0x001C
	rage::vector3 m_centre_of_mass; //0x0020
	char pad_002C[4]; //0x002C
	rage::vector3 m_inertia_mult; //0x0030
	char pad_003C[4]; //0x003C
	float m_buoyancy; //0x0040
	float m_drive_bias_rear; //0x0044
	float m_drive_bias_front; //0x0048
	float m_acceleration; //0x004C
	uint8_t m_initial_drive_gears; //0x0050
	char pad_0051[3]; //0x0051
	float m_drive_inertia; //0x0054
	float m_upshift; //0x0058
	float m_downshift; //0x005C
	float m_initial_drive_force; //0x0060
	float m_drive_max_flat_velocity; //0x0064
	float m_initial_drive_max_flat_vel; //0x0068
	float m_brake_force; //0x006C
	char pad_0070[4]; //0x0070
	float m_brake_bias_front; //0x0074
	float m_brake_bias_rear; //0x0078
	float m_handbrake_force; //0x007C
	float m_steering_lock; //0x0080
	float m_steering_lock_ratio; //0x0084
	float m_traction_curve_max; //0x0088
	float m_traction_curve_lateral; //0x008C
	float m_traction_curve_min; //0x0090
	float m_traction_curve_ratio; //0x0094
	float m_curve_lateral; //0x0098
	float m_curve_lateral_ratio; //0x009C
	float m_traction_spring_delta_max; //0x00A0
	float m_traction_spring_delta_max_ratio; //0x00A4
	float m_low_speed_traction_loss_mult; //0x00A8
	float m_camber_stiffness; //0x00AC
	float m_traction_bias_front; //0x00B0
	float m_traction_bias_rear; //0x00B4
	float m_traction_loss_mult; //0x00B8
	float m_suspension_force; //0x00BC
	float m_suspension_comp_damp; //0x00C0
	float m_suspension_rebound_damp; //0x00C4
	float m_suspension_upper_limit; //0x00C8
	float m_suspension_lower_limit; //0x00CC
	float m_suspension_raise; //0x00D0
	float m_suspension_bias_front; //0x00D4
	float m_suspension_bias_rear; //0x00D8
	float m_anti_rollbar_force; //0x00DC
	float m_anti_rollbar_bias_front; //0x00E0
	float m_anti_rollbar_bias_rear; //0x00E4
	float m_roll_centre_height_front; //0x00E8
	float m_roll_centre_height_rear; //0x00EC
	float m_collision_damage_mult; //0x00F0
	float m_weapon_damamge_mult; //0x00F4
	float m_deformation_mult; //0x00F8
	float m_engine_damage_mult; //0x00FC
	float m_petrol_tank_volume; //0x0100
	float m_oil_volume; //0x0104
	char pad_0108[4]; //0x0108
	rage::vector3 m_seat_offset_dist; //0x010C
	uint32_t m_monetary_value; //0x0118
	char pad_011C[8]; //0x011C
	uint32_t m_model_flags; //0x0124
	uint32_t m_handling_flags; //0x0128
	uint32_t m_damage_flags; //0x012C
	char pad_0130[12]; //0x0130
	uint32_t m_ai_handling_hash; //0x013C
}; //Size: 0x0140
static_assert(sizeof(CHandlingData) == 0x140);
#pragma pack(pop)
#pragma pack(push, 1)
class CVehicle : public rage::CPhysical {
public:
	char gap30C[4];
	uint32_t dword310;
	uint32_t dword314;
	uint8_t m_boost_state; // 0x318
	char gap319[2];
	uint8_t m_boost_allow_recharge; // 0x31B
	uint16_t word31C;
	char gap31E[2];
	float m_boost; // 0x320
	float m_rocket_recharge_speed; // 0x324
	uint32_t dword328;
	uint8_t byte32C;
	char gap32D[3];
	uint8_t byte330;
	char gap331[3];
	uint64_t qword334;
	uint32_t dword33C;
	uint8_t byte340;
	char gap341[3];
	uint32_t dword344;
	uint8_t byte348;
	char gap349[3];
	uint64_t qword34C;
	uint64_t qword354;
	uint64_t qword35C;
	uint64_t qword364;
	uint32_t dword36C;
	uint32_t dword370;
	uint8_t byte374;
	uint16_t word375;
	uint8_t byte377;
	uint64_t qword378;
	uint64_t qword380;
	uint64_t qword388;
	uint32_t dword390;
	uint32_t dword394;
	uint8_t byte398;
	char gap399[3];
	uint64_t qword39C;
	uint64_t qword3A4;
	char gap3AC[4];
	float m_jump_boost_charge; // 0x3B0
	uint8_t byte3B4;
	char gap3B5[3];
	uint64_t qword3B8;
	uint32_t dword3C0;
	uint32_t dword3C4;
	char gap3C8[8];
	uint16_t oword3D0;
	char gap3D2[30];
	uint16_t oword3F0;
	char gap3F2[14];
	uint32_t dword400;
	uint64_t qword404;
	char gap40C[4];
	uint32_t dword410;
	uint64_t qword414;
	char gap41C[4];
	uint64_t qword420;
	uint32_t dword428;
	uint32_t dword42C;
	char gap430[1032];
	uint64_t qword838;
	float m_body_health; // 0x840
	float m_petrol_tank_health; // 0x844
	char gap848[12];
	float float854;
	char gap858[176];
	float m_engine_health; // 0x908
	char gap90C[44];
	CHandlingData* m_handling_data; // 0x938
	char gap940[2];
	uint8_t m_is_drivable; //0x0942
	uint8_t m_tyres_can_burst; //0x0943
	uint8_t m_deform_god; //0x0944
	char gap945[6];
	uint8_t byte94B;
	char gap94C;
	uint8_t byte94D;
	char gap94E;
	uint8_t byte94F;
	char gap950[3];
	uint8_t byte953;
	uint8_t byte954;
	char gap955;
	uint8_t byte956;
	uint8_t byte957;
	char gap958[2];
	uint8_t byte95A;
	char gap95B[9];
	uint64_t qword964;
	char gap96C[4];
	uint64_t qword970;
	uint64_t qword978;
	char gap980[8];
	uint64_t qword988;
	uint16_t word990;
	uint32_t dword992;
	uint16_t word996;
	uint64_t qword998;
	uint64_t qword9A0;
	uint32_t dword9A8;
	uint64_t qword9AC;
	uint64_t qword9B4;
	uint64_t qword9BC;
	uint16_t word9C4;
	uint8_t byte9C6;
	char gap9C7;
	uint32_t dword9C8;
	uint8_t byte9CC;
	char gap9CD;
	uint16_t word9CE;
	uint16_t word9D0;
	char gap9D2[2];
	uint32_t dword9D4;
	char gap9D8[8];
	uint32_t dword9E0;
	uint64_t qword9E4;
	uint32_t dword9EC;
	uint32_t dword9F0;
	char gap9F4[4];
	float m_dirt_level; // 0x9F8
	uint32_t dword9FC;
	uint64_t qwordA00;
	uint64_t qwordA08;
	uint32_t dwordA10;
	uint32_t dwordA14;
	uint8_t byteA18;
	uint16_t wordA19;
	uint8_t byteA1B;
	uint32_t dwordA1C;
	uint64_t qwordA20;
	uint32_t dwordA28;
	uint32_t dwordA2C;
	uint64_t qwordA30;
	uint64_t qwordA38;
	uint64_t qwordA40;
	uint64_t qwordA48;
	uint8_t byteA50;
	char gapA51[7];
	uint64_t qwordA58;
	uint64_t qwordA60;
	uint32_t dwordA68;
	uint32_t dwordA6C;
	uint32_t dwordA70;
	uint32_t dwordA74;
	uint32_t dwordA78;
	uint32_t dwordA7C;
	uint64_t qwordA80;
	uint8_t byteA88;
	char gapA89;
	uint16_t wordA8A;
	uint64_t qwordA8C;
	uint64_t qwordA94;
	uint64_t qwordA9C;
	uint64_t qwordAA4;
	uint32_t dwordAAC;
	uint16_t wordAB0;
	uint16_t wordAB2;
	uint8_t byteAB4;
	uint16_t wordAB5;
	uint16_t wordAB7;
	char gapAB9[2];
	char gapABB[3]; // start of some kind of flag, default value 0x1000000i64
	uint8_t m_is_targetable; // 0xABE
	char gapABF[4]; // end of some kind of flag
	uint32_t dwordAC3;
	uint32_t dwordAC7;
	uint16_t wordACB;
	uint8_t byteACD;
	uint8_t byteACE;
	char gapACF;
	uint64_t qwordAD0;
	uint64_t qwordAD8;
	uint8_t byteAE0;
	char gapAE1[3];
	uint32_t dwordAE4;
	uint32_t dwordAE8;
	uint32_t dwordAEC;
	uint32_t dwordAF0;
	char gapAF4[4];
	uint32_t dwordAF8;
	char gapAFC[20];
	uint32_t dwordB10;
	uint32_t dwordB14;
	char gapB18[24];
	uint32_t dwordB30;
	uint64_t qwordB34;
	char gapB3C[4];
	uint32_t dwordB40;
	uint64_t qwordB44;
	char gapB4C[4];
	uint16_t owordB50;
	char gapB52[14];
	uint16_t owordB60;
	char gapB62[14];
	uint32_t dwordB70;
	uint32_t dwordB74;
	uint64_t qwordB78;
	uint32_t dwordB80;
	uint32_t dwordB84;
	uint32_t dwordB88;
	uint32_t dwordB8C;
	uint32_t dwordB90;
	uint32_t dwordB94;
	uint32_t dwordB98;
	uint32_t dwordB9C;
	uint32_t dwordBA0;
	uint64_t qwordBA4;
	char gapBAC[4];
	uint32_t dwordBB0;
	uint64_t qwordBB4;
	char gapBBC[20];
	uint64_t qwordBD0;
	char gapBD8[16];
	uint32_t dwordBE8;
	char gapBEC[4];
	uint64_t qwordBF0;
	uint32_t dwordBF8;
	uint64_t qwordBFC;
	uint16_t wordC04;
	uint8_t byteC06;
	char gapC07;
	uint64_t qwordC08;
	uint32_t dwordC10;
	uint32_t dwordC14;
	uint16_t wordC18;
	char gapC1A[2];
	uint64_t qwordC1C;
	uint64_t qwordC24;
	uint64_t qwordC2C;
	uint64_t qwordC34;
	char gapC3C[4];
	uint64_t qwordC40;
	uint64_t qwordC48;
	uint32_t dwordC50;
	char gapC54[4];
	uint32_t dwordC58;
	float m_gravity; // 0xC5C - might be start of some sub-class
	char gapC60[8];
	class CPed* m_driver; //0x0C68
	class CPed* m_passengers[15]; //0x0C70
	class CPed* m_last_driver; //0x0CE8
	char gapCF0[1424]; // end of sub-class
	uint32_t dword1280;
	char gap1284[4];
	uint32_t dword1288;
	char gap128C[12];
	uint16_t word1298;
	uint8_t byte129A;
	char gap129B;
	uint64_t qword129C;
	uint64_t qword12A4;
	uint64_t qword12AC;
	uint64_t qword12B4;
	char gap12BC[4];
	uint64_t qword12C0;
	uint64_t qword12C8;
	uint16_t word12D0;
	char gap12D2[14];
	uint32_t dword12E0;
	uint32_t dword12E4;
	uint64_t qword12E8;
	uint32_t dword12F0;
	char gap12F4[4];
	uint64_t qword12F8;
	char gap1300[56];
	uint64_t qword1338;
	uint64_t qword1340;
	uint32_t dword1348;
	uint32_t dword134C;
	uint32_t dword1350;
	uint64_t qword1354;
	uint32_t dword135C;
	uint32_t dword1360;
	uint32_t dword1364;
	uint32_t dword1368;
	char gap136C[4];
	float float1370;
	float float1374;
	char gap1378[8];
	uint64_t qword1380;
	uint64_t qword1388;
	uint32_t dword1390;
	uint64_t qword1394;
	uint16_t word139C;
	uint16_t word139E;
	uint8_t byte13A0;
	uint16_t word13A1;
	char gap13A3[2];
	uint8_t byte13A5;
	uint16_t word13A6;
	uint8_t byte13A8;
	char gap13A9[3];
	uint32_t dword13AC;
	uint8_t byte13B0;
	char gap13B1[3];
	uint64_t qword13B4;
	uint32_t dword13BC;
	uint32_t dword13C0;
	uint32_t dword13C4;
	uint32_t dword13C8;
	uint8_t byte13CC;
	char gap13CD[3];
	uint64_t qword13D0;
	uint8_t byte13D8;
	char gap13D9[3];
	uint32_t dword13DC;
	char gap13E0[8];
	uint32_t dword13E8;
	char gap13EC[116];
	uint32_t dword1460;
	uint16_t word1464;
	uint8_t byte1466;
	char gap1467;
	uint64_t qword1468;
}; //Size: 0x1450
static_assert(sizeof(CVehicle) == 0x1450);
#pragma pack(pop)
class CItemInfo {
public:
	char pad_0000[16]; //0x0000
	uint32_t m_name; //0x0010
	uint32_t m_model; //0x0014
	uint32_t m_audio; //0x0018
	uint32_t m_slot; //0x001C
}; //Size: 0x0020
static_assert(sizeof(CItemInfo) == 0x20);
class CAmmoInfo : public CItemInfo {
public:
	int32_t m_ammo_max; //0x0020
	int32_t m_ammo_max_50; //0x0024
	int32_t m_ammo_max_100; //0x0028
	int32_t m_ammo_max_mp; //0x002C
	int32_t m_ammo_max_50_mp; //0x0030
	int32_t m_ammo_max_100_mp; //0x0034
	uint32_t m_ammo_flags; //0x0038
	eAmmoSpecialType m_ammo_special_type; //0x003C
	char pad_0040[24]; //0x0040
	float m_missile_speed; //0x0058
	char pad_005C[284]; //0x005C
	uint32_t m_lock_on_time; //0x0178
}; //Size: 0x017C
static_assert(sizeof(CAmmoInfo) == 0x17C);
class CAimingInfo {
public:
	std::uint32_t m_name; //0x0000
	float m_heading_limit; //0x0004
	float m_sweep_pitch_min; //0x0008
	float m_sweep_pitch_max; //0x000C
}; //Size: 0x0010
static_assert(sizeof(CAimingInfo) == 0x10);
class CForceInfo {
public:
	std::int32_t m_bone_tag; //0x0000
	float m_front; //0x0004
	float m_back; //0x0008
}; //Size: 0x000C
static_assert(sizeof(CForceInfo) == 0xC);
class CWeaponInfo : public CItemInfo {
public:
	eDamageType m_damage_type; //0x0020
	std::uint32_t m_explosion_default; //0x0024
	std::uint32_t m_explosion_hit_car; //0x0028
	std::uint32_t m_explosion_hit_truck; //0x002C
	std::uint32_t m_explosion_hit_bike; //0x0030
	std::uint32_t m_explosion_hit_boat; //0x0034
	std::uint32_t m_explosion_hit_plane; //0x0038
	char pad_003C[24]; //0x003C
	eFireType m_fire_type; //0x0054
	eWheelSlot m_wheel_slot; //0x0058
	uint32_t m_group; //0x005C
	class CAmmoInfo* m_ammo_info; //0x0060
	class CAimingInfo* m_aiming_info; //0x0068
	uint32_t m_clip_size; //0x0070
	float m_accuracy_spread; //0x0074
	float m_accurate_mode_accuracy_modifier; //0x0078
	float m_run_and_gun_accuracy; //0x007C
	float m_run_and_gun_min_accuracy; //0x0080
	float m_recoil_accuracy_max; //0x0084
	float m_recoil_error_time; //0x0088
	float m_recoil_recovery_rate; //0x008C
	float m_recoil_accuracy_to_allow_headshot_ai; //0x0090
	float m_min_headshot_distance_ai; //0x0094
	float m_max_headshot_distance_ai; //0x0098
	float m_headshot_damage_modifier_ai; //0x009C
	float m_recoil_accuracy_to_allow_headshot_player; //0x00A0
	float m_min_headshot_distance_player; //0x00A4
	float m_max_headshot_distance_player; //0x00A8
	float m_headshot_damage_modifier_player; //0x00AC
	float m_damage; //0x00B0
	float m_damage_time; //0x00B4
	float m_damage_time_in_vehicle; //0x00B8
	float m_damage_time_in_vehicle_headshot; //0x00BC
	float m_hit_limbs_damage_modifier; //0x00C0
	float m_network_hit_limbs_damage_modifier; //0x00C4
	float m_lightly_armoured_damage_modifier; //0x00C8
	float m_vehicle_damage_modifier; //0x00CC
	float m_force; //0x00D0
	float m_force_hit_ped; //0x00D4
	float m_force_hit_vehicle; //0x00D8
	float m_force_hit_flying_heli; //0x00DC
	class CForceInfo* m_force_info; //0x00E0
	std::int16_t m_force_info_amount; //0x00E8
	std::int16_t m_force_info_count; //0x00EA
	char pad_00EC[8]; //0x00EC
	float m_force_max_strength_mult; //0x00F8
	float m_force_falloff_range_start; //0x00FC
	float m_force_falloff_range_end; //0x0100
	float m_force_falloff_range_min; //0x0104
	float m_project_force; //0x0108
	float m_frag_impulse; //0x010C
	float m_penetration; //0x0110
	float m_vertical_launch_adjustment; //0x0114
	float m_drop_forward_velocity; //0x0118
	float m_speed; //0x011C
	uint32_t m_bullets_in_batch; //0x0120
	float m_batch_spread; //0x0124
	float m_reload_time_mp; //0x0128
	float m_reload_time_sp; //0x012C
	float m_vehicle_reload_time; //0x0130
	float m_anim_reload_time; //0x0134
	int32_t m_bullets_per_anime_loop; //0x0138
	float m_time_between_shots; //0x013C
	float m_time_left_between_shots_where_should_fire_is_cached; //0x0140
	float m_spinup_time; //0x0144
	float m_spin_time; //0x0148
	float m_spindown_time; //0x014C
	float m_alternate_wait_time; //0x0150
	float m_bullet_bending_near_radius; //0x014C
	float m_bullet_bending_far_radius; //0x0150
	float m_bullet_bending_zoomed_radius; //0x0154
	float m_first_person_bullet_bending_near_radius; //0x0158
	float m_first_person_bullet_bending_far_radius; //0x015C
	float m_first_person_bullet_bending_zoomed_radius; //0x0160
	char pad_0164[12]; //0x0164
	std::int32_t m_effect_group; //0x0170
	std::uint32_t m_flash_fx; //0x0174
	std::uint32_t m_flash_fx_alt; //0x0178
	std::uint32_t m_flash_fx_first_person; //0x017C
	std::uint32_t m_flash_fx_first_person_alt; //0x0180
	std::uint32_t m_muzzle_smoke_fx; //0x0184
	std::uint32_t m_muzzle_smoke_fx_first_person; //0x0188
	char pad_018C[20]; //0x018C
	rage::vector3 m_muzzle_override_offset; //0x01A0
	char pad_01AC[8]; //0x01AC
	std::uint32_t m_shell_fx; //0x01B4
	std::uint32_t m_shell_fx_first_person; //0x01B8
	std::uint32_t m_tracer_fx; //0x01BC
	std::uint32_t m_ped_damage_hash; //0x01C0
	float m_tracer_fx_chance_sp; //0x01C4
	float m_tracer_fx_chance_mp; //0x01C8
	char pad_01CC[4]; //0x01CC
	float m_flash_fx_chance_sp; //0x01D0
	float m_flash_fx_chance_mp; //0x01D4
	float m_flash_fx_alt_chance; //0x01D8
	float m_flash_fx_scale; //0x01DC
	char pad_01E0[4]; //0x01E0
	float m_flash_fx_light_offset_dist; //0x01E4
	char pad_01E8[80]; //0x01E8
	float m_ground_disturb_fx_dist; //0x0238
	std::uint32_t m_ground_disturb_fx_name_default; //0x023C
	std::uint32_t m_ground_disturb_fx_name_sand; //0x0240
	std::uint32_t m_ground_disturb_fx_name_dirt; //0x0244
	std::uint32_t m_ground_disturb_fx_name_water; //0x0248
	std::uint32_t m_ground_disturb_fx_name_foliage; //0x024C
	std::int32_t m_initial_rumble_duration; //0x0250
	float m_initial_rumble_intensity; //0x0254
	float m_initial_rumble_intensity_trigger; //0x0258
	std::int32_t m_rumble_duration; //0x025C
	float m_rumble_intensity; //0x0260
	float m_rumble_intensity_trigger; //0x0264
	float m_rumble_damage_intensity; //0x0268
	std::int32_t m_initial_rumble_duration_fps; //0x026C
	float m_initial_rumble_intensity_fps; //0x0270
	std::int32_t m_rumble_duration_fps; //0x0274
	float m_rumble_intensity_fps; //0x0278
	float m_network_player_damage_modifier; //0x027C
	float m_network_ped_damage_modifier; //0x0280
	float m_network_headshot_modifier; //0x0284
	float m_lock_on_range; //0x0288
	float m_weapon_range; //0x028C
	float m_ai_sound_range; //0x0290
	float m_ai_potential_blast_event_range; //0x0294
	float m_damage_fall_off_range_min; //0x0298
	float m_damage_fall_off_range_max; //0x029C
	float m_damage_fall_off_modifier; //0x02A4
	std::uint32_t m_default_camera_hash; //0x02AC
	std::uint32_t m_ai_camera_hash; //0x02B0
	std::uint32_t m_fire_camera_hash; //0x02B4
	std::uint32_t m_cover_camera_hash; //0x02B8
	std::uint32_t m_cover_ready_to_fire_camera_hash; //0x02BC
	std::uint32_t m_run_and_gun_camera_hash; //0x02C0
	std::uint32_t m_cinematic_shooting_camera_hash; //0x02C4
	std::uint32_t m_alternative_or_scoped_camera_hash; //0x02C8
	std::uint32_t m_run_and_gun_alternative_or_scoped_camera_hash; //0x02CC
	std::uint32_t m_cinematic_shooting_alternative_or_scoped_camera_hash; //0x02D0
	char pad_02D4[4]; //0x02D4
	std::uint32_t m_recoil_shake_hash; //0x02D8
	std::uint32_t m_recoil_shake_hash_first_person; //0x02DC
	std::uint32_t m_accuracy_offset_shake_hash; //0x02E0
	std::int32_t m_min_time_between_recoil_shakes; //0x02E4
	float m_recoil_shake_amplitude; //0x02E8
	float m_explosion_shake_amplitude; //0x02EC
	float m_camera_fov; //0x02F0
	std::float_t m_first_person_aim_fov_min; //0x02F4
	std::float_t m_first_person_aim_fov_max; //0x02F8
}; //Size: 0x02F8
static_assert(sizeof(CWeaponInfo) == 0x2F8);
class CPedWeaponManager {
public:
	char pad_0000[16]; //0x0000
	class CPed* m_owner; //0x0010
	uint32_t m_selected_weapon_hash; //0x0018
	char pad_001C[4]; //0x001C
	class CWeaponInfo* m_weapon_info; //0x0020
	char pad_0028[72]; //0x0028
	class CWeaponInfo* m_vehicle_weapon_info; //0x0070
}; //Size: 0x0078
static_assert(sizeof(CPedWeaponManager) == 0x78);
class CPedFactory {
public:
	char pad_0000[8]; //0x0000
	class CPed* m_local_ped; //0x0008
}; //Size: 0x0010
static_assert(sizeof(CPedFactory) == 0x10);
class CPedModelInfo {
public:
	char pad_0000[24]; //0x0000
	uint32_t m_model_hash; //0x0018
}; //Size: 0x001C
static_assert(sizeof(CPedModelInfo) == 0x1C);
class posBase {
public:
	char pad_0000[80]; //0x0000
	rage::vector3 m_pos; //0x0050
}; //Size: 0x005C
static_assert(sizeof(posBase) == 0x5C);
#pragma pack(push, 1)
class CPed : public rage::CPhysical {
public:
	char pad_02EC[20]; //0x02EC
	struct rage::vector3 m_velocity; //0x0300
	char pad_030C[2564]; //0x030C
	class CVehicle* m_vehicle; //0x0D10
	char pad_0D18[912]; //0x0D18
	class CPlayerInfo* m_player_info; //0x10A8
	class CPedInventory* m_inventory; //0x10B0
	class CPedWeaponManager* m_weapon_manager; //0x10B8
	char pad_10C0[907]; //0x10C0
	uint8_t m_ped_task_flag; //0x144B
	char pad_144C[192]; //0x144C
	float m_armor; //0x150C
}; //Size: 0x1510
static_assert(sizeof(CPed) == 0x1510);
#pragma pack(pop)
#pragma pack(push, 4)
class CPlayerInfo {
public:
	char pad_0000[32]; //0x0000
	class rage::rlGamerInfo m_gamer_info; //0x0020
	char pad_00B8[184]; //0x00B8
	float m_swim_speed; //0x0170
	char pad_0174[20]; //0x0174
	uint32_t m_water_proof; //0x0188
	char pad_018C[92]; //0x018C
	class CPed* m_ped; //0x01E8
	char pad_01F0[40]; //0x01F0
	uint32_t m_frame_flags; //0x0218
	char pad_021C[52]; //0x021C
	uint32_t m_player_controls; //0x0250
	char pad_0254[1256]; //0x0254
	float m_wanted_can_change; //0x073C
	char pad_0740[304]; //0x0740
	uint32_t m_npc_ignore; //0x0870
	char pad_0874[12]; //0x0874
	bool m_is_wanted; //0x0880
	char pad_0881[7]; //0x0881
	uint32_t m_wanted_level; //0x0888
	uint32_t m_wanted_level_display; //0x088C
	char pad_0890[1120]; //0x0890
	float m_run_speed; //0x0CF0
	float m_stamina; //0x0CF4
	float m_stamina_regen; //0x0CF8
	char pad_0CFC[16]; //0x0CFC
	float m_weapon_damage_mult; //0x0D0C
	float m_weapon_defence_mult; //0x0D10
	char pad_0D14[4]; //0x0D14
	float m_melee_weapon_damage_mult; //0x0D18
	float m_melee_damage_mult; //0x0D1C
	float m_melee_defence_mult; //0x0D20
	char pad_0D24[8]; //0x0D24
	float m_melee_weapon_defence_mult; //0x0D2C
}; //Size: 0x0D30
static_assert(sizeof(CPlayerInfo) == 0xD30);
#pragma pack(pop)
#pragma pack(push, 1)
class ClanData {
public:
	int64_t m_clan_member_id; //0x0000
	int64_t m_clan_id; //0x0008
	int32_t m_clan_color; //0x0010
	int32_t m_clan_member_count; //0x0014
	int32_t m_clan_created_time; //0x0018
	bool m_is_system_clan; //0x001C
	bool m_is_clan_open; //0x001D
	char m_clan_name[25]; //0x001E
	char m_clan_tag[5]; //0x0037
	char m_clan_motto[65]; //0x003C
	char pad_007D[3]; //0x007D
	int64_t m_clan_id_2; //0x0080
	char m_clan_rank_name[25]; //0x0088
	char pad_00A1[3]; //0x00A1
	int32_t m_clan_rank_order; //0x00A4
	int64_t m_clan_rank_flags; //0x00A8
	char unk_00B0[8]; //0x00B0
}; //Size: 0x00B8
static_assert(sizeof(ClanData) == 0xB8);
#pragma pack(pop)
#pragma pack(push, 8)
class CNetGamePlayer : public rage::netPlayer {
public:
	class CPlayerInfo* m_player_info; //0x00A0
	uint32_t m_matchmaking_group; //0x0008
	bool m_is_spectating; //0x000C
	char pad_00AD[3]; //0x000AD
	uint64_t unk_00B0; //0x00B0
	char unk_00B8; //0x00B8
	char pad_00B9[3]; //0x00B9
	uint32_t unk_00BC; //0x00BC
	uint32_t unk_00C0; //0x00C0
	char pad_00C4[4]; //0x00C4
	class ClanData m_clan_data; //0x00C8
	char m_crew_rank_title[25]; //0x0180
	bool m_is_rockstar_dev; //0x0199
	bool m_is_rockstar_qa; //0x019A
	bool m_is_cheater; //0x019B
	uint32_t unk_019C; //0x019C
	uint16_t unk_01A0; //0x01A0
	char unk_01A2; //0x01A2
	char pad_01A3; //0x01A3
	uint32_t m_phone_explosion_vehicle_net_id; //0x01A4
	uint16_t unk_01A8; //0x01A8
	bool m_has_started_transition; //0x01AA
	char pad_01AB[5]; //0x01AB
	class rage::rlSessionInfo m_transition_session_info; //0x01A3
	char pad_022D[16]; //0x022D
	uint64_t unk_0230; //0x0230
	uint64_t unk_0238; //0x0238
	uint32_t m_mute_count; //0x0240
	uint32_t m_mute_talkers_count; //0x0244
	char pad_0248[5]; //0x0248
	bool m_have_communication_privileges; //0x024D
	uint16_t unk_024E; //0x024E
	uint16_t unk_0250; //0x0250
	char pad_0252[2]; //0x0252
	uint32_t m_cheat_report_ids[20]; //0x0254
	uint32_t m_num_cheat_reports; //0x02A4
	uint8_t unk_02A8; //0x02A8
	char pad_02A9[3]; //0x02A9
	uint32_t unk_02AC; //0x02AC
	char unk_02B0; //0x02B0
	char pad_02B1[3]; //0x02B1
	uint32_t unk_02B4; //0x02B4
	uint32_t m_account_id; //0x02B4
	uint32_t m_unk_02BC; //0x02BC
}; //Size: 0x02C0
static_assert(sizeof(CNetGamePlayer) == 0x2C0);
#pragma pack(pop)
#pragma pack(push, 2)
class CNetworkPlayerMgr : public rage::netPlayerMgrBase {
public:
	class CNetGamePlayer m_net_players[32]; //0x08E0
	uint64_t unk_60E0; //0x60E0
	uint64_t unk_60E8; //0x60E8
	uint64_t unk_60F0; //0x60F0
	uint64_t unk_60F8; //0x60F8
	class CNetGamePlayer m_net_players_2[32]; //0x6100
	uint64_t unk_B900; //0xB900
	uint64_t unk_B908; //0xB908
	uint64_t unk_B910; //0xB910
	uint64_t unk_B918; //0xB918
	uint64_t unk_B920; //0xB920
	uint64_t unk_B928; //0xB928
	uint64_t unk_B930; //0xB930
	uint32_t unk_B938; //0xB938
	char pad_B93C[3]; //0xB93C
	bool unk_B93F; //0xB93F
	uint32_t unk_B940; //0xB940
	uint32_t unk_B944; //0xB944
	uint16_t unk_B948; //0xB948
}; //Size: 0xB94A
static_assert(sizeof(CNetworkPlayerMgr) == 0xB94A);
#pragma pack(pop)
class CScriptedGameEvent : public rage::netGameEvent {
public:
	char m_padding[0x40];      // 0x30
	std::int64_t m_args[54];   // 0x70
	std::uint32_t m_bitset;    // 0x220
	std::uint32_t m_args_size; // 0x224
};
class CNetworkIncrementStatEvent : public rage::netGameEvent {
public:
	std::uint32_t m_stat;   // 0x30
	std::uint32_t m_amount; // 0x34
};
#pragma pack(push, 1)
class ScInfo {
public:
	char m_ticket[256]; //0x0000
	char pad_0100[256]; //0x0100
	char m_auth_token[128]; //0x0200
	char pad_0280[16]; //0x0280
	uint64_t m_peer_id; //0x0290
	char pad_0298[132]; //0x0298
	char m_country_code[3]; //0x031C
	char pad_031F[32]; //0x031F
	char m_email[78]; //0x033F
	char pad_038D[24]; //0x038D
	char m_language_code[8]; //0x03A5
	char pad_03AD[2]; //0x03AD
	char m_name[20]; //0x03AF
	char pad_03C3[200]; //0x03C3
}; //Size: 0x048B
static_assert(sizeof(ScInfo) == 0x48B);
#pragma pack(pop)
class GtaThread : public rage::scrThread {
public:
	std::uint32_t m_script_hash;                // 0x120
	char m_padding3[0x14];                      // 0x124
	std::int32_t m_instance_id;                 // 0x138
	char m_padding4[0x04];                      // 0x13C
	std::uint8_t m_flag1;                       // 0x140
	bool m_safe_for_network_game;               // 0x141
	char m_padding5[0x02];                      // 0x142
	bool m_is_minigame_script;                  // 0x144
	char m_padding6[0x02];                      // 0x145
	bool m_can_be_paused;                       // 0x147
	bool m_can_remove_blips_from_other_scripts; // 0x148
	char m_padding7[0x0F];                      // 0x149
};
class CPickup {
public:
	char pad_0x0000[0x30]; //0x0000
	CNavigation* m_navigation; //0x0030
	char pad_0x0038[0x58]; //0x0083
	rage::vector3 m_position; //0x0090
	char pad_0x009C[0x3F4]; //0x009C
	int32_t m_money; //0x0490
	char pad_0x0484[0x104]; //0x0484
};//Size=0x0588
class CPickupHandle {
public:
	CPickup* m_pickup; //0x0000 
	int32_t m_handle; //0x0008 
	char pad_0x000C[4]; //0x000C
}; //Size=0x0010
//Max pickups: 73
class CPickupList {
public:
	CPickupHandle m_pickups[73]; //0x0000 
	uintptr_t getAddress(size_t index) {
		uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
		return *(uintptr_t*)addr;
	}
}; //Size=0x0490
class CPickupInterface {
public:
	char pad_0x0000[0x100]; //0x0000
	CPickupList* m_pickup_list; //0x0100 
	int32_t m_max_pickups; //0x0108 
	int32_t m_cur_pickups; //0x0110 
	CPickup* get_pickup(const int& index) {
		if (index < m_max_pickups)
			return m_pickup_list->m_pickups[index].m_pickup;
		return nullptr;
	}
}; //Size=0x0114
class CObject : public rage::fwEntity {}; //Size: 0x00B9
class CObjectHandle {
public:
	CObject* m_object; //0x0000
	int32_t m_handle; //0x0008
	char pad_000C[4]; //0x000C
}; //Size: 0x0010
static_assert(sizeof(CObjectHandle) == 0x10);
class CObjectList {
public:
	CObjectHandle m_objects[2300]; //0x0000
	uintptr_t getAddress(size_t index) {
		uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
		return *(uintptr_t*)addr;
	}
}; //Size: 0x8FC0
class CObjectInterface {
public:
	char pad_0000[344]; //0x0000
	CObjectList* m_object_list; //0x0158
	int32_t m_max_objects; //0x0160
	char pad_0164[4]; //0x0164
	int32_t m_cur_objects; //0x0168
	CObject* get_object(const int& index) {
		if (index < m_max_objects)
			return m_object_list->m_objects[index].m_object;
		return nullptr;
	}
}; //Size: 0x016C
class CPedHandle {
public:
	CPed* m_ped; //0x0000
	int32_t m_handle; //0x0008
	char pad_000C[4]; //0x000C
}; //Size: 0x0010
static_assert(sizeof(CPedHandle) == 0x10, "CPedHandle is not properly sized");
class CPedList {
public:
	CPedHandle m_peds[256]; //0x0000
	uintptr_t getAddress(size_t index) {
		uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
		return *(uintptr_t*)addr;
	}
}; //Size: 0x1000
class CPedInterface {
public:
	char pad_0000[256]; //0x0000
	CPedList* m_ped_list; //0x0100
	int32_t m_max_peds; //0x0108
	char pad_010C[4]; //0x010C
	int32_t m_cur_peds; //0x0110
	CPed* get_ped(const int& index) {
		if (index < m_max_peds)
			return m_ped_list->m_peds[index].m_ped;
		return nullptr;
	}
}; //Size: 0x0114
class CVehicleHandle {
public:
	CAutomobile* m_vehicle; //0x0000
	int32_t m_handle; //0x0008
	char pad_000C[4]; //0x000C
}; //Size: 0x0010
static_assert(sizeof(CVehicleHandle) == 0x10, "CVehicleHandle is not properly sized");
class CVehicleList {
public:
	class CVehicleHandle m_vehicles[300]; //0x0000
	uintptr_t getAddress(size_t index) {
		uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
		return *(uintptr_t*)addr;
	}
}; //Size: 0x12C0
class CVehicleInterface {
public:
	char pad_0000[384]; //0x0000
	class CVehicleList* m_vehicle_list; //0x0180
	int32_t m_max_vehicles; //0x0188
	char pad_018C[4]; //0x018C
	int32_t m_cur_vehicles; //0x0190
	CAutomobile* get_vehicle(const int& index) {
		if (index < m_max_vehicles)
			return m_vehicle_list->m_vehicles[index].m_vehicle;
		return nullptr;
	}
}; //Size: 0x0194
class CReplayInterface {
public:
	char pad_0x0000[0x10]; //0x0000
	class CVehicleInterface* m_vehicle_interface; //0x0010
	class CPedInterface* m_ped_interface; //0x0018
	class CPickupInterface* m_pickup_interface; //0x0020 
	class CObjectInterface* m_object_interface; //0x0028
	char pad_0x0030[0x10]; //0x0030
}; //Size=0x0040
class CNetworkObjectMgr : public rage::netObjectMgrBase {};
class CUpdateFxnEventVtbl {
public:
	void* Destructor; //0x0000
	void* GetName; //0x0008
	void* IsInScope; //0x0018
	void* CanChangeScope; //0x0020
	void* Prepare; //0x0028
	char pad_0030[16]; //0x0030
}; //Size=0x0040

class globals {
private:
	uint64_t m_index;
	static void* getScriptGlobal(uint64_t index) { return g_pointers.m_globals[index >> 18 & 0x3F] + (index & 0x3FFFF); }
	static void* getLocalGlobal(PVOID stack, uint64_t index) { return reinterpret_cast<uintptr_t*>(uintptr_t(stack) + (index * sizeof(uintptr_t))); }
public:
	globals(uint64_t index) {
		m_index = index;
	}
	globals at(uint64_t index) {
		return globals(m_index + index);
	}
	globals at(uint64_t index, uint64_t size) {
		return at(1 + (index * size));
	}
	//Script Globals
	template <typename T> std::enable_if_t<std::is_pointer<T>::value, T> as() {
		return (T)getScriptGlobal(m_index);
	}
	//Local Globals
	template <typename T> std::enable_if_t<std::is_pointer<T>::value, T> asLocal(PVOID stack) {
		return (T)getLocalGlobal(stack, m_index);
	}
};
class simpleTimer {
public:
	void start(std::uint64_t ticks) {
		if (m_tick) {
			m_ready_at = GetTickCount64() + ticks;
			m_tick = false;
		}
	}
	bool isReady() {
		return GetTickCount64() > m_ready_at;
	}
	void reset() {
		m_tick = true;
	}
private:
	std::uint64_t m_ready_at;
	bool m_tick;
};

template <typename type>
inline CNetGamePlayer* getNetPlyr(type val) {
	if (auto netPlyrMgr = *g_pointers.m_networkPlayerMgr; netPlyrMgr) {
		for (auto& plyr : netPlyrMgr->m_player_list) {
			if (plyr && plyr->IsConnected()) {
				if (auto netData = plyr->GetGamerInfo(); netData) {
					if (netData->m_host_token == (uint64_t)val || plyr->m_player_id == (uint8_t)val || plyr->m_msg_id == (uint32_t)val || netData->m_id == (uint64_t)val) {
						return plyr;
					}
				}
			}
		}
	}
	return nullptr;
}