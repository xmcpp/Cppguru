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
	bool loadIniFile( const std::string & fileName );
	void  getSectionName( std::vector<std::string> & nameVec );
	void getKeyName( const std::string & sectionName , std::vector<std::string> & nameVec );
	std::string getValue( const std::string & sectionName , const std::string & keyName );
	bool saveIniFile();
	
	bool hasSectionName( const std::string & sectionName );
	bool hasKeyName( const std::string & sectionName , const std::string & keyName );

	bool createSection( const std::string & sectionName );
	bool destroySection( const std::string & sectionName );
	bool insertKey( const std::string & sectionName , const std::string & keyName , const std::string & value );
	bool removeKey( const std::string & sectionName , const std::string & keyName );
	bool updateKey( const std::string & sectionName , const std::string & keyName , const std::string & value );
	//还需要处理前后空格
private:
	bool isSectionName( const std::string & str );
	void parseSectionName( const std::string & str , std::string & sectionName );
	bool isKeyValue( const std::string & str );
	void parseKeyValue( const std::string & str , std::string & keyName , std::string & value );
	void clearAllData();
private:
	std::map<std::string , std::map<std::string , std::string> > m_sectionMap;
	typedef std::map<std::string , std::map<std::string , std::string> >::iterator sectionMapItor;
	typedef std::map<std::string , std::string>::iterator keyMapItor;

	std::string m_fileName;
};

#endif //__INIFILEMANAGER_H__
