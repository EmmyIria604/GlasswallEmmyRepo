#ifndef PerformanceH
#define PerformanceH

#include <iostream>
#include <chrono>
#include <random>

#include <set>
#include <map>
#include <list>
#include <forward_list>

#include "Allocator.h"

extern const std::size_t KonsTgrowSize = 512;// 2048;//1024;
const std::size_t growSize = KonsTgrowSize;
const int numberOfIterations = KonsTgrowSize;
const int randomRange = KonsTgrowSize;

class PerformanceTimer
{
    std::chrono::high_resolution_clock::time_point from, to;


    public:

        void start()
        {
            from = std::chrono::high_resolution_clock::now();
        }

        void stop()
        {
            to = std::chrono::high_resolution_clock::now();
        }

        double toSeconds() const
        {
            return std::chrono::duration_cast<std::chrono::duration<double>>(to - from).count();
        }
};

template <typename Container>
class PerformanceTest
{
    virtual void testIteration(int newSize) = 0;


    protected:

        int size = 0;
        Container container;

        std::default_random_engine randomNumberGenerator;
        std::uniform_int_distribution<int> randomNumberDistribution;

		std::wofstream* m_p = nullptr;

    public:

        PerformanceTest(std::wofstream* p = nullptr) : randomNumberGenerator(0),
            randomNumberDistribution(0, randomRange), m_p(p)
        {
        }

        double run()
        {
            PerformanceTimer timer;
            timer.start();

			for (int i = 0; i < numberOfIterations; i++)
			{
				testIteration(randomNumberDistribution(randomNumberGenerator));
			}

            timer.stop();
            return timer.toSeconds();
        }
};

template <typename Container>
class PushFrontTest : public PerformanceTest<Container>
{
    virtual void testIteration(int newSize)
    {
		while (size < newSize)
		{
			container.push_front(size++);
		}

		for (; size > newSize; size--)
		{
			container.pop_front();
		}
    }
};

template <typename Container>
class PushBackTest : public PerformanceTest<Container>
{
    virtual void testIteration(int newSize)
    {
		while (size < newSize)
		{
			container.push_back(size++);
		}

		for (; size > newSize; size--)
		{
			container.pop_back();
		}
    }
};

template <typename Container>
class MapTest : public PerformanceTest<Container>
{
    virtual void testIteration(int newSize)
    {
		while (size < newSize)
		{
			container.insert(std::pair<char, int>(size++, size));
		}

		while (size > newSize)
		{
			container.erase(--size);
		}
    }
};

template <typename Container>
class SetTest : public PerformanceTest<Container>
{
    virtual void testIteration(int newSize)
    {
		while (size < newSize)
		{
			container.insert(size++);
		}

		while (size > newSize)
		{
			container.erase(--size);
		}
    }
};

class Performance
{
    template <typename StlContainer, typename FastContainer>
    void printTestStatus(const char *name, StlContainer &stlContainer, FastContainer &fastContainer)
    {
        std::cout << name << " - Default STL Allocator : " << std::fixed << stlContainer.run() << " seconds." << std::endl;
        std::cout << name << " - Memory Pool Allocator : " << std::fixed << fastContainer.run() << " seconds." << std::endl;
        std::cout << std::endl;
		*m_p<< name << " - Default STL Allocator : " << std::fixed << stlContainer.run() << " seconds." << std::endl;
		*m_p << name << " - Memory Pool Allocator : " << std::fixed << fastContainer.run() << " seconds." << std::endl;
		*m_p << endl;
    }

    void runTests()
    {
        typedef int DataType;
        typedef Moya::Allocator<DataType, growSize> MemoryPoolAllocator;

        PushFrontTest<std::forward_list<DataType>> pushFrontForwardListTestStl;
        PushFrontTest<std::forward_list<DataType, MemoryPoolAllocator>> pushFrontForwardListTestFast;
        printTestStatus("ForwardList PushFront", pushFrontForwardListTestStl, pushFrontForwardListTestFast);

        PushFrontTest<std::list<DataType>> pushFrontListTestStl;
        PushFrontTest<std::list<DataType, MemoryPoolAllocator>> pushFrontListTestFast;
        printTestStatus("List PushFront", pushFrontListTestStl, pushFrontListTestFast);

        PushBackTest<std::list<DataType>> pushBackListTestStl;
        PushBackTest<std::list<DataType, MemoryPoolAllocator>> pushBackListTestFast;
        printTestStatus("List PushBack", pushBackListTestStl, pushBackListTestFast);

        MapTest<std::map<DataType, DataType, std::less<DataType>>> mapTestStl;
        MapTest<std::map<DataType, DataType, std::less<DataType>, MemoryPoolAllocator>> mapTestFast;
        printTestStatus("Map", mapTestStl, mapTestFast);

        SetTest<std::set<DataType, std::less<DataType>>> setTestStl;
        SetTest<std::set<DataType, std::less<DataType>, MemoryPoolAllocator>> setTestFast;
        printTestStatus("Set", setTestStl, setTestFast);
    }


    public:

        Performance(int argumentCount, char **arguments, std::wofstream* p=nullptr)
			:m_p(p)
        {

        }

        int run()
        {
            std::cout << "Allocator performance measurement example" << std::endl;
			*m_p      << "Allocator performance measurement example" << std::endl;
            std::cout << "Version: 1.0" << std::endl << std::endl;
			*m_p      << "Version: 1.0" << std::endl << std::endl;

            runTests();
            return 0;
        }
		std::wofstream* m_p;
};

#endif
