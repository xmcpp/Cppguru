/**********************************************************************
ini文件读取和保存对象

Desc:用于读取ini文件的section和key-value，同时提供保存功能

Author: 徐淼

Date: 2012.1.4

Update: 
***********************************************************************/
#ifndef __INIFILEMANAGER_H__
#define __INIFILEMANAGER_H__

class IniFileManager
{
public:
	
public:
	bool openIniFile( const std::string & fileName );
	void  getSectionName( std::vector<std::string> & nameVec );
	void getKeyName( const std::string & sectionName , std::vector<std::string> & nameVec );
	std::string getValue( const std::string & sectionName , const std::string & keyName );
	bool setValue( const std::string & sectionName , const std::string & keyName , const std::string & value );
	

private:
	std::map<std::string , std::string> m_keyValueMap;
	typedef std::map<std::string , std::string>::iterator keyMapItor;
	std::map<std::string , std::map<std::string , std::string> > m_sectionMap;
	typedef std::map<std::string , std::map<std::string , std::string> >::iterator sectionMapItor;
};

#endif //__INIFILEMANAGER_H__
