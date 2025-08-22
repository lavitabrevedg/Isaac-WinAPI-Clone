#pragma once
#include "Actor.h"

template <typename T>
class ObjectPool
{
public:
	void Init(int size)
	{
		for (int i = 0; i < size; i++)
		{
			_pool.push(new T());
		}
	}

	void Clear()
	{
		while (!_pool.empty())
		{
			T* obj = _pool.top();
			_pool.pop();
			if (obj == nullptr) { continue; }

			obj->Destroy();
			SAFE_DELETE(obj);
		}
	}

	T* Pull()
	{
		if (_pool.empty())
		{
			for (int i = 0; i < 5; i++)
			{
				_pool.push(new T());
			}
		}

		T* obj = static_cast<T*>(_pool.top());
		_pool.pop();

		return obj;
	}

	void RePush(T* obj)
	{
		if (obj == nullptr)
			return;

		_pool.push(obj);
	}

private:
	std::stack<T*> _pool;
};