#include "pch.h"
#include "StringConverter.h"
#include <sstream>


//-----------------------------------------------------------------------
std::string StringConverter::toString(float val, unsigned short precision, 
    unsigned short width, char fill, std::ios::fmtflags flags)
{
    std::stringstream stream;
    stream.precision(precision);
    stream.width(width);
    stream.fill(fill);
    if (flags)
        stream.setf(flags);
    stream << val;
    return stream.str();
}
//-----------------------------------------------------------------------
std::string StringConverter::toString(int val, 
    unsigned short width, char fill, std::ios::fmtflags flags)
{
    std::stringstream stream;
	stream.width(width);
    stream.fill(fill);
    if (flags)
        stream.setf(flags);
    stream << val;
    return stream.str();
}
//-----------------------------------------------------------------------
std::string StringConverter::toString(unsigned int val, 
    unsigned short width, char fill, std::ios::fmtflags flags)
{
    std::stringstream stream;
    stream.width(width);
    stream.fill(fill);
    if (flags)
        stream.setf(flags);
    stream << val;
    return stream.str();
}
//-----------------------------------------------------------------------
std::string StringConverter::toString(unsigned long val, 
    unsigned short width, char fill, std::ios::fmtflags flags)
{
    std::stringstream stream;
    stream.width(width);
    stream.fill(fill);
    if (flags)
        stream.setf(flags);
    stream << val;
    return stream.str();
}

std::string StringConverter::toString(long val, 
    unsigned short width, char fill, std::ios::fmtflags flags)
{
    std::stringstream stream;
	stream.width(width);
    stream.fill(fill);
    if (flags)
        stream.setf(flags);
    stream << val;
    return stream.str();
}

//-----------------------------------------------------------------------
float StringConverter::parseFloat(const std::string& val)
{
	// Use istringstream for direct correspondence with toString
	std::istringstream str(val);
	float ret = 0;
	str >> ret;

    return ret;
}
//-----------------------------------------------------------------------
int StringConverter::parseInt(const std::string& val)
{
	// Use istringstream for direct correspondence with toString
	std::istringstream str(val);
	int ret = 0;
	str >> ret;

    return ret;
}
//-----------------------------------------------------------------------
unsigned int StringConverter::parseUnsignedInt(const std::string& val)
{
	// Use istringstream for direct correspondence with toString
	std::istringstream str(val);
	unsigned int ret = 0;
	str >> ret;

	return ret;
}
//-----------------------------------------------------------------------
long StringConverter::parseLong(const std::string& val)
{
	// Use istringstream for direct correspondence with toString
	std::istringstream str(val);
	long ret = 0;
	str >> ret;

	return ret;
}
//-----------------------------------------------------------------------
unsigned long StringConverter::parseUnsignedLong(const std::string& val)
{
	// Use istringstream for direct correspondence with toString
	std::istringstream str(val);
	unsigned long ret = 0;
	str >> ret;

	return ret;
}



