/**********************************************************************
ini�ļ���ȡ�ͱ������

Desc:���ڶ�ȡini�ļ���section��key-value��ͬʱ�ṩ���湦��

Author: ���

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
