#pragma once
#include <type_traits>
#include <utility>
#include "Poolable.h"
#include <memory>

template<typename T, typename... args>
class ObjectPool
{
public:
	using type = std::remove_pointer_t<T>;
	static_assert(std::is_base_of<Poolable, type>::value, "Must be poolable");
	static_assert(!std::is_pointer<T>::value, "Pooled object must not be a pointer");

	void Release(std::unique_ptr<T>& p) {
		//if size < maxsize?
		poolPointers.push_back(std::move(p));
	}

	std::unique_ptr<T>& Get() {
		if (poolPointers.size() > 0)
		{
			std::unique_ptr<T> ptr = std::move(poolPointers.back());
			poolPointers.pop_back();
			return std::move(ptr);
		}
		return nullptr;
	}

	void Init(size_t p_maxSize, args... p_constructionValues) {
		maxSize = p_maxSize;
		for (int i = 0; i < p_maxSize; i++) {			
			T* t = new T(p_constructionValues...);
			std::unique_ptr<T> ptr(std::move(t));
			poolPointers.push_back(std::move(ptr));
		}
	}
private:
	size_t maxSize;
	std::vector<std::unique_ptr<T>> poolPointers;
};