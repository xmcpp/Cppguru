#include "stdafx.h"
#include "RingBuffer.h"



RingBuffer::RingBuffer( uint32_t buffsize )
:m_data( NULL ) , m_head( NULL ) , m_tail( NULL ) , m_buffSize( 0 )
{
	m_data = new uint8_t[buffsize];
	m_buffSize = buffsize;
	reset();
}

RingBuffer::~RingBuffer()
{
	delete []m_data;
}

uint8_t * RingBuffer::pushBack( uint8_t * pData , uint32_t size )
{
	uint8_t * tmp = m_tail + size;
	
	//�ж��Ƿ�Խ��ͷ��������Ǳ�ʾû�пռ�
	if( m_tail < m_head && tmp > m_head )
		return NULL;

	//�ж��Ƿ�Խ��β��
	if( tmp > m_realTail )
	{
		if( m_data + size > m_head )
		{
			//��ʾǰ��Ҳû�пռ䣬���ؿ�
			return NULL;
		}
		else
		{
			//��ʾβ���޿ռ䣬ͷ���пռ䣬�����ǽ�β���ռ�����
			
			//�޸�realtailָ��������ڵ�tail����ʾ�����ռ��޷�ʹ��
			m_realTail = m_tail;
			//����β��ָ��
			m_tail = m_data + size;
			//��������
			memcpy( m_data , pData , size );

			//���������׵�ַ
			return m_data;
		}
	}

	//��ʾ����������������
	memcpy( m_tail , pData , size );
	//��¼�����׵�ַ
	tmp = m_tail;
	//�޸�β��ָ��
	m_tail = m_tail + size;
	
	//���������׵�ַ
	return tmp;
}

bool RingBuffer::popFront( uint32_t size )
{
	uint8_t * tmp = m_head + size;
	
	//���Ҫ���������ݳ��ȳ���β���򳬹�realtail���ʾ�����˴���
	if( tmp > m_tail || tmp > m_realTail )
		return false;
	
	//�޸�ͷ��ָ��
	m_head = tmp;

	//���ͷ��ָ�����m_realTailָ�룬����Ҫ���⴦��
	if( m_head == m_realTail )
	{
		if( m_realTail == ( m_data + m_buffSize ) )
		{
			//��ʾ��ǰ��ͷָ���Ѿ�ָ�����һ���ֽڣ�����Խ�ͷָ��������ǰ��
			m_head = m_data;
		}
		else
		{
			//��ʾ����ԭ���п��пռ�δʹ�ã������ڽ��ÿռ�ϲ�

			//��realtailָ���������ͷ��ָ�벻��
			m_realTail = m_data + m_buffSize;
		}
		
	}
	return true;
}

void RingBuffer::reset()
{
	m_head = m_tail = m_data;
	m_realTail = m_data + m_buffSize;

	memset( m_data , 0 , m_buffSize );
}