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


#define SIGNAL_ARGS_GLUE(x, y) x y
#define SIGNAL_MACRO_VAR_ARGS_IMPL_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define SIGNAL_MACRO_VAR_ARGS_IMPL(args)  SIGNAL_MACRO_VAR_ARGS_IMPL_COUNT args
#define SIGNAL_MACRO_COUNT_VAR_ARGS(...)  SIGNAL_MACRO_VAR_ARGS_IMPL((__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define SIGNAL_MACRO_CHOOSE_HELPER2(count)  SIGNAL_BIND##count
#define SIGNAL_MACRO_CHOOSE_HELPER1(count)  SIGNAL_MACRO_CHOOSE_HELPER2(count)
#define SIGNAL_MACRO_CHOOSE_HELPER(count)   SIGNAL_MACRO_CHOOSE_HELPER1(count)
#define SIGNAL_BIND2(sig, func) sig::GetInstance().Bind(func);
#define SIGNAL_BIND3(sig, func, instance) sig::GetInstance().Bind(func, instance);

#define SIGNAL_BIND(...) SIGNAL_ARGS_GLUE(SIGNAL_MACRO_CHOOSE_HELPER(SIGNAL_MACRO_COUNT_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))
