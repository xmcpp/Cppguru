// UnitTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "pch.h"
#include "vld.h"
#include "GlobalInit.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//���ȫ���¼���
	testing::AddGlobalTestEnvironment( new Globalinit() );

	//��ʼ�����в�������
	testing::InitGoogleTest( &argc , argv );

	return RUN_ALL_TESTS();
}

