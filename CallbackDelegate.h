#pragma once
#include <functional>
#include <tuple>
#include "MemoryPool.h"

class DelegateBase
{
public:
	virtual void Callback() = 0;
	virtual void Recycle() = 0;
};

template <typename... Args>
class CallbackDelegate : public DelegateBase
{
public:
	void Bind(std::function<void(Args...)> func)
	{
		m_func = func;
	}

	void Callback()
	{
		m_func(0);
//  	doFunc(m_func, m_tuple);
	}
	void Recycle()
	{
		MemoryPoolSingleParam<CallbackDelegate<Args...>>::GetInstance().Recycle(this);
	}
	void Clear()
	{
		m_func = nullptr;
	}
private:
	template<typename F, typename T, std::size_t... I>
	auto doFuncImpl(F f, const T& t, std::index_sequence<I...>)// -> decltype(f(std::get<I>(t)...))
	{
		return f(std::get<I>(t)...);
	}
	
	template<typename F, typename T>
	auto doFunc(F f, const T& t)// -> decltype(doFuncImpl(f, t, std::make_index_sequence<std::tuple_size<T>::value>()))
	{
		return doFuncImpl(f, t, std::make_index_sequence<std::tuple_size<T>::value>());
	}
private:
	std::function<void(Args...)> m_func;
// 	std::tuple<Args...> m_tuple;
};
