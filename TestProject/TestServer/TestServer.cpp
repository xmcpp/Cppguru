// TestServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServerExample.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TestServer server;
	server.init();
	server.go();
	return 0;
}

