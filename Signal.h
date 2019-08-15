#pragma once
#include <functional>
#include <list>

template <typename... Args>
class Signal
{
public:
	template <typename T>
	void Bind(void(T::*slot)(Args...), T* instance)
	{
		m_slots.push_back([=](Args... args) {if (instance) { (instance->*slot)(args...); }; });
	}

	void Bind(std::function<void(Args...)> func)
	{
		m_slots.push_back(func);
	}

	void Emit(Args... args)
	{
		for (auto& slot : m_slots) {
			slot(args...);
		}
	}

	void operator()(Args... args)
	{
		Emit(args...);
	}
private:
	std::list<std::function<void(Args...)>> m_slots;
};