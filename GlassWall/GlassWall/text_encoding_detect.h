#pragma once
#ifndef TEXT_ENCODING_DETECT_H_
#define TEXT_ENCODING_DETECT_H_



#include <stddef.h>

namespace Emmy
{ 
namespace Common
{
	class TextEncodingDetect
	{
	public:
		enum Encoding
		{
			None,				// Unknown or binary
			ANSI,				// 0-255
			ASCII,				// 0-127
			UTF8_BOM,			// UTF8 with BOM
			UTF8_NOBOM,			// UTF8 without BOM
			UTF16_LE_BOM,		// UTF16 LE with BOM
			UTF16_LE_NOBOM,		// UTF16 LE without BOM
			UTF16_BE_BOM,		// UTF16-BE with BOM
			UTF16_BE_NOBOM,		// UTF16-BE without BOM
		};

		TextEncodingDetect();
		~TextEncodingDetect();

		static Encoding CheckBOM(const unsigned char *pBuffer, size_t size);		// Just check if there is a BOM and return 
		Encoding DetectEncoding(const unsigned char *pBuffer, size_t size) const;	// Check BOM and also guess if there is no BOM
		static int GetBOMLengthFromEncodingMode(Encoding encoding);			// Just return the BOM length of a given mode

		void SetNullSuggestsBinary(bool null_suggests_binary) { null_suggests_binary_ = null_suggests_binary; }
		void SetUtf16UnexpectedNullPercent(int percent);
		void SetUtf16ExpectedNullPercent(int percent);

	private:
		TextEncodingDetect(const TextEncodingDetect&);
		const TextEncodingDetect& operator=(const TextEncodingDetect&);

		static const unsigned char* utf16_bom_le_;
		static const unsigned char* utf16_bom_be_;
		static const unsigned char* utf8_bom_;

		bool	null_suggests_binary_;
		int		utf16_expected_null_percent_;
		int		utf16_unexpected_null_percent_;

		Encoding CheckUTF8(const unsigned char *pBuffer, size_t size) const;				// Check for valid UTF8 with no BOM
		static Encoding CheckUTF16NewlineChars(const unsigned char *pBuffer, size_t size);	// Check for valid UTF16 with no BOM via control chars
		Encoding CheckUTF16ASCII(const unsigned char *pBuffer, size_t size) const;		// Check for valid UTF16 with no BOM via null distribution
		static bool DoesContainNulls(const unsigned char *pBuffer, size_t size);			// Check for nulls
	};

} // Emmy.Common
} // Emmy

//////////////////////////////////////////////////////////////////////

#endif
