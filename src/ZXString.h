#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <iosfwd>

#ifdef ZX_HAVE_QT
	class QString;
#endif

namespace ZXing {

/// <summary>
/// This is UTF-8 string class (i.e. it keeps data internally as UTF-8).
/// </summary>
class String
{
public:
	String(const std::string& other) : m_utf8(other) {;}
	String(const char* i_utf8 = nullptr, int i_len = -1) {
		if (i_utf8 != nullptr) {
			if (i_len >= 0) {
				m_utf8.append(i_utf8, i_len);
			}
			else {
				m_utf8.append(i_utf8);
			}
		}
	}

	String(const wchar_t* i_wstr);
	String(const wchar_t* i_begin, const wchar_t* i_end);
	String(const wchar_t* i_wstr, int i_len);

	bool empty() const											{ return m_utf8.empty(); }
	int byteCount() const										{ return static_cast<int>(m_utf8.length()); }
	int charCount() const;	// count the number of characters (which may not same as byte count)

	void appendUtf8(const char* str)							{ m_utf8.append(str); }
	void appendUtf8(const char* str, int len)					{ m_utf8.append(str, len); }
	void appendUtf8(const uint8_t* str)							{ m_utf8.append((const char*)str); }
	void appendUtf8(const uint8_t* str, int len)				{ m_utf8.append((const char*)str, len); }
	void appendUcs2(const uint16_t* ucs2);
	void appendUcs2(const uint16_t* ucs2, int len);
	void appendUtf16(const uint16_t* utf16, int len);
	void appendUtf16(const std::vector<uint16_t>& utf16);
	void appendUtf32(const uint32_t* utf32, int len);
	void appendUtf32(const std::vector<uint32_t>& utf32);

	const char* utf8() const { return m_utf8.c_str(); }
	void toUtf16(std::vector<uint16_t>& buffer) const;
	void toUtf32(std::vector<uint32_t>& buffer) const;
	void toWString(std::vector<wchar_t>& buffer) const;
	std::wstring toWString() const;

	std::string toStdString() const
	{
		return m_utf8;
	}

	bool operator==(const String& other) const
	{
		return m_utf8 == other.m_utf8;
	}

	bool operator!=(const String& other) const
	{
		return m_utf8 != other.m_utf8;
	}

	bool operator<(const String& other) const
	{
		return m_utf8 < other.m_utf8; // this is a property of UTF-8
	}

	bool operator<=(const String& other) const
	{
		return m_utf8 <= other.m_utf8; // this is a property of UTF-8
	}

	bool operator>(const String& other) const
	{
		return m_utf8 > other.m_utf8; // this is a property of UTF-8
	}

	bool operator>=(const String& other) const
	{
		return m_utf8 >= other.m_utf8; // this is a property of UTF-8
	}
	
	String operator+(const String& other) const
	{
		String sum(*this);
		return sum += other;
	}

	String& operator+=(const String& other)
	{
		m_utf8.append(other.m_utf8.begin(), other.m_utf8.end());
		return *this;
	}
	
#ifdef NB_HAVE_QT
	String(const QString& qstr);
	operator QString() const;
#endif

	friend std::ostream& operator<<(std::ostream& out, const String& str);
	friend std::wostream& operator<<(std::wostream& out, const String& str);

private:
	std::string m_utf8;
};

} // namespace ZXing
