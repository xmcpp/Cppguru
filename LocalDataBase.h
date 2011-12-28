/****************************
�������ݿ�򵥷�װcppsqlite3
******************************/
#ifndef __LOCALDATABASE_H__
#define __LOCALDATABASE_H__

#include "CppSQLite3.h"
#include "Singleton.h"

class LocalDataBase :public Singleton<LocalDataBase>
{
public:

	/**���캯��*/
	LocalDataBase();

	/**�������������Զ��ر����ݿ�*/
	~LocalDataBase();

	/**�����ݿ�
	*@param databsefilename ���ݿ��ļ���
	*@param createDB ���ָ�����ݿⲻ�����Ƿ񴴽��µ����ݿ��ļ�
	*@return �ɹ�������ʧ�ܷ��ؼ�
	*/
	bool open(const std::string& databasefilename,bool createDB=false);


	/**�ر����ݿ�*/
	void close();

	/**�ж����ݿ��Ƿ��*/
	//bool isOpen()const;

	/**�ж��Ƿ���ָ���ı�*/
	bool hasTable(const std::string& tableName);


	/**��ȡһ���������������
	*@param tableName  
	*@param table���ر�����
	*@param �ɹ������档ʧ�ܷ��ؼ�
	*/
	bool getTable(const std::string& tabelName,CppSQLite3Table& table);


	/**����һ����
	*@param tableName����
	*@param tableDes ���ֶ�����
	*@return �ɹ������档ʧ�ܷ��ؼ�
	*@remark  tableDes ÿ���ֶ��ö��ŷֿ����ֶ�������ʽ �ֶα�+�ո�+����+����˵��
	*���� empno integer primary key, empname char(20)
	*/
	bool createTable(const std::string& tableName,const std::string& tableDes);

   /**ִ��һ����ѯ����
   *@param sql ��ѯ����
   *@param ����query ��ѯ���
   *@return �ɹ������桢ʧ�ܷ��ؼ�
   */
	bool Query(const std::string& sql,CppSQLite3Query& qury);

	/**ִ��sql ����
	*@param sql sql���
	*@return ���µ����� -1��ʾû��ִ�гɹ�
	*/
	int  exeSQL(const std::string& sql);
	
	/**
	*��ʼ��������Ϊ����ٶ����������ݲ�����Ҫд��beginTransaction��endTransaction֮��
	*������begin end ֮���exeSQL��һ����Ρ���Ϊһ��ԭ�Ӳ���
	*@remark beginTransaction��˳��endTransaction���ʹ�á�
	*/
	bool beginTransaction();

	/**
	*��������
	*/
	bool endTransaction();
protected:
	/**cppsqlite db*/
	CppSQLite3DB* m_pDB;
};

#endif //__LOCALDATABASE_H__
