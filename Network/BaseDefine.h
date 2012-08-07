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

/*用于描述消息处理队列中的消息类型的枚举类型
@remark 
	NETWORK		表示该消息是网络层专用的消息
	MANAGE		表示该消息是服务器组管理用的消息
	GAMELOGIC	表示该消息是游戏逻辑用的消息
*/
enum MSG_TYPE{ NETWORK = 0 , MANAGE = 1 , GAMELOGIC = 2 };

typedef struct tagMessageData
{
	uint8_t messageType; //MSG_TYPE
	uint16_t messageID;
	uint16_t senderIndex; //记录发送者session id
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
