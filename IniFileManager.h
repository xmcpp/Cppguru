/**********************************************************************
ini�ļ���ȡ�ͱ������

���ڶ�ȡini�ļ���section��key-value��ͬʱ�ṩ���湦��

@Author: ���

@Date: 2012.1.4

Update: 
***********************************************************************/
#ifndef __INIFILEMANAGER_H__
#define __INIFILEMANAGER_H__

class IniFileManager
{
public:
	/** ��Ini�ļ��ж�ȡ����
	 * 
	 * @param fileName �ļ�·��������
	 * @return �򿪶�ȡ�ɹ�Ϊtrue��ʧ��Ϊfalse
	 * @note 
	 *		�˺���ֻ���ļ�������ȡ��Ϣ���ں�������ǰ�͹ر��ļ��ˣ������ݱ������ڴ���
	 */
	bool loadIniFile( const std::string & fileName );

	/** ��ȡ��ǰini�ļ��е�����Section�����б�
	 */
	void getSectionName( std::vector<std::string> & nameVec );
	
	/** ��ȡ��ǰini�ļ���ָ��Section�����е�key������
	 */
	void getKeyName( const std::string & sectionName , std::vector<std::string> & nameVec );
	
	/** ����Section�������ܺ�Key���ƻ��value
	 * @return �����ֵ���ڣ��򷵻ظ��ַ��������������Section �� Key�����ڣ��򷵻ؿ��ַ���
	*/
	std::string getValue( const std::string & sectionName , const std::string & keyName );

	/** ����ǰ�ڴ��е�ini��Ϣ���浽ָ����ini�ļ���
	 * @param fileName �ļ�·��������
	 * @note
	 *      �˺�������ǰ�ڴ������е���Ϣ���浽ָ���ļ��У�����ļ��������򴴽�����������򸲸�
	 */
	bool saveIniFile( const std::string & fileName );
	
	/** �ж��Ƿ����ָ�����Ƶ�Section����
	 */
	bool hasSectionName( const std::string & sectionName );
	
	/** �ж��Ƿ����ָ�����Ƶ�Key����
	 */
	bool hasKeyName( const std::string & sectionName , const std::string & keyName );
	
	/** ���ļ��д���Section
	 * @return �ɹ�����true
	 * @note �����Section�Ѿ����ڣ��򷵻�false
	 */
	bool createSection( const std::string & sectionName );

	/** ���ļ���ɾ��һ��Section
	 * @return �ɹ�����true
	 * @note �����Section�����ڴ��ڣ��򷵻�false
	 */
	bool destroySection( const std::string & sectionName );

	/** ���ļ���ָ����Section�²���һ��Key
	 * @return �ɹ�����true
	 * @note �����Section������ ���� key�Ѿ����ڣ��򷵻�false
	 */
	bool insertKey( const std::string & sectionName , const std::string & keyName , const std::string & value );

	/** ���ļ���ָ����Section��ɾ��һ��Key
	 * @return �ɹ�����true
	 * @note �����Section������ ���� key�����ڣ��򷵻�false
	 */
	bool removeKey( const std::string & sectionName , const std::string & keyName );

	/** ���ļ��и���ָ����Section�£�ָ��key��value
	 * @return �ɹ�����true
	 * @note �����Section������ ���� key�����ڣ��򷵻�false
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
