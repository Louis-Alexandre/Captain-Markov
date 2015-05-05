#pragma once

#include <algorithm>

struct nullopt_t {
    constexpr nullopt_t(int) {}
};

constexpr static nullopt_t nullopt{0};

template<typename T>
struct optionnal {
	constexpr optionnal() : engaged{false} {}
	constexpr optionnal(optionnal&& other) : value{std::move(other.value)}, engaged{other.engaged} {}
	constexpr optionnal(const optionnal& other) : value{other.value}, engaged{other.engaged} {}
	constexpr optionnal(nullopt_t) : value{}, engaged{false} {}
	constexpr optionnal(T&& _value) : value{_value}, engaged{true} {}
	constexpr optionnal(const T& _value) : value{_value}, engaged{true} {}
	
	optionnal& operator=(nullopt_t) {
		engaged = false;
	}
	
	optionnal& operator=(const optionnal& other) {
		engaged = other.engaged;
		value = other.value;
	}
	
	optionnal& operator=(optionnal&& other) {
		engaged = other.engaged;
		value = std::move(other.value);
		other.engaged = false;
	}
	
	template<typename U>
	optionnal& operator=(U&& _value) {
		value = std::move(_value);
		engaged = true;
	}
	
	constexpr operator bool() const {
		return engaged;
	}
	
	constexpr const T* operator->() const {
		return &value;
	}
	
	T* operator->() {
		return &value;
	}
	
	constexpr const T& operator*() const& {
		return value;
	}
	
	T& operator*() & {
		return value;
	}
	
	constexpr const T&& operator*() const&& {
		return std::move(value);
	}
	
	T&& operator*() && {
		return std::move(value);
	}
	
	template<typename ...Args>
	void emplace(Args... args) {
		value = T{std::forward<Args>(args)...};
	}
	
private:
	bool engaged;
	T value;
};
