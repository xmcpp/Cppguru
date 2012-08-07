#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include "BaseDefine.h"


/** 一个特殊的环形buff，用于消息数据的保存
@class RingBuffer

@remarks
	这个类主要用于存储服务器处理消息的数据。消息队列在收到每一个信息的时候将信息中的数据指针
	所值向的数据拷贝到本RingBuffer中，再将消息中的数据指针指向在Ringbuffer中的地址。
	
	另外采取连续地址的使用方式使得buff后面可能出现空间不够的情况，如果出现这种情况，ringbuffer中将会在末尾
	做出标示，表示后续空间没有使用，而数据将从缓冲区的头部开始存储。

	由于本模块是为消息处理定制的，所以假定了数据的存储是向地址高的方向存储，而数据的释放是从地址低的一端开始。另外释放
	数据块的大小由用户控制，需要小心处理。

@note
	由于在使用时消息中的数据地址直接使用了buffer中数据的实际地址，所以这个buff在开始时就要初始化足够的空间。因为
	如果在运行过程中对buffer的大小进行了调整会导致整个地址值的变化，最终导致所有消息中的数据指向无效的内存区域。
	如果想要做到内存的大小可以进行运行时调整，就必须改变引用的方式，由具体的地址值改为字节偏移。

@author 徐淼

@date 2009-09-22

*/

class RingBuffer
{
public:
	/** 缓冲区构造函数
	@param buffsize 用于表示构造缓冲的大小

	@remark
		本buffer无法在构造后修改大小，所以在构造时需要考虑好应用的情形
	*/
	RingBuffer( uint32_t buffsize );
	
	///析构函数
	~RingBuffer();

public:
	/** 向缓冲区内追加数据
	@param	pData 用于表示传入数据块的首地址

	@param size 用于表示传入数据块的大小

	@return 返回存入数据在缓冲区内的首地址，是堆上的地址，不是缓冲区相对地址
	
	@remark
		如果空间已满无法分配将会返回NULL地址，请小心处理
	*/
	uint8_t * pushBack( uint8_t * pData , uint32_t size );

	/** 从缓冲区前端清除数据
	@param size 用于表示清除数据块的大小

	@return 返回清除操作是否成功。如果返回false，则表示用户申请清除的数据大小越过了头指针的位置，那么可能
		已经出现了严重的数据错误。

	@remark
		该大小由用户控制，请严格按照传入的大小进行释放，防止扰乱所有的数据。
	*/
	bool popFront( uint32_t size );

	/** 重置缓冲区
	@remark
		该操作将清除当前缓冲区内的所有数据，并将各个控制指针复位，构造函数中会默认调用一次重置操作。
	*/
	void reset();
private:
	///记录尾指针
	uint8_t * m_tail; 

	///记录头指针
	uint8_t * m_head; 
	
	///记录当前buff中使用的数据的真实结尾，用于处理后续空间不足存储下一个数据的时候，用这个标记标示后续的空间没有使用
	uint8_t * m_realTail; 
	
	///记录当前数据块的首地址
	uint8_t * m_data;

	///记录当前buff的大小单位为字节
	uint32_t m_buffSize; 
};

#endif //_RINGBUFFER_H_
