#pragma once
#include "stdafx.h"
#ifndef MemoryPoolH
#define MemoryPoolH

#include <memory>

namespace Moya {
	//KonsTgrowSize
	//template <class T, std::size_t growSize = 1024>
	template <class T, std::size_t growSize = KonsTgrowSize>
	class MemoryPool
	{
		struct Block
		{
			Block *next;
		};

		class Buffer
		{
			static const std::size_t blockSize = sizeof(T) > sizeof(Block) ? sizeof(T) : sizeof(Block);
			uint8_t data[blockSize * growSize];

		public:

			Buffer *const next;

			Buffer(Buffer *next) :
				next(next)
			{
			}

			T *getBlock(std::size_t index)
			{
				return reinterpret_cast<T *>(&data[blockSize * index]);
			}
		};

		Block *firstFreeBlock = nullptr;
		Buffer *firstBuffer = nullptr;
		std::size_t bufferedBlocks = growSize;

		MemoryPool(MemoryPool &&memoryPool) = delete;
		MemoryPool(const MemoryPool &memoryPool) = delete;
		MemoryPool &operator =(MemoryPool &&memoryPool) = delete;
		MemoryPool &operator =(const MemoryPool &memoryPool) = delete;


	public:

		MemoryPool() = default;

		~MemoryPool()
		{
			while (firstBuffer) 
			{
				Buffer *buffer = firstBuffer;
				firstBuffer = buffer->next;
				cout << typeid(*this).name() << " DTOR     @ = " << this <<", buffer = "<< buffer << endl;
				delete buffer;
			}
		}

		T *allocate()
		{
			if (firstFreeBlock) {
				Block *block = firstFreeBlock;
				firstFreeBlock = block->next;
				return reinterpret_cast<T *>(block);
			}

			if (bufferedBlocks >= growSize) {
				firstBuffer = new Buffer(firstBuffer);
				bufferedBlocks = 0;
			}

			return firstBuffer->getBlock(bufferedBlocks++);
		}

		void deallocate(T *pointer)
		{
			Block *block = reinterpret_cast<Block *>(pointer);
			block->next = firstFreeBlock;
			firstFreeBlock = block;
		}
	};

}

#endif
