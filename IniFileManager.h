/**********************************************************************
ini文件读取和保存对象

用于读取ini文件的section和key-value，同时提供保存功能

@Author: 徐淼

@Date: 2012.1.4

Update: 
***********************************************************************/
#ifndef __INIFILEMANAGER_H__
#define __INIFILEMANAGER_H__

class IniFileManager
{
public:
	/** 从Ini文件中读取数据
	 * 
	 * @param fileName 文件路径和名称
	 * @return 打开读取成功为true，失败为false
	 * @note 
	 *		此函数只打开文件，并读取信息，在函数返回前就关闭文件了，将数据保存在内存中
	 */
	bool loadIniFile( const std::string & fileName );

	/** 获取当前ini文件中的所有Section名称列表
	 */
	void getSectionName( std::vector<std::string> & nameVec );
	
	/** 获取当前ini文件中指定Section下所有的key的名称
	 */
	void getKeyName( const std::string & sectionName , std::vector<std::string> & nameVec );
	
	/** 根据Section明澈功能和Key名称获得value
	 * @return 如果该值存在，则返回该字符串，如果给定的Section 和 Key不存在，则返回空字符串
	*/
	std::string getValue( const std::string & sectionName , const std::string & keyName );

	/** 将当前内存中的ini信息保存到指定的ini文件中
	 * @param fileName 文件路径和名称
	 * @note
	 *      此函数将当前内存中所有的信息保存到指定文件中，如果文件不存在则创建，如果存在则覆盖
	 */
	bool saveIniFile( const std::string & fileName );
	
	/** 判断是否存在指定名称的Section名称
	 */
	bool hasSectionName( const std::string & sectionName );
	
	/** 判断是否存在指定名称的Key名称
	 */
	bool hasKeyName( const std::string & sectionName , const std::string & keyName );
	
	/** 在文件中创建Section
	 * @return 成功返回true
	 * @note 如果该Section已经存在，则返回false
	 */
	bool createSection( const std::string & sectionName );

	/** 在文件中删除一个Section
	 * @return 成功返回true
	 * @note 如果该Section不存在存在，则返回false
	 */
	bool destroySection( const std::string & sectionName );

	/** 在文件中指定的Section下插入一个Key
	 * @return 成功返回true
	 * @note 如果该Section不存在 或者 key已经存在，则返回false
	 */
	bool insertKey( const std::string & sectionName , const std::string & keyName , const std::string & value );

	/** 在文件中指定的Section下删除一个Key
	 * @return 成功返回true
	 * @note 如果该Section不存在 或者 key不存在，则返回false
	 */
	bool removeKey( const std::string & sectionName , const std::string & keyName );

	/** 在文件中更新指定的Section下，指定key的value
	 * @return 成功返回true
	 * @note 如果该Section不存在 或者 key不存在，则返回false
	 */
	bool updateKey( const std::string & sectionName , const std::string & keyName , const std::string & value );
	
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
};

#endif //__INIFILEMANAGER_H__
