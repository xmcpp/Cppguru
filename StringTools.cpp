#include "pch.h"
#include "StringTools.h"

void StringTools::splitString( const std::string & srcString , std::vector<std::string> & stringVec , const char splitChar )
{
	stringVec.clear();
	
	std::string::const_iterator itor ,itorEnd ;
		
	std::string word;
	for ( itor = srcString.begin(),itorEnd = srcString.end();itor != itorEnd ; itor++ )
	{
		
		if ( splitChar == *itor  )
		{
			if ( word.size() > 0 )
			{
				stringVec.push_back( word );
				word.clear();
			}
		}
		else
			word.push_back(*itor);
	}
	
	if ( word.size() > 0 )
	{
		stringVec.push_back( word );
	}
}

void StringTools::trimBoth( std::string & srcString )
{
	if( srcString.length() == 0 ) return;
	std::string::iterator itBegin , itEnd;

	itBegin = srcString.begin();
	itEnd = srcString.end();
	while( itBegin != itEnd )
	{
		if( *itBegin == ' ' )
			itBegin++;
		else
			break;
	}
	srcString.assign( itBegin , itEnd );
	
	itBegin = srcString.begin();
	itEnd = srcString.end();

	if( itEnd != srcString.begin() ) itEnd--;
	while( itEnd != itBegin )
	{
		if( *itEnd == ' ' )
			itEnd--;
		else
			break;
	}
	if( itEnd != srcString.end() ) itEnd++;
		
	srcString.assign( itBegin , itEnd );
}