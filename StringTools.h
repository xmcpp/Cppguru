#ifndef __STRINGTOOLS_H__
#define __STRINGTOOLS_H__

class StringTools
{
public:
	static void splitString( const std::string & srcString , std::vector<std::string> & stringVec , const char splitChar = ' ' );
};

#endif //__STRINGTOOLS_H__
