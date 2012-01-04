#include "pch.h"
#include "IniFileManager.h"

bool IniFileManager::openIniFile( const std::string & fileName )
{
	
	return true;
}

void  IniFileManager::getSectionName( std::vector<std::string> & nameVec )
{
	nameVec.clear();
	for ( sectionMapItor it = m_sectionMap.begin() ; it != m_sectionMap.end() ; it++ )
	{
		nameVec.push_back( it->first );
	}
}

void IniFileManager::getKeyName( const std::string & sectionName , std::vector<std::string> & nameVec )
{

}

std::string IniFileManager::getValue( const std::string & sectionName , const std::string & keyName )
{
	return "";
}

bool IniFileManager::setValue( const std::string & sectionName , const std::string & keyName , const std::string & value )
{
	return true;
}