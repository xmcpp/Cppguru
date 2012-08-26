#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include "BaseDefine.h"


/** һ������Ļ���buff��������Ϣ���ݵı���
@class RingBuffer

@remarks
	�������Ҫ���ڴ洢������������Ϣ�����ݡ���Ϣ�������յ�ÿһ����Ϣ��ʱ����Ϣ�е�����ָ��
	��ֵ������ݿ�������RingBuffer�У��ٽ���Ϣ�е�����ָ��ָ����Ringbuffer�еĵ�ַ��
	
	�����ȡ������ַ��ʹ�÷�ʽʹ��buff������ܳ��ֿռ䲻�������������������������ringbuffer�н�����ĩβ
	������ʾ����ʾ�����ռ�û��ʹ�ã������ݽ��ӻ�������ͷ����ʼ�洢��

	���ڱ�ģ����Ϊ��Ϣ�������Ƶģ����Լٶ������ݵĴ洢�����ַ�ߵķ���洢�������ݵ��ͷ��Ǵӵ�ַ�͵�һ�˿�ʼ�������ͷ�
	���ݿ�Ĵ�С���û����ƣ���ҪС�Ĵ�����

@note
	������ʹ��ʱ��Ϣ�е����ݵ�ֱַ��ʹ����buffer�����ݵ�ʵ�ʵ�ַ���������buff�ڿ�ʼʱ��Ҫ��ʼ���㹻�Ŀռ䡣��Ϊ
	��������й����ж�buffer�Ĵ�С�����˵����ᵼ��������ֵַ�ı仯�����յ���������Ϣ�е�����ָ����Ч���ڴ�����
	�����Ҫ�����ڴ�Ĵ�С���Խ�������ʱ�������ͱ���ı����õķ�ʽ���ɾ���ĵ�ֵַ��Ϊ�ֽ�ƫ�ơ�

@author ����

@date 2009-09-22

*/

class RingBuffer
{
public:
	/** ���������캯��
	@param buffsize ���ڱ�ʾ���컺��Ĵ�С

	@remark
		��buffer�޷��ڹ�����޸Ĵ�С�������ڹ���ʱ��Ҫ���Ǻ�Ӧ�õ�����
	*/
	RingBuffer( uint32_t buffsize );
	
	///��������
	~RingBuffer();

public:
	/** �򻺳�����׷������
	@param	pData ���ڱ�ʾ�������ݿ���׵�ַ

	@param size ���ڱ�ʾ�������ݿ�Ĵ�С

	@return ���ش��������ڻ������ڵ��׵�ַ���Ƕ��ϵĵ�ַ�����ǻ�������Ե�ַ
	
	@remark
		����ռ������޷����佫�᷵��NULL��ַ����С�Ĵ���
	*/
	uint8_t * pushBack( uint8_t * pData , uint32_t size );

	/** �ӻ�����ǰ���������
	@param size ���ڱ�ʾ������ݿ�Ĵ�С

	@return ������������Ƿ�ɹ����������false�����ʾ�û�������������ݴ�СԽ����ͷָ���λ�ã���ô����
		�Ѿ����������ص����ݴ���

	@remark
		�ô�С���û����ƣ����ϸ��մ���Ĵ�С�����ͷţ���ֹ�������е����ݡ�
	*/
	bool popFront( uint32_t size );

	/** ���û�����
	@remark
		�ò����������ǰ�������ڵ��������ݣ�������������ָ�븴λ�����캯���л�Ĭ�ϵ���һ�����ò�����
	*/
	void reset();
private:
	///��¼βָ��
	uint8_t * m_tail; 

	///��¼ͷָ��
	uint8_t * m_head; 
	
	///��¼��ǰbuff��ʹ�õ����ݵ���ʵ��β�����ڴ��������ռ䲻��洢��һ�����ݵ�ʱ���������Ǳ�ʾ�����Ŀռ�û��ʹ��
	uint8_t * m_realTail; 
	
	///��¼��ǰ���ݿ���׵�ַ
	uint8_t * m_data;

	///��¼��ǰbuff�Ĵ�С��λΪ�ֽ�
	uint32_t m_buffSize; 
};

#endif //_RINGBUFFER_H_