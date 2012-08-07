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
	
	//判断是否超越了头部，如果是表示没有空间
	if( m_tail < m_head && tmp > m_head )
		return NULL;

	//判断是否超越了尾部
	if( tmp > m_realTail )
	{
		if( m_data + size > m_head )
		{
			//表示前端也没有空间，返回空
			return NULL;
		}
		else
		{
			//表示尾部无空间，头部有空间，做法是将尾部空间作废
			
			//修改realtail指针等于现在的tail，表示后续空间无法使用
			m_realTail = m_tail;
			//设置尾部指针
			m_tail = m_data + size;
			//拷贝数据
			memcpy( m_data , pData , size );

			//返回数据首地址
			return m_data;
		}
	}

	//表示可以正常存入数据
	memcpy( m_tail , pData , size );
	//记录数据首地址
	tmp = m_tail;
	//修改尾部指针
	m_tail = m_tail + size;
	
	//返回数据首地址
	return tmp;
}

bool RingBuffer::popFront( uint32_t size )
{
	uint8_t * tmp = m_head + size;
	
	//如果要弹出的数据长度超过尾部或超过realtail则表示出现了错误
	if( tmp > m_tail || tmp > m_realTail )
		return false;
	
	//修改头部指针
	m_head = tmp;

	//如果头部指针等于m_realTail指针，则需要特殊处理
	if( m_head == m_realTail )
	{
		if( m_realTail == ( m_data + m_buffSize ) )
		{
			//表示当前的头指针已经指向最后一个字节，则可以将头指针移向最前面
			m_head = m_data;
		}
		else
		{
			//表示后续原先有空闲空间未使用，则现在将该空间合并

			//将realtail指针移至最后，头部指针不动
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