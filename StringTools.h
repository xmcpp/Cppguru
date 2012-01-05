#ifndef __STRINGTOOLS_H__
#define __STRINGTOOLS_H__

class StringTools
{
public:
	/***���ո����ķָ�����и��ַ���
	@param srcString Դ�ַ���
	@param stringVec �����и���ַ����б�
	@param spliteChar ���÷ָ��ַ�
	*/
	static void splitString( const std::string & srcString , std::vector<std::string> & stringVec , const char splitChar = ' ' );
	
	/***ȥ��ָ���ַ������˵Ŀո����
	@param srcString Դ�ַ���
	*/
	static void trimBoth( std::string & srcString );
};

#endif //__STRINGTOOLS_H__
