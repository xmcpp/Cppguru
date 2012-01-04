#include "pch.h"
#include "IniFileManager.h"
#include "StringTools.h"
#include <fstream>

bool IniFileManager::openIniFile( const std::string & fileName )
{
	m_fileName = fileName;
	
	std::fstream fs;
	fs.open( fileName.c_str() , std::ios::in | std::ios::_Nocreate );
	if( !fs.is_open() ) return false;
	
	std::string data;
	std::string key,value;
	std::string sectionName;
	while( std::getline( fs , data ) )
	{
		if( data == "" ) continue;

		if( isSectionName( data ) )
		{
			parseSectionName( data , sectionName );
			
			
		}
		else if( isKeyValue( data ) )
		{
			parseKeyValue( data , key , value );
		}
		
	}

	fs.close();
	
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
	nameVec.clear();

	sectionMapItor it = m_sectionMap.find( sectionName );
	if( it == m_sectionMap.end() ) return;
	
	keyMapItor itBegin , itEnd;
	itBegin = it->second.begin();
	itEnd = it->second.end();

	for(; itBegin != itEnd ; itBegin++ )
	{
		nameVec.push_back( itBegin->second );
	}
}

std::string IniFileManager::getValue( const std::string & sectionName , const std::string & keyName )
{
	sectionMapItor it = m_sectionMap.find( sectionName );
	if( it == m_sectionMap.end() ) return "";

	keyMapItor it2 = it->second.find( keyName );
	if( it2 == it->second.end() ) return "";

	return it2->second;
}

bool IniFileManager::setValue( const std::string & sectionName , const std::string & keyName , const std::string & value )
{
	return true;
}

bool IniFileManager::saveIniFile()
{
	
	return true;
}

bool IniFileManager::closeIniFile()
{

	return true;
}


bool IniFileManager::isSectionName( const std::string & str )
{
	if( str.length() < 3 ) return false;
	if( *str.begin() != '[' || *(--str.end()) != ']' ) return false;

	return true;
}

void IniFileManager::parseSectionName( const std::string & str , std::string & sectionName )
{
	sectionName.clear();
	sectionName.assign( ++str.begin() , -- str.end() );
}

bool IniFileManager::isKeyValue( const std::string & str )
{
	//第一个字符如果为=，或者字符串中没有=，都是不合法的
	if ( *str.begin() == '=' || str.find( '=' ) == -1 )
		return false;
	return true;
}

void IniFileManager::parseKeyValue( const std::string & str , std::string & keyName , std::string & value )
{
	keyName.clear();
	value.clear();

	std::vector<std::string> stringVec;
	StringTools::splitString( str , stringVec , '=' );

	keyName = stringVec[0];
	
	if( stringVec.size() > 1 ) 
		value = stringVec[1];

}