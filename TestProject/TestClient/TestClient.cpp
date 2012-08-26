// TestClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ClientExample.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TestClient client;
	client.init();
	client.go();
	return 0;
}

