#pragma once
#include <iostream>

namespace css
{
	class String
	{
	public:
		String();
		String(const String &other);
		String(String &&other);
		String(const char *str);
		~String();
		std::size_t GetLength() const;
		const char *GetData() const;
		String operator+(const String &other) const;

	private:
		std::size_t _length;
		char *_data;

		void _copyStringData(const char *str, std::size_t len, std::size_t offset = 0);
		static std::size_t _getStringLiteralLength(const char *str);

		friend std::ostream &operator<<(std::ostream &os, const String &s);
	};
}
