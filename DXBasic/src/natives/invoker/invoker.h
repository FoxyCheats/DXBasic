#pragma once
#include "pch/pch.h"
#include "natives/types.h"
#include "natives/crossmap/crossmap.h"
#include <iostream>

namespace rage {
	class scrNativeCallContext {
	public:
		void reset() {
			m_argCount = 0;
			m_dataCount = 0;
		}
		template <typename t>
		void pushArg(t&& value) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(reinterpret_cast<std::uint64_t*>(m_args) + (m_argCount++)) = std::forward<t>(value);
		}
		template <typename t>
		t& getArg(std::size_t index) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			return *reinterpret_cast<t*>(reinterpret_cast<std::uint64_t*>(m_args) + index);
		}
		template <typename t>
		void setArg(std::size_t index, t&& value) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(reinterpret_cast<std::uint64_t*>(m_args) + index) = std::forward<t>(value);
		}
		template <typename t>
		t* getRetValue() {
			return reinterpret_cast<t*>(m_ret);
		}
		template <typename t>
		void setRetValue(t&& value) {
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(m_ret) = std::forward<t>(value);
		}
	public:
		int64_t shiftVectorCoords() {
			auto a1 = (int64_t)this;
			int64_t res{};
			for (; *(uint32_t*)(a1 + 0x18); *(uint32_t*)(*(uint64_t*)(a1 + 8i64 * *(int*)(a1 + 0x18) + 0x20) + 16i64) = uint32_t(res)) {
				--(*(uint32_t*)(a1 + 0x18));
				**(uint32_t**)(a1 + 8i64 * *(int*)(a1 + 0x18) + 32) = *(uint32_t*)(a1 + 16 * (*(int*)(a1 + 0x18) + 4i64));
				*(uint32_t*)(*(uint64_t*)(a1 + 8i64 * *(int*)(a1 + 0x18) + 0x20) + 8i64) = *(uint32_t*)(a1 + 16i64 * (*(int*)(a1 + 0x18)) + m_vecSpace[32]);
				res = *(unsigned int*)(a1 + 16i64 * *(int*)(a1 + 0x18) + 0x48);
			}
			--* (uint32_t*)(a1 + 0x18);
			return res;
		}
	public:
		void* m_ret;
		uint32_t m_argCount;
		char padding[4];
		void* m_args;
		uint32_t m_dataCount;
		char padding1[4];
		alignas(uintptr_t) uint8_t m_vecSpace[192];
	};
	using scrNativeHandler = fnptr<void(class scrNativeCallContext*)>;
	using scrNativeHash = uint64_t;
}

class nativeCtx : public rage::scrNativeCallContext {
public:
	nativeCtx() {
		reset();
	}
	void reset() {
		m_ret = &m_retData[0];
		m_argCount = 0;
		m_args = &m_argData[0];
		m_dataCount = 0;
		std::fill(std::begin(m_vecSpace), std::end(m_vecSpace), '\0');
		std::fill(std::begin(m_argData), std::end(m_argData), 0);
		std::fill(std::begin(m_retData), std::end(m_retData), 0);
	}
	template <typename type>
	void pushArg(type value) {
		m_argData[m_argCount++] = (uintptr_t)value;
	}
	void pushArg(Vector3 value) {
		pushArg(value.x);
		pushArg(value.y);
		pushArg(value.z);
	}
	template <typename type>
	type getRet() { return *static_cast<type*>(m_ret); }
	template <>
	void getRet<void>() {}
public:
	uintptr_t m_retData[10]{};
	uintptr_t m_argData[100]{};
};
class invoker {
public:
	void cache();
public:
	void begin();
	void end(std::uint64_t hash);
	template <typename type>
	void push(type&& value) {
		m_context.pushArg(std::forward<type>(value));
	}
	template <typename ret>
	ret get() {
		return m_context.getRet<ret>();
	}
public:
	std::map<rage::scrNativeHash, rage::scrNativeHandler> m_cache{};
	nativeCtx m_context{};
};
inline invoker g_invoker{};