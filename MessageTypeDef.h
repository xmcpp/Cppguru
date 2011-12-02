#ifndef MessageTypeDef_h
#define MessageTypeDef_h


/**消息类型表
USERMESSAGE_BEGIN为最后一个系统消息,用户消息的编号由它开始
*/

//tolua_begin
enum MessageType 
{
	MD_TIME_FRAMETICK, //每帧发出的事件 ,参数：interval 类型 float 说明：帧间隔，单位秒
	MD_TIME_ONESECOND, //每秒发出的事件 ，无参数

	USERMESSAGE_BEGIN
};
//tolua_end

#endif //MessageTypeDef_h