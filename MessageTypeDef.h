#ifndef MessageTypeDef_h
#define MessageTypeDef_h


/**��Ϣ���ͱ�
USERMESSAGE_BEGINΪ���һ��ϵͳ��Ϣ,�û���Ϣ�ı��������ʼ
*/

//tolua_begin
enum MessageType 
{
	MD_TIME_FRAMETICK, //ÿ֡�������¼� ,������interval ���� float ˵����֡�������λ��
	MD_TIME_ONESECOND, //ÿ�뷢�����¼� ���޲���

	USERMESSAGE_BEGIN
};
//tolua_end

#endif //MessageTypeDef_h