#include "pch.h"
#include "IniFileManager.h"
#include "StringTools.h"
#include <fstream>

bool IniFileManager::loadIniFile( const std::string & fileName )
{

	std::fstream fs;
	fs.open( fileName.c_str() , std::ios::in | std::ios::_Nocreate );
	if( !fs.is_open() ) return false;
	
	clearAllData();

	std::string data;
	std::string key,value;
	std::string sectionName;
	while( std::getline( fs , data ) )
	{
		if( data == "" ) continue;

		if( isSectionName( data ) )
		{
			parseSectionName( data , sectionName );
			if( !hasSectionName(sectionName) )
				createSection( sectionName );
			
		}
		else if( isKeyValue( data ) )
		{
			parseKeyValue( data , key , value );
			if( hasKeyName(sectionName,key))
				updateKey( sectionName , key , value );
			else
				insertKey( sectionName , key , value );
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
		nameVec.push_back( itBegin->first );
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

bool IniFileManager::saveIniFile( const std::string & fileName )
{
	std::fstream fs;
	fs.open( fileName.c_str() , std::ios::in | std::ios::trunc | std::ios::out);
	if( !fs.is_open() ) return false;
	
	for( sectionMapItor it = m_sectionMap.begin() ; it != m_sectionMap.end(); it++ )
	{
		fs<<'['<<it->first<<']'<<std::endl;
		for( keyMapItor it2 = it->second.begin(); it2 != it->second.end() ; it2++ )
		{
			fs<<it2->first<<'='<<it2->second<<std::endl;
		}
		fs<<std::endl;
	}

	fs.close();
	return true;
}

bool IniFileManager::hasSectionName( const std::string & sectionName )
{
	sectionMapItor it = m_sectionMap.find( sectionName );
	if ( it == m_sectionMap.end() ) return false;
	
	return true;
}

bool IniFileManager::hasKeyName( const std::string & sectionName , const std::string & keyName )
{
	sectionMapItor it = m_sectionMap.find( sectionName );
	if ( it == m_sectionMap.end() ) return false;

	keyMapItor it2 = it->second.find( keyName );
	if( it2 == it->second.end() ) return false;

	return true;
}

bool IniFileManager::createSection( const std::string & sectionName )
{
	if( hasSectionName( sectionName ) ) return false;
	
	std::map<std::string,std::string> keyValueMap;
	m_sectionMap.insert( std::make_pair(sectionName,keyValueMap) );
	return true;
}

bool IniFileManager::destroySection( const std::string & sectionName )
{
	sectionMapItor it = m_sectionMap.find( sectionName );
	if ( it == m_sectionMap.end() ) return false;
	
	m_sectionMap.erase( it );

	return true;
}

bool IniFileManager::insertKey( const std::string & sectionName , const std::string & keyName , const std::string & value )
{
	sectionMapItor it = m_sectionMap.find( sectionName );
	if ( it == m_sectionMap.end() ) return false;

	keyMapItor it2 = it->second.find( keyName );
	if( it2 != it->second.end() ) return false;
	
	it->second.insert( std::make_pair(keyName , value));
	
	return true;
}

bool IniFileManager::removeKey( const std::string & sectionName , const std::string & keyName )
{
	sectionMapItor it = m_sectionMap.find( sectionName );
	if ( it == m_sectionMap.end() ) return false;

	keyMapItor it2 = it->second.find( keyName );
	if( it2 == it->second.end() ) return false;

	it->second.erase( it2 );
	return true;
}

bool IniFileManager::updateKey( const std::string & sectionName , const std::string & keyName , const std::string & value )
{
	sectionMapItor it = m_sectionMap.find( sectionName );
	if ( it == m_sectionMap.end() ) return false;

	keyMapItor it2 = it->second.find( keyName );
	if( it2 == it->second.end() ) return false;

	it2->second = value;
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
	
	StringTools::trimBoth( stringVec[0] );
	keyName = stringVec[0];
	
	if( stringVec.size() > 1 )
	{
		StringTools::trimBoth( stringVec[1] );
		value = stringVec[1];
	}

}

void IniFileManager::clearAllData()
{
	m_sectionMap.clear();
}