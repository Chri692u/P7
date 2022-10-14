#ifndef StringHelper_HH
#define StringHelper_HH

#include <string>
#include <streambuf>
#include <memory>
#include <iostream>
#include <stdarg.h>  // For va_start, etc.
#include <cstring>

class StringHelper {
public:
	static void RemoveCharacter(std::string* buffer, char character);
	static std::string RemoveCharacter(std::string buffer, char character);
	static void Trim(std::string* buffer);
	static std::string Trim(std::string buffer);
	static std::string StringFormat(const std::string fmt_str, ...);
};

#endif