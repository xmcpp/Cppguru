#include "pch.h"
#include "CppSQLite3.h"
#include "localDataBase.h"
#include <io.h>

LocalDataBase* Singleton<LocalDataBase>::ms_Singleton=NULL;


LocalDataBase::LocalDataBase()
:m_pDB(NULL)
{
	m_pDB = new CppSQLite3DB();

}

LocalDataBase::~LocalDataBase()
{
	if(m_pDB!=NULL)
	{
		m_pDB->close();
		delete m_pDB;
	}

}

bool LocalDataBase::open(const  std::string& databasefilename,bool createDB)
{
	/**如果不存在指定的数据库文件就直接返回假*/
	if(::access(databasefilename.c_str(),0)==-1)
	{
		if(createDB==false)
		{
			return false;
		}
	}


	try
	{
		m_pDB->open(databasefilename.c_str());

	}
	catch (CppSQLite3Exception& e)
	{
		return false;
		
	}
	return true;

}


/**判断数据库是否打开*/
//bool LocalDataBase::isOpen()const
//{
//	if(m_pDB==NULL)
//		return false;
//	try
//	{
//	 m_pDB->checkDB();
//
//	}catch( CppSQLite3Exception & e)
//	{
//		return false;
//	}
//	return true;
//
//}



void LocalDataBase::close()
{
	m_pDB->close();

}

bool LocalDataBase::hasTable(const std::string& tableName)
{
	try
	{
		 m_pDB->tableExists(tableName.c_str());

	}catch(CppSQLite3Exception& e )
	{

		return false;      
	}
	return true;

}


bool LocalDataBase::getTable(const std::string& tabelName,CppSQLite3Table& table)
{

	try
	{
		///"select * from emp order by 1;"

		std::string	selectDes ="select * from "+tabelName+";";//+" order by 1;";
		table =m_pDB->getTable(selectDes.c_str());

	}catch(CppSQLite3Exception& e)
	{
		return false;
	}
	return  true;
}



bool LocalDataBase::createTable(const std::string& tableName,const std::string& tableDes)
{
	try
	{
		std::string crateDes = tableName+" ( "+tableDes+" );";
		m_pDB->execDML(crateDes.c_str());
	}
	catch (CppSQLite3Exception& e)
	{
		return false;
	}
	
	return true;

}


bool  LocalDataBase::Query(const std::string& sql,CppSQLite3Query& qury)
{

	try
	{
	 qury=m_pDB->execQuery(sql.c_str());

	}catch(CppSQLite3Exception& e)
	{
		return false;
	}

	return true;
}


int  LocalDataBase::exeSQL(const std::string& sql)
{
	try
	{
	    return 	m_pDB->execDML(sql.c_str());

	}catch(CppSQLite3Exception& e)
	{
   
		return -1;
	}
}




bool LocalDataBase::beginTransaction()
{
	
	try
	{
		m_pDB->execDML("begin transaction;");

	}catch(CppSQLite3Exception & e)
	{
		return false;
	}
	return true;

}



bool LocalDataBase::endTransaction()
{
   
   try
   {
	   	m_pDB->execDML("commit transaction;");

   }catch(CppSQLite3Exception& e)
   {
	   return false;
   }
   return  true;

}

