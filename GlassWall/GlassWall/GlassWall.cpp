// GlassWall.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <ctype.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <locale>
#include <codecvt>
#include <chrono>
#include <vector>
#include<cctype>
#include <algorithm>
#include <cstdlib>
#include <forward_list>
#include <limits>
#include <random>
#include <iterator>
#include <list>
#include <map>
#include <memory>

#include <iomanip>      // std::setw

#include "text_encoding_detect.h"
// #include "MemTracker.h"
#include "Allocator.h"
#include "Performance.h"

#include "crc32.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "keccak.h"
#include "sha3.h"


using namespace Emmy::Common;
using namespace std;
#pragma warning (disable:4244)
#pragma warning (disable:4290)
///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
class A3
{
	int* m_ptrnIndex;
	//std::ofstream* p;
	static int m_nCounter;
public:
	//A3(std::ofstream* tp = NULL, int nIndex = 3333) //:p(tp)
	A3(int nIndex = 3333) //:p(tp)
	{
		if (nIndex > 100000)
		{
			throw (nIndex);
		}

		m_ptrnIndex = new int(nIndex);
		cout << typeid(*this).name() << " CTOR     @ = " << this << ",\t\t\tcounter =  " << m_nCounter++ << ", T* = " << m_ptrnIndex << endl;
		//*p << typeid(*this).name() << " CTOR     @ = " << this << ",\t\t\tcounter =  " << m_nCounter << endl;
		//p->flush();		 
	}
	/*
	A3(std::initializer_list<std::valarray<int> > nIndexList)
	{
	for (auto i = nIndexList.begin(); i != nIndexList.end(); ++i)
	{
	if (*i. > 100000)
	{
	throw (*i);
	}
	m_ptrnIndex = new int(*i);
	cout << typeid(*this).name() << " CTOR IL  @ = " << this << ",\t\t\tcounter =  " << m_nCounter++ << ", T* = " << m_ptrnIndex << endl;
	}
	}
	*/

	//-----------------------------------------------------------
	A3(std::initializer_list<int> nIndexList)
	{
		for (auto i = nIndexList.begin(); i != nIndexList.end(); ++i)
		{
			if (*i > 100000)
			{
				throw (*i);
			}
			m_ptrnIndex = new int(*i);
			cout << typeid(*this).name() << " CTOR IL  @ = " << this << ",\t\t\tcounter =  " << m_nCounter++ << ", T* = " << m_ptrnIndex << endl;
		}
	}

	//-----------------------------------------------------------
	void SetA3(int n)
	{
		*(m_ptrnIndex) = n;
	}
	//----------------------------------------------------------
	int* GetTDebug() const
	{
		return m_ptrnIndex;
	}

	//---------------------------------------------------------------
	// copy constructor
	A3(const A3& rhs)
	{
		m_ptrnIndex = new int(*(rhs.m_ptrnIndex));
		cout << typeid(*this).name() << " COPYCTOR @ = " << this << ", rhs = " << &rhs << ",\tcounter =  " << m_nCounter++ << ", T* = " << m_ptrnIndex << endl;
		//p = rhs.p;
		//*p << typeid(*this).name() << " COPYCTOR @ = " << this << ", rhs = " << &rhs << ",\tcounter =  " << m_nCounter++ << endl;
		//p->flush();

	}
	//---------------------------------------------------------------
	// copy assignment operator
	A3& operator = (const A3& rhs)
	{
		if (this == &rhs)
		{
			cout << typeid(*this).name() << " COPYSELFASSIGN @ = " << this << ", rhs = " << &rhs << ",\t\tT* = " << m_ptrnIndex << endl;
			//*p << typeid(*this).name() << " SELFASSIGN @ = " << this << ", rhs = " << &rhs << endl;
			//p->flush();
			return *this;
		}
		else
		{

			delete m_ptrnIndex;
			m_ptrnIndex = 0;
			m_ptrnIndex = new int(*(rhs.m_ptrnIndex));
			cout << typeid(*this).name() << " COPYASSIGN   @ = " << this << ", rhs = " << &rhs << ",\t\tT* = " << m_ptrnIndex << endl;
			//*p << typeid(*this).name() << " ASSIGN     @ = " << this << ", rhs = " << &rhs << endl;
			//p->flush();

			return *this;
		}
	}

	//Move Constructor for A3
	A3(const A3&& rhs) : m_ptrnIndex(nullptr)
	{
		//m_ptrnIndex = new int(*(rhs.m_ptrnIndex));

		*this = std::move(rhs);
		cout << typeid(*this).name() << " MOVECTOR @ = " << this << ", rhs = " << &rhs << ",\tcounter =  " << m_nCounter++ << ", T* = " << m_ptrnIndex << endl;
		//p = rhs.p;
		//*p << typeid(*this).name() << " MOVECTOR @ = " << this << ", rhs = " << &rhs << ",\tcounter =  " << m_nCounter << endl;
		//p->flush();


	}


	//---------------------------------------------------
	//Move Assignment operator for A3
	A3& operator = (A3&& rhs)
	{
		if (this == &rhs)
		{
			cout << typeid(*this).name() << " MOVE-SELFASSIGN @ = " << this << ", rhs = " << &rhs << ", T* = " << m_ptrnIndex << endl;
			//*p << typeid(*this).name() << " MOVE-SELFASSIGN @ = " << this << ", rhs = " << &rhs << endl;
			//p->flush();
			return *this;
		}
		else
		{

			delete m_ptrnIndex;
			m_ptrnIndex = 0;
			m_ptrnIndex = new int(*(rhs.m_ptrnIndex));
			cout << typeid(*this).name() << " MOVEASSIGN     @ = " << this << ", rhs = " << &rhs << ", T* = " << m_ptrnIndex << endl;
			//*p << typeid(*this).name() << " MOVEASSIGN     @ = " << this << ", rhs = " << &rhs << endl;
			//p->flush();
			rhs.m_ptrnIndex = nullptr;

			return *this;
		}

	}


	//----------------------------------------------------------------
	/*
	A3* operator = (const A3* rhs)
	{
	if (this == rhs)
	{
	cout << typeid(*this).name() << " SELFASSIGN @ = " << this << ", rhs = " << rhs << endl;
	return this;
	}
	else
	{

	delete m_ptrnIndex;
	m_ptrnIndex = 0;
	m_ptrnIndex = new int(*(rhs->m_ptrnIndex));
	cout << typeid(*this).name() << " ASSIGN     @ = " << this << ", rhs = " << rhs << endl;
	return this;
	}
	}

	*/


	A3& operator++()
	{
		++(*(m_ptrnIndex));
		return *this;
	}

	A3& operator--()
	{
		--(*(m_ptrnIndex));
		return *this;
	}

	A3 operator++(int)
	{
		A3 temp = *this;
		cout << "\tDEBUG operator++(int) A2 temp = " << temp << endl;
		++(*(m_ptrnIndex));
		return temp;
	}
	A3 operator--(int)
	{
		A3 temp = *this;
		cout << "\tDEBUG operator--(int) A2 temp = " << temp << endl;
		--(*(m_ptrnIndex));
		return temp;

	}

	//---------------------------------------------------------------

	//operator int(/* Emmy zajebava */) const	
	operator int() const
	{
		return *(m_ptrnIndex);
	}

	int operator()(int p)
	{

		*(m_ptrnIndex) = p;
		return *(m_ptrnIndex);
		//return *(m_ptrnIndex);
	}

	//---------------------------------------------------------------

	//http://www.tutorialspoint.com/cplusplus/subscripting_operator_overloading.htm
	//A3& operator[](int i)		{if (i > SIZEARRAY){cout << "Index out of bounds" << endl;return A2[0];} else return A2[i];}
	//---------------------------------------------------------------
	virtual ~A3()
	{
		//delete m_ptrnIndex;
		cout << typeid(*this).name() << " DTOR @ = " << this << ",\t\t\tcounter =  " << --m_nCounter << ", T* = " << m_ptrnIndex << endl;
		delete m_ptrnIndex;
		//*p << typeid(*this).name() << " DTOR @ = " << this << ",\tcounter =  " << --m_nCounter << endl;
		//p->flush();
		//m_ptrnIndex = 0;
		//*m_ptrnIndex = 0;

	}
	//---------------------------------------------------------------
	int* GetPtrnName() const
	{
		return m_ptrnIndex;
	}
	//---------------------------------------------------------------
	/* Emmy To do
	bool operator < (const A3& a1)
	{
	return *(this->GetPtrnName()) < *(a1.GetPtrnName());
	}
	*/
	//private:
	friend ostream& operator << (ostream &out, A3 &a2);
	friend istream& operator >> (istream &in, A3 &a2);

	friend bool operator== (A3 &a1, A3& a2);
	friend bool operator== (A3 &a1, const int index);
	friend bool operator== (int index, A3 &a1);
	friend bool operator!= (A3 &a1, A3& a2);

	friend bool operator > (A3 &cC1, A3 &cC2);
	friend bool operator<= (A3 &cC1, A3 &cC2);
	friend bool operator < (A3 &cC1, A3 &cC2);
	friend bool operator>= (A3 &cC1, A3 &cC2);

	friend int operator + (A3 &cC1, A3 &cC2);
	friend int operator - (A3 &cC1, A3 &cC2);
	friend int operator * (A3 &cC1, A3 &cC2);
	friend int operator / (A3 &cC1, A3 &cC2);
	friend int operator % (A3 &cC1, A3 &cC2);
	//friend bool operator % (std::valarray<A3>&cC1, const int n);



};

//----------------------------------------------------------
int A3::m_nCounter = 0;
//----------------------------------------------------------
ostream& operator<< (ostream &out, A3 &a2)
{

	int temp = *(a2.GetPtrnName());
	out << temp << ",";
	return out;
}

istream& operator>>(istream &in, A3 &a2)
{

	/*
	char temp[String::CINLIM];
	is.get(temp, String::CINLIM);
	if (is)
	{
	st = temp;
	}
	while (is && is.get() != '\n')
	{
	continue;
	}
	return is;
	*/

	int temp = 0;
	in >> temp;
	//in.get(&temp,20);
	if ((!in.bad()) && (temp != 0))
	{
		a2 = temp;
		return in;
	}

	in.setstate(ios_base::failbit);
	return in;
}

int operator + (A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) + *(cC2.GetPtrnName());

}


//---------------------------------------------------
int operator- (A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) - *(cC2.GetPtrnName());

}

//---------------------------------------------------

int operator* (A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) * *(cC2.GetPtrnName());

}

int operator /(A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) / *(cC2.GetPtrnName());

}


int operator % (A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) % *(cC2.GetPtrnName());

}

/*
bool operator % (std::valarray<A3>&cC1, const int n)
{

//std::valarray<bool> even = (cC1 % n) == 0);
return (cC1%n == 0);
//return *(cC1.GetPtrnName()) %  n);

}

*/

//--------------------------------------------------
bool operator== (A3 &a1, A3&a2)
{
	return *(a1.GetPtrnName()) == *(a2.GetPtrnName());
}

//---------------------------------------------------
bool operator== (A3 &a1, const int index)
{
	return *(a1.GetPtrnName()) == index;
}

//---------------------------------------------------
bool operator== (int index, A3 &a1)
{
	return  index == *(a1.GetPtrnName());
}
//---------------------------------------------------
bool operator!= (A3 &a1, A3& a2)
{
	return !(a1 == a2);
}
//----------------------------------------------------------
bool operator> (A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) > *(cC2.GetPtrnName());
}
//----------------------------------------------------------
bool operator<= (A3 &cC1, A3 &cC2)
{
	return  *(cC1.GetPtrnName()) <= *(cC2.GetPtrnName());
}
//----------------------------------------------------------
bool operator< (A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) < *(cC2.GetPtrnName());
}
//----------------------------------------------------------
bool operator >= (A3 &cC1, A3 &cC2)
{
	return *(cC1.GetPtrnName()) >= *(cC2.GetPtrnName());
}


///////////////////////////////////////////////////////////
struct TextFragment
{
	unsigned int m_index{};
	size_t hash{};
	std::wstring  m_ptrOrig{};	
};

//---------------------------------------------------------
	void PrintBinaryAndNumber16(unsigned int uiNumber, std::wofstream* p = NULL)
	//void PrintBinaryAndNumber16(unsigned int uiNumber)
	{
		int n = 0;
		//cout << "[" << uiNumber << "] " << cout.width(4);
		//*p   << "[" << uiNumber << "] " << cout.width(4);

		//cout << "[" << cout.width(0) <<uiNumber << "] " ;
		//*p << "[" << cout.width(0) << uiNumber << "] ";
		cout << std::setw(0);
		*p << std::setw(0);

		cout <<(char)uiNumber<<" "<< "[" << uiNumber << "]";
		*p <<(char)uiNumber << " " << "[" << uiNumber << "]";
		for (int i = 15; i >= 0; --i, ++n)
		{
			if (n % 4 == 0)
			{
				cout << " ";
				//*p << " ";
			}

			//unsigned t = uiNumber >> i;
			//cout << "t = " << t << ", i = " << i << endl;
			//*p   << "t = " << t << ", i = " << i << endl;
			//cout << (((t) % 2) ? '1' : '0');
			//*p   << (((t) % 2) ? '1' : '0');
			cout << (((uiNumber >> i) % 2) ? '1' : '0');
			*p << (((uiNumber >> i) % 2) ? '1' : '0');
		}

		cout << " ";
		*p << " " << endl;;

	}


	////////////////////////////////////////////////////////////////////
	
	template<class _Elem,
		unsigned long _Mymax = 0x10ffff,
		codecvt_mode _Mymode = (codecvt_mode)0>
		class Mycodecvt : public std::codecvt_utf16<_Elem, _Mymax, _Mymode>
	{
	public:
		explicit Mycodecvt(std::wofstream* p = nullptr,size_t _Refs = 0): std::codecvt_utf16<_Elem,_Mymax,_Mymode> (_Refs)
		{
			mp = p;
			wcout << typeid(this).name() << " CTOR  @ = " << this << endl;
			*mp << typeid(this).name() << " CTOR  @ = " << this << endl;
		}
		virtual ~Mycodecvt() 
		{
			wcout << typeid(this).name() << " DTOR  @ = " << this << endl;
			*mp << typeid(this).name() << " DTOR  @ = " << this << endl;
		}
	private:
		std::wofstream* mp = nullptr;
		
	};

	////////////////////////////////////////////////////////////////
	template<class _Elem,
		unsigned long _Mymax = 0x10ffff,
		codecvt_mode _Mymode = (codecvt_mode)0>
		class Iriacodecvt : public Mycodecvt<_Elem, _Mymax, _Mymode>
	{
	public:
		explicit Iriacodecvt(std::wofstream* p = nullptr,size_t _Refs = 0) : Mycodecvt<_Elem, _Mymax, _Mymode >(p,_Refs)
		{
			mp = p;
			wcout << typeid(this).name() << " CTOR  @ = " << this << endl;
			*mp << typeid(this).name() << " CTOR  @ = " << this << endl;
		}
		virtual ~Iriacodecvt()
		{
			wcout << typeid(this).name() << " DTOR  @ = " << this << endl;
			*mp << typeid(this).name() << " DTOR  @ = " << this << endl;
		}

	private:
		std::wofstream* mp = nullptr;
	};

	//new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>)
	

	/////////////////////////////////////////////////////////////////////
	// apply BOM-sensitive UTF-16 facet std::wistream for the input file
	///////////////////////////////////////////////////////////////////// std::wofstream* p=nullptr
	//void ApplyBOM_To_UTF_16_facet(std::wistream& fs)
	void ApplyBOM_To_UTF_16_facet(std::wistream& fs, std::wofstream* p = nullptr)
	{	
		//fs.imbue(std::locale(fs.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
		//fs.imbue(std::locale(fs.getloc(), new Mycodecvt<wchar_t, 0x10ffff, std::consume_header>()));
		// Iria fs.imbue(std::locale(fs.getloc(), new Iriacodecvt<wchar_t, 0x10ffff, std::consume_header>(p,0)));
	}

/////////////////////////////////////////////////////////////////////
// Prints the data the index and Original string stream to Console and Log file
/////////////////////////////////////////////////////////////////////
void PrintTextFragment(const std::vector<TextFragment>& vecTFrag, std::wofstream* p)
{
	//std::vector<TextFragment>::const_iterator iterFrag;
	for ( auto iterFrag = vecTFrag.cbegin(); iterFrag != vecTFrag.cend(); iterFrag++)
	{		
		wcout << iterFrag->m_ptrOrig <<" \t("<<iterFrag->hash<<")"<<std::endl;
		*p << iterFrag->m_ptrOrig << " \t(" << iterFrag->hash << ")" << std::endl;
		
	}
}

///////////////////////////////////////////////////////////////////
void PrintTokenedString(const std::vector<std::wstring>& strToken,std::wofstream* p)
{
	for (auto iterFrag = strToken.cbegin(); iterFrag != strToken.cend(); iterFrag++)
	{
		wcout << *iterFrag <<  std::endl;
		*p   << *iterFrag << std::endl;
	}

}

/////////////////////////////////////////////////////////////////////
// Test a character for alphanumeric value,
// return bool
/////////////////////////////////////////////////////////////////////
bool my_isalnum(char ch)
{
	return std::isalnum(static_cast<unsigned char>(ch));
}

/////////////////////////////////////////////////////////////////////
// Test for  character space
// return bool
/////////////////////////////////////////////////////////////////////
bool my_isspace(char ch)
{
	return std::isspace(static_cast<unsigned char>(ch));
}


//////////////////////////////////////////////////////////////////////
// General Purpose Hash Function Algorithms
// http://www.partow.net/programming/hashfunctions/index.html

//unsigned int RSHash(const char* str, unsigned int len)
unsigned int RSHash(const  std::wstring& ws, std::wofstream* p = NULL)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int i = 0;
	//wcout << "---------------------------------" << endl;
	
	const wchar_t* str = ws.c_str();
	size_t len = ws.length();
	*p << "---------------------------------" << endl;
	*p << "string len = "<<len << endl;
	*p << "a = " << endl;
	for (i = 0; i < len; str++, i++)
	{
		
		hash = hash * a + (*str);
		*p << a << ", hash = " << hash << endl;
		a = a * b;
	}

	//wcout << "---------------------------------" << endl;
	*p << "---------------------------------" << endl;

	return hash;
}
/* End Of RS Hash Function */

// http://www.partow.net/programming/hashfunctions/index.html#RSHashFunction
//unsigned int JSHash(const char* str, unsigned int length)
unsigned int JSHash(const  std::wstring& ws, std::wofstream* p = NULL)
{
	unsigned int hash = 1315423911;
	unsigned int i = 0;
	const wchar_t* str = ws.c_str();
	size_t len = ws.length();	
	*p << "---------------------------------" << endl;
	*p << "string len = " << len << endl;	
	for (i = 0; i < len; ++str, ++i)
	{
		hash ^= ((hash << 5) + (*str) + (hash >> 2));
		*p << "hash = " << hash << endl;
	}

	//wcout << "---------------------------------" << endl;
	*p << "---------------------------------" << endl;
	return hash;
}

//////////////////////////////////////////////////////////////
// http://www.partow.net/programming/hashfunctions/index.html#RSHashFunction
//unsigned int PJWHash(const char* str, unsigned int length)
unsigned int PJWHash(const  std::wstring& ws, std::wofstream* p = NULL)
{
	const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
	const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
	const unsigned int HighBits =(unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	unsigned int i    = 0;

	const wchar_t* str = ws.c_str();
	size_t len = ws.length();
	*p << "---------------------------------" << endl;
	*p << "string len = " << len << endl;

	for (i = 0; i < len; ++str, ++i)
	{
		hash = (hash << OneEighth) + (*str);
		*p << "hash = " << hash << endl;

		if ((test = hash & HighBits) != 0)
		{
			*p << "&    = " << (hash & HighBits) << endl;
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
			//*p << "\thash = " << hash << endl;
		}
	}

	*p << "---------------------------------" << endl;
	return hash;
}

///////////////////////////////////////////////////////////
// 05 - SDBM Hash Function
// http://www.partow.net/programming/hashfunctions/index.html#RSHashFunction
//unsigned int SDBMHash(const char* str, unsigned int length)
unsigned int SDBMHash(const  std::wstring& ws, std::wofstream* p = NULL)
{
	unsigned int hash = 0;
	unsigned int i = 0;
	const wchar_t* str = ws.c_str();
	size_t len = ws.length();
	*p << "---------------------------------" << endl;
	*p << "string len = " << len << endl;

	for (i = 0; i < len; ++str, ++i)
	{

		hash = (*str) + (hash << 6) + (hash << 16) - hash;
		*p << "hash = " << hash << endl;
	}

	*p << "---------------------------------" << endl;
	return hash;
}
//////////////////////////////////////////////////////////////
size_t HashFuntionOnString(const  std::wstring& ws, std::wofstream* p = NULL)
{
	std::hash<std::wstring> hash_fn;
	size_t hash = hash_fn(ws);
	return hash;
}


//////////////////////////////////////////////////////////////
// https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string
void  split(std::vector<std::wstring>& tokens,const std::wstring &text, const wchar_t sep) 
{	
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) 
	{
		if (end != start) 
		{
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) 
	{
		tokens.push_back(text.substr(start));
	}
	
}

/////////////////////////////////////////////////////////////////////
// Called to to screen the encoded input file
/////////////////////////////////////////////////////////////////////
void RedactionofWideChar(std::vector<std::wstring>& VecSubToken,int& numETX, std::wifstream& fs,
	std::vector<TextFragment>& vecTFrag, wchar_t ETX, const TextEncodingDetect::Encoding& refencodig,
	std::wofstream* p = NULL)
{   
	//char16_t carriage = L'\r';
	wchar_t carriage = L'\r';		
	std::wstring wstrLine;
	std::wstring wstrToken;
	//std::vector<std::wstring> VecSubToken;
	unsigned int indexCount = 0;	
	
		while (std::getline(fs, wstrLine, ETX))
		{
			//numETX++;
			TextFragment tFrag;			
			wstrToken.clear();			
			tFrag.m_index = indexCount;
			for (auto c : wstrLine)
			{							
				if (refencodig == TextEncodingDetect::UTF16_LE_BOM || 
					refencodig == TextEncodingDetect::UTF16_LE_NOBOM)					
				{
					if (((my_isalnum(c)) || my_isspace(c)) && (c != carriage))
					{
						wstrToken += c;
						++indexCount;	
						//PrintBinaryAndNumber16(c, p);
						//wcout << endl;
						//*p << endl;
					}					
				}
				else
				{
					return;
				}
				
			
			}
		
			//wcout << L"----------------------------------- " << endl;
			//*p << L"----------------------------------- " << endl;
			
			tFrag.m_ptrOrig = wstrToken;
			size_t len = wstrToken.length();
			//tFrag.hash = HashFuntionOnString(wstrToken, p);
			//tFrag.hash = RSHash(wstrToken, p);  // the better
			//tFrag.hash = JSHash(wstrToken, p);
			//tFrag.hash = PJWHash(wstrToken, p); // The best
			tFrag.hash = SDBMHash(wstrToken, p);  // The best
			split(VecSubToken, wstrToken, L' ');
			vecTFrag.push_back(std::move(tFrag));
			//vecTFrag.push_back(tFrag);
			numETX++;
		}
		
}

/////////////////////////////////////////////////////////////////////
// Read input file and verify
/////////////////////////////////////////////////////////////////////
void ReadInputFile(const wchar_t* filenamein, std::wifstream& fs, std::wofstream* p=nullptr)
{	
	if (!fs.good())
	{
		std::wcout << L"cannot open input file [" << filenamein << "]\n" << std::endl;
		*p << L"cannot open input file [" << filenamein << "]\n" << std::endl;
		return;
	}
}

/////////////////////////////////////////////////////////////////////
// print information for debugging purpose
/////////////////////////////////////////////////////////////////////
void PrintInformation( const std::vector<TextFragment>& vecTFrag, const wchar_t* filenamein,
					const wchar_t ETX, const int numETX, std::wofstream* p)
{	
	std::cout << "Size vecTFrag  = " << vecTFrag.size() << std::endl;
	*p << L"Size vecTFrag  = " << vecTFrag.size() << std::endl;
	std::cout << "Delim          = " << ETX << std::endl;
	*p << L"Delim          = " << (unsigned int)ETX << std::endl;
	std::wcout << L"Input file Name : (" << filenamein << ")" << std::endl;
	*p << L"Input file Name : (" << filenamein << ")" << std::endl;

	std::cout << "Number of ETX occurence: " << numETX << std::endl;
	*p << "Number of ETX occurence: " << numETX << std::endl;
	std::cout << std::endl;
	*p << endl;
	
}

/////////////////////////////////////////////////////////////////////
// DetectFileEncoding the type of enconding
// returns encoding type
/////////////////////////////////////////////////////////////////////
TextEncodingDetect::Encoding  DetectFileEncoding(const wchar_t*filenamein,
	                       const wchar_t* mode, std::wofstream* p= nullptr)
{	
	
	errno_t err;
	FILE *file = NULL;// _wfopen(filenamein, mode);
	err = _wfopen_s(&file, filenamein, mode);

	//if (file == NULL)
	if (file == NULL && !err)	
	{
		wprintf(L"\nCould not open file.\n");
		*p << L"\nCould not open file." << endl;
		return TextEncodingDetect:: None;
	}

	// Get file size
	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Read it all in
	unsigned char *buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	// Detect the encoding
	TextEncodingDetect textDetect;
	TextEncodingDetect::Encoding encoding = textDetect.DetectEncoding(buffer, fsize);

	wprintf(L"\nEncoding: ");
	*p << L"\nEncoding: ";
	if (encoding == TextEncodingDetect::None)
	{
		wprintf(L"Binary");
		*p << L"Binary" << endl;
	}
		
	else if (encoding == TextEncodingDetect::ASCII)
	{
		wprintf(L"ASCII (chars in the 0-127 range)");
		*p << L"ASCII (chars in the 0-127 range)" << endl;
	}
	else if (encoding == TextEncodingDetect::ANSI)
	{
		wprintf(L"ANSI (chars in the range 0-255 range)");
		*p << L"ANSI (chars in the range 0-255 range)" << endl;
	}
	else if (encoding == TextEncodingDetect::UTF8_BOM || encoding == TextEncodingDetect::UTF8_NOBOM)
	{
		wprintf(L"UTF-8");
		*p << L"UTF-8" << endl;
	}
	else if (encoding == TextEncodingDetect::UTF16_LE_BOM || encoding == TextEncodingDetect::UTF16_LE_NOBOM)
	{
		wprintf(L"UTF-16 Little Endian");
		*p << L"UTF-16 Little Endian" << endl;
	}
	else if (encoding == TextEncodingDetect::UTF16_BE_BOM || encoding == TextEncodingDetect::UTF16_BE_NOBOM)
	{
		wprintf(L"UTF-16 Big Endian");
		*p << L"UTF-16 Big Endian" << endl;
	}

	// Free up
	delete[] buffer;

	wprintf(L"\n");
	*p << L"\n" << endl;
	return encoding;

}

/////////////////////////////////////////////////////////////
// Candidate Exercise
/////////////////////////////////////////////////////////////
void CandidateExercise(std::wofstream* p)
{		
	wchar_t* mode = L"rb";
	const wchar_t* filenamein = L"IriaGlassWell.txt";     //Tested OK 
	//const wchar_t* filenamein = L"IriaGlassWell.pdf";     //Tested OK 
	wchar_t ETX = L'\u0394';						   //Tested OK	
	
	//const wchar_t* filenamein = L"IriaGlassWellBig.txt";   //Tested OK
	//const wchar_t* filenamein = L"IriaGlassWell300.txt";
	//wchar_t ETX = L'\u0394';						   //Tested OK
	
	std::vector<TextFragment> vecTFrag;
	std::vector<std::wstring> VecSubToken;
	int numETX = 0; 
		
	TextEncodingDetect::Encoding  encoding = DetectFileEncoding(filenamein, mode, p);
		
	//Open input file
	std::wifstream inputfs(filenamein, std::ios::binary);
	ReadInputFile(filenamein, inputfs, p);

	//apply BOM-sensitive UTF-16 facet  	
	ApplyBOM_To_UTF_16_facet(inputfs,p);
				
	//Redaction of the stream wide characters ithe input file.	
	RedactionofWideChar(VecSubToken,numETX, inputfs, vecTFrag, ETX, encoding,p);

	inputfs.close();
	
	// Print the output od redacted stream to Console and log file
	PrintTextFragment(vecTFrag, p);	
	std::wcout<<"++++++++++++++++++++++++++++++++++++++++"<< endl;
	*p << "++++++++++++++++++++++++++++++++++++++++" << endl;
	
	PrintTokenedString(VecSubToken, p);
	std::wcout <<"Number of Tokened String:"<<VecSubToken.size()<< endl;
	*p         <<"Number of Tokened String:" << VecSubToken.size() << endl;
	
	// Print the information of the results		
	PrintInformation(vecTFrag, filenamein, ETX, numETX,p);
	
}


////////////////////////////////////////////////////////
//Portable C++ Hashing Library
// http://create.stephan-brumme.com/hash-library/
//////////////////////////////////////////////////////
void Portable_CPP_HashingLibrary(std::wofstream* p)
{
	// syntax check
	/*
	if (argc < 2 || argc > 3)
	{
		std::cout << "./digest filename [--crc|--md5|--sha1|--sha256|--keccak|--sha3]" << std::endl;
		return ;
	}
	*/

	//const wchar_t* filename = "IriaGlassWellHashing1.txt";
	// parameters
	//std::string filename = argv[1];
	//std::string algorithm = argc == 3 ? argv[2] : "";
	std::string filename = "IriaGlassWellHashing1.txt";
	//std::string algorithm = "IriaGlassWellHashing2.txt";
	std::string algorithm = "--sha3";// "--md5";// "--crc";
	bool computeCrc32 = algorithm.empty() || algorithm == "--crc";
	bool computeMd5 = algorithm.empty() || algorithm == "--md5";
	bool computeSha1 = algorithm.empty() || algorithm == "--sha1";
	bool computeSha2 = algorithm.empty() || algorithm == "--sha2" || algorithm == "--sha256";
	bool computeKeccak = algorithm.empty() || algorithm == "--keccak";
	bool computeSha3 = algorithm.empty() || algorithm == "--sha3";

	CRC32  digestCrc32;
	MD5    digestMd5;
	SHA1   digestSha1;
	SHA256 digestSha2;
	Keccak digestKeccak(Keccak::Keccak256);
	SHA3   digestSha3(SHA3::Bits256);

	// each cycle processes about 1 MByte (divisible by 144 => improves Keccak/SHA3 performance)
	const size_t BufferSize = 144 * 7 * 1024;
	char* buffer = new char[BufferSize];

	// select input source: either file or standard-in
	std::ifstream file;
	std::istream* input = NULL;
	// accept std::cin, syntax will be: "./digest - --sha3 < data"
	if (filename == "-")
	{
		input = &std::cin;
	}
	else
	{
		// open file
		file.open(filename.c_str(), std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cerr << "Can't open '" << filename << "'" << std::endl;
			return ;
		}

		input = &file;
	}

	// process file
	while (*input)
	{
		input->read(buffer, BufferSize);
		std::size_t numBytesRead = size_t(input->gcount());

		if (computeCrc32)
			digestCrc32.add(buffer, numBytesRead);
		if (computeMd5)
			digestMd5.add(buffer, numBytesRead);
		if (computeSha1)
			digestSha1.add(buffer, numBytesRead);
		if (computeSha2)
			digestSha2.add(buffer, numBytesRead);
		if (computeKeccak)
			digestKeccak.add(buffer, numBytesRead);
		if (computeSha3)
			digestSha3.add(buffer, numBytesRead);
	}

	// clean up
	file.close();
	delete[] buffer;

	// show results
	if (computeCrc32)
	{
		std::cout << "CRC32:      " << digestCrc32.getHash() << std::endl;
		       *p << "CRC32:      " << (std::wstring*) &digestCrc32.getHash() << std::endl;
	}
	if (computeMd5)
	{
		std::cout << "MD5:        " << digestMd5.getHash() << std::endl;
	}
	if (computeSha1)
	{
		std::cout << "SHA1:       " << digestSha1.getHash() << std::endl;
	}
	if (computeSha2)
	{
		std::cout << "SHA2/256:   " << digestSha2.getHash() << std::endl;
	}
	if (computeKeccak)
	{
		std::cout << "Keccak/256: " << digestKeccak.getHash() << std::endl;
	}
	if (computeSha3)
	{
		std::cout << "SHA3/256:   " << digestSha3.getHash() << std::endl;
	}

}



////////////////////////////////////////////////////////////////

template <typename T>
struct mallocator {
#ifdef NDEBUG
	static const bool debug = false;
#else
	static const bool debug = true;
#endif

	std::wofstream* m_p;

	using value_type = T;

	mallocator() = default;
	template <class U>
	mallocator(const mallocator<U>& refalloc, std::wofstream* p = nullptr):
	//mallocator(std::wofstream* p ,const mallocator<U>& refalloc) :
		m_p(p)
	{
		cout << typeid(*this).name() << " COPYCTOR     @ = " << this << endl;
		//*m_p << typeid(*this).name() << " COPYCTOR     @ = " << this << endl;
	}

	T* allocate(std::size_t n) 
	{
		if (debug)
		{
			std::cout << "allocate(" << n << ") = "; 
			//*m_p << typeid(*this).name() << " CTOR  ( "<< n <<" )    @ = " ;
		}

		std::size_t myLimit = std::numeric_limits<std::size_t>::max() / sizeof(T);
		//myLimit = 5;
		if (n <= myLimit)
		{
			auto ptr = std::malloc(n * sizeof(T));
			if (ptr) 
			{
				if (debug)
				{
					//std::cout << ptr << '\n'; 
					cout << " CTOR  ( " << n << " )  ptr = " << ptr << endl;
					//*m_p << ptr << '\n';
				}
				return static_cast<T*>(ptr);
			}
		}

		if (debug)
		{
			std::cout << "[bad_alloc]\n"; 
			//*m_p << "[bad_alloc]\n";

		}
		throw std::bad_alloc();
	}
	void deallocate(T* ptr, std::size_t n) 
	{
		if (debug) 
		{
		  //std::cout << "deallocate(" << ptr << ", " << n << ")\n"; 
		  cout<<" DTOR  ( " << n << " )  ptr = "<< ptr <<endl;
			//*m_p << "deallocate(" << ptr << ", " << n << ")\n";
		}
		std::free(ptr);
	}
};

template <typename T, typename U>
inline bool operator == (const mallocator<T>&, const mallocator<U>&)
{
	return true;
}

template <typename T, typename U>
inline bool operator != (const mallocator<T>& a, const mallocator<U>& b) 
{
	return !(a == b);
}



////////////////////////////////////////////////////////////////
// http://coliru.stacked-crooked.com/a/9214894a7c7a921d
void FunCustomAllocator(std::wofstream* p)
{
	/*
	auto engine = std::mt19937_64{ std::random_device{}() };
	auto dist = std::uniform_int_distribution<int>{};
	auto rng = [&] {return dist(engine); };

	{
		// vector.
		auto c = std::vector<int, mallocator<int>>{};
		std::generate_n(std::back_inserter(c), 1024, rng);
	}

	{
		// forward_list
		auto c = std::forward_list<int, mallocator<int>>{};
		std::generate_n(std::front_inserter(c), 1024, rng);
	}
	*/
}
///////////////////////////////////////////////////////

struct MyObj 
{
	MyObj() 
	{
		std::cout << "This is the constructor" << std::endl;
	}
	MyObj(const MyObj& x) 
	{
		std::cout << "This is the copy constructor" << std::endl;
	}
};

///////////////////////////////////////////////////////////
template<typename T>
class MyAlloc : public std::allocator <T>
{
public:
	typedef size_t     size_type;
	typedef ptrdiff_t  difference_type;
	typedef T*         pointer;
	typedef const T*   const_pointer;
	typedef T&         reference;
	typedef const T&   const_reference;
	typedef T          value_type;


	template<typename U>
	struct rebind
	{
		typedef MyAlloc <U> other;
	};

	MyAlloc() 
	{

	}

	template<typename U>
	MyAlloc(const MyAlloc<U>&) 
	{

	}

	void construct(pointer p, const_reference t) 
	{
		std::cout << "Construct in the allocator" << std::endl;
		//new((void*)p) MyObj(t);
		//new((MyObj*)p) MyObj(t);
		//new MyObj(t); Emmy compiler error
	}

};



/////////////////////////////////////////////////
// How to overwrite the default behavor of the construct method 
// in the allocator class in C++ STL
// https://stackoverflow.com/questions/8089850/how-to-overwrite-the-default-behavor-of-the-construct-method-in-the-allocator-cl?rq=1
void FunCustomAllocator_2(std::wofstream* p) 
{
	//MyObj x;
	// std::list <MyObj, MyAlloc<MyObj>> list(5, x);

}
//////////////////////////////////////////////////
/*
template<typename T>
struct track_alloc : std::allocator<T> 
{
	typedef typename std::allocator<T>::pointer pointer;
	typedef typename std::allocator<T>::size_type size_type;

	template<typename U>
	struct rebind 
	{
		typedef track_alloc<U> other;
	};

	track_alloc() 
	{

	}

	template<typename U>
	track_alloc(track_alloc<U> const& u):std::allocator<T>(u)
	{

	}

	pointer allocate(size_type size,
		std::allocator<void>::const_pointer = 0) 
	{
		void * p = std::malloc(size * sizeof(T));
		if (p == 0)
		{
			throw std::bad_alloc();
		}
		return static_cast<pointer>(p);
	}

	void deallocate(pointer p, size_type) 
	{

		std::free(p);
	}
};

//---------------------------------------------------------
typedef std::map< void*, std::size_t, std::less<void*>,
	track_alloc< std::pair<void* const, std::size_t> > > track_type;

struct track_printer 
{
	track_type * track;
	track_printer(track_type * trackky) :track(trackky) 
	{
		//cout << typeid(*this).name() << " CTOR     @ = " << this << endl;
	}
	~track_printer() 
	{
		track_type::const_iterator it = track->begin();
		while (it != track->end()) 
		{
			std::cerr << "TRACK: leaked at " << it->first << ", "<< it->second << " bytes\n";
			++it;
			cerr <<typeid(*this).name() << " DTOR EmmyLinking     @ = " << this << endl;
		}
		//cout << typeid(*this).name() << " DTOR     @ = " << this << endl;
	}
};

//---------------------------------------------------------
track_type * get_map() 
{
	// don't use normal new to avoid infinite recursion.
	static track_type * track = new (std::malloc(sizeof *track)) track_type;
	static track_printer printer(track);
	return track;
}

//---------------------------------------------------------
void * operator new(std::size_t size) throw(std::bad_alloc) 
{
	// we are required to return non-null
	void * mem = std::malloc(size == 0 ? 1 : size);
	if (mem == 0) 
	{
		throw std::bad_alloc();
	}
	(*get_map())[mem] = size;
	return mem;
}

//---------------------------------------------------------
void operator delete(void * mem) throw() 
{
	if (get_map()->erase(mem) == 0) 
	{
		// this indicates a serious bug
		std::cerr << "bug: memory at "<< mem << " wasn't allocated by us\n";
	}
	std::free(mem);
}

*/
////////////////////////////////////////////////////
// How to track memory allocations in C++ (especially new/delete)
//https://stackoverflow.com/questions/438515/how-to-track-memory-allocations-in-c-especially-new-delete
void FunCustomAllocator_3(std::wofstream* p)

{



	//std::string *s = new std::string;
	//delete s;

	
	A3 * ptra3 = new  A3(3881);
	cout << *ptra3 << endl;
	*p << *ptra3 << endl;
	delete ptra3;
	
	std::auto_ptr<A3> aA3(new A3(604));
	cout << *aA3 << " @ = " << &aA3 << endl;
	*p << *aA3 << " @ = " << &aA3 << endl;
	std::auto_ptr<A3> aA32 = aA3;
	cout << *aA32 << " @ = " <<&aA32<< endl;
	*p << *aA32 << " @ = " << &aA32 << endl;
	
	std::unique_ptr<A3> a3uq(new A3(1847));
	cout << *a3uq << endl;
	*p << *a3uq << endl;
	

	std::shared_ptr<A3> a3sh(new A3(1847));
	cout << *a3sh << " , use count = " << a3sh.use_count() << endl;
	*p << *a3sh << " , use count = " << a3sh.use_count() << endl;
	std::shared_ptr<A3> a3sh2 = a3sh;
	cout << *a3sh2 << " , use count = " << a3sh2.use_count() << endl;
	*p << *a3sh2 << " , use count = " << a3sh2.use_count() << endl;
}

/////////////////////////////////////////////////////////

// https://github.com/moya-lang/Allocator/tree/master/Allocator
void FunCustomAllocator_4(std::wofstream* p) 
{
	using namespace Moya;
	Allocator<A3> a1;
	//Allocator<A3>* a2 = a1.allocate(10);
	A3* ptra3 = a1.allocate(1);
	a1.construct(ptra3, 1847);
	cout << *ptra3 << endl;
	*p << *ptra3 << endl;
	//delete ptra3;



}

////////////////////////////////////////////////////
void FunCustomAllocator_5(int argc, char **argv, std::wofstream* p=nullptr)
{
	cout << "\nargc = " << argc << ", argv =  " << *argv << endl;
	cout << endl;
	*p   << "\nargc = " << argc << ", argv =  " << *argv << endl;
	*p << endl;
	Performance project(argc, argv, p);
	project.run();
}
/////////////////////////////////////////////////////////////
// cout << typeid(*this).name() << " CTOR     @ = " << this << endl;
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	
	std::wofstream  m_ofstream;	
	m_ofstream.open("GlassWallLog_Encoded.txt", ios_base::trunc | ios_base::out);
	if (m_ofstream.is_open())
	{
		
		using std::chrono::steady_clock;
		auto start = std::chrono::high_resolution_clock::now();
		
		
		m_ofstream << "\n=====================WELLCOME GlassWall(Encoded)=====================\n" << endl;		
		m_ofstream.flush();		
		//--------------------------------------		
		CandidateExercise(&m_ofstream); 
		//Portable_CPP_HashingLibrary(&m_ofstream);
		//FunCustomAllocator(&m_ofstream);
		//FunCustomAllocator_2(&m_ofstream);
		//FunCustomAllocator_3(&m_ofstream);
		//FunCustomAllocator_4(&m_ofstream);
		FunCustomAllocator_5(argc, argv, &m_ofstream);
		

		//--------------------------------------
		
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - start;
		auto i_millis = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
		std::wcout << "Elapsed Time(miliseconds ): " << i_millis.count() << "ms" << endl;
		m_ofstream << "Elapsed Time(miliseconds ): " << i_millis.count() << "ms" << endl;
				
		m_ofstream << "=====================BYE-BYE==============================" << endl;
		m_ofstream.flush();
		m_ofstream.close();
		

	}
	//FunCustomAllocator_3();
    return 0;
}

