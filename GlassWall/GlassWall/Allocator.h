#pragma once
#include "stdafx.h"
#ifndef AllocatorH
#define AllocatorH

#include <memory>

#include "MemoryPool.h"

namespace Moya {

	template <class T, std::size_t growSize = 1024>
	class Allocator : private MemoryPool<T, growSize>
	{
		std::allocator<T>* defaultAllocator = nullptr;
		std::wofstream* m_p = nullptr;

	public:

		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T value_type;

		template <class U>
		struct rebind
		{
			typedef Allocator<U, growSize> other;
		};

		//Allocator() = default;
		Allocator(std::wofstream* p = nullptr):m_p(p)
		{
			cout << typeid(*this).name() << "  CTOR     @ = " << this << endl;
			//*m_p << typeid(*this).name() << "  CTOR     @ = " << this << endl;
		}

		template <class U>
		Allocator(const Allocator<U, growSize> &other)
		{
			if (!std::is_same<T, U>::value)
				defaultAllocator = new std::allocator<T>();
		}

		~Allocator()
		{
			cout << typeid(*this).name() << "  DTOR     @ = " << this << endl;
			delete defaultAllocator;
		}

		pointer allocate(size_type n, std::allocator<void>::const_pointer hint = 0)
		{
			if (defaultAllocator)
				return defaultAllocator->allocate(n, hint);

			if (n != 1 || hint)
				throw std::bad_alloc();

			return MemoryPool<T, growSize>::allocate();
		}

		void deallocate(pointer p, size_type n)
		{
			if (defaultAllocator)
				defaultAllocator->deallocate(p, n);

			else
				MemoryPool<T, growSize>::deallocate(p);
		}

		void construct(pointer p, const_reference val)
		{
			new (p) T(val);
		}

		void destroy(pointer p)
		{
			p->~T();
		}
	};

}

#endif
