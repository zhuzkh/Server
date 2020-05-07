#pragma once
template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
protected:
	Singleton(){}
	virtual ~Singleton(){}
 	Singleton(const Singleton<T>&) = delete;
 	Singleton<T>& operator=(const Singleton<T>&) = delete;
 	Singleton<T>& operator=(const Singleton<T>&&) = delete;
};

template <typename T>
class ThreadLocalSingleton
{
public:
	static T& GetInstance()
	{
		static thread_local T instance;
		return instance;
	}
protected:
	ThreadLocalSingleton() {}
	virtual ~ThreadLocalSingleton() {}
	ThreadLocalSingleton(const ThreadLocalSingleton<T>&) = delete;
	ThreadLocalSingleton<T>& operator=(const ThreadLocalSingleton<T>&) = delete;
	ThreadLocalSingleton<T>& operator=(const ThreadLocalSingleton<T>&&) = delete;
};

