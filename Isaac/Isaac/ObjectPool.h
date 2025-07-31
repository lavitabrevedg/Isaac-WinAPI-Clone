#pragma once
#include <stack>

template <typename T>
class Pool
{
public: //@TODO Pool±¸Çö
	Pool<T>(int size)
	{
		for (int i = 0; i < size; i++)
		{
			_pool.push(new T());
		}
	}

	~Pool()
	{
		for (auto& iter : _pool)
		{
			delete iter;
			iter = nullptr;
			_pool
		}
	}

	T Pull()
	{
		
	}

	void RePush(T* obj)
	{

	}

private:
	std::stack<T*> _pool;
};