#ifndef _BASEDEFINE_HPP_
#define _BASEDEFINE_HPP_ 

#pragma once

#include "NativeTypes.h"

/*
typedef unsigned char		uint8_t;
typedef char				int8_t;
typedef unsigned short		uint16_t;
typedef short				int16_t;
typedef unsigned long		uint32_t;
typedef long				int32_t;
typedef unsigned long long	uint64_t;
typedef long long			int64_t;
*/

/*����������Ϣ��������е���Ϣ���͵�ö������
@remark 
	NETWORK		��ʾ����Ϣ�������ר�õ���Ϣ
	MANAGE		��ʾ����Ϣ�Ƿ�����������õ���Ϣ
	GAMELOGIC	��ʾ����Ϣ����Ϸ�߼��õ���Ϣ
*/
enum MSG_TYPE{ NETWORK = 0 , MANAGE = 1 , GAMELOGIC = 2 };

typedef struct tagMessageData
{
	uint8_t messageType; //MSG_TYPE
	uint16_t messageID;
	uint16_t senderIndex; //��¼������session id
	uint32_t size;
	uint8_t * data;
}MessageData;

typedef struct tagServerEnv
{
	std::string	localIp; 
	uint16_t localPort; 
	std::string	localPassword;
	uint16_t localMaxConnectionCount;
	uint32_t localNetworkThreadSleepTime;
	
}ServerEnv;


#endif //_BASEDEFINE_HPP_
