/****************************
本地数据库简单封装cppsqlite3
******************************/
#ifndef __LOCALDATABASE_H__
#define __LOCALDATABASE_H__

#include "CppSQLite3.h"
#include "Singleton.h"

class LocalDataBase :public Singleton<LocalDataBase>
{
public:

	/**构造函数*/
	LocalDataBase();

	/**析构函数，会自动关闭数据库*/
	~LocalDataBase();

	/**打开数据库
	*@param databsefilename 数据库文件名
	*@param createDB 如果指定数据库不存在是否创建新的数据库文件
	*@return 成功返回真失败返回假
	*/
	bool open(const std::string& databasefilename,bool createDB=false);


	/**关闭数据库*/
	void close();

	/**判断数据库是否打开*/
	//bool isOpen()const;

	/**判断是否有指定的表*/
	bool hasTable(const std::string& tableName);


	/**获取一个表里的所有数据
	*@param tableName  
	*@param table返回表数据
	*@param 成功返回真。失败返回假
	*/
	bool getTable(const std::string& tabelName,CppSQLite3Table& table);


	/**创建一个表
	*@param tableName表名
	*@param tableDes 表字段描术
	*@return 成功返回真。失败返回假
	*@remark  tableDes 每个字段用逗号分开，字段描述格式 字段表+空格+类型+其它说明
	*例如 empno integer primary key, empname char(20)
	*/
	bool createTable(const std::string& tableName,const std::string& tableDes);

   /**执行一个查询动作
   *@param sql 查询语名
   *@param 返回query 查询结果
   *@return 成功返回真、失败返回假
   */
	bool Query(const std::string& sql,CppSQLite3Query& qury);

	/**执行sql 语名
	*@param sql sql语句
	*@return 更新的行数 -1表示没有执行成功
	*/
	int  exeSQL(const std::string& sql);
	
	/**
	*开始处理事务，为提高速度批量的数据操作需要写在beginTransaction和endTransaction之间
	*所有在begin end 之间的exeSQL会一次提次、做为一个原子操作
	*@remark beginTransaction必顺与endTransaction配对使用。
	*/
	bool beginTransaction();

	/**
	*结束事务
	*/
	bool endTransaction();
protected:
	/**cppsqlite db*/
	CppSQLite3DB* m_pDB;
};

#endif //__LOCALDATABASE_H__
