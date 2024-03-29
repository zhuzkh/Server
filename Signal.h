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

#define REGISTER_SIGNAL(SigImpl, ...) class SigImpl : public Signal<__VA_ARGS__>\
									  {\
									  public:\
									  	static SigImpl& GetInstance()\
									  	{\
									  		static SigImpl instance;\
									  		return instance;\
									  	}\
									  }; 

#define SIGNAL_EMIT(sig, ...) sig::GetInstance().Emit(__VA_ARGS__);

#define SIGNAL_BIND(sig, ...) sig::GetInstance().Bind(__VA_ARGS__)  

