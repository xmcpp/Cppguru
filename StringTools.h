#ifndef __STRINGTOOLS_H__
#define __STRINGTOOLS_H__

class StringTools
{
public:
	/***按照给定的分割符，切割字符串
	@param srcString 源字符串
	@param stringVec 返回切割后字符串列表
	@param spliteChar 设置分割字符
	*/
	static void splitString( const std::string & srcString , std::vector<std::string> & stringVec , const char splitChar = ' ' );
	
	/***去除指定字符串两端的空格符号
	@param srcString 源字符串
	*/
	static void trimBoth( std::string & srcString );
};

#endif //__STRINGTOOLS_H__
