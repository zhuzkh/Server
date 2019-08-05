#pragma once
#include "stdafx.h"
namespace NetWork
{
	enum
	{
		Mem_Mode_Init = 0,		//内存模式：初始化
		Mem_Mode_Resume = 1,	//内存模式：还原
	};
}

struct SMsgQueueHead 
{
	size_t m_iMemSize;
	size_t m_iQueueSize;
	volatile size_t m_iReadIndex;
	volatile size_t m_iWriteIndex;
};

class MessageCirularQueue
{
public:

	enum
	{
		Queue_Message_Head_Length	 = sizeof(size_t),					//用size_t大小的字节数来表示放入的内容长度
		Min_Message_Chunk_Size		 = Queue_Message_Head_Length + 1,	//最小的消息长度为头部+1
		Message_Queue_Reverse_Length = 2 * Queue_Message_Head_Length,		//用来防止read和write重叠
	};

	MessageCirularQueue();

private:
	SMsgQueueHead* m_pHead;
	char* m_pMsgBase;

	uint64_t stat_total_size;

public:
	size_t AllocSize(size_t iQueueSize)
	{
		return (sizeof(SMsgQueueHead)*2 + iQueueSize + Message_Queue_Reverse_Length);
	}

	bool Init(size_t iQueueSize, int32_t iMemMode = NetWork::Mem_Mode_Init);

	bool Append(const char* pmsg, size_t msg_length, uint32_t stat_msg_type = 0);
	bool Pop(char* pmsg, size_t& msg_length);

	size_t GetSize(void)
	{
		return m_pHead->m_iQueueSize - Message_Queue_Reverse_Length;
	}

	uint64_t get_total_size() { return stat_total_size; }

private:
	size_t _getFreeSize(void)
	{
		return (m_pHead->m_iReadIndex > m_pHead->m_iWriteIndex) ? (m_pHead->m_iReadIndex - m_pHead->m_iWriteIndex - Message_Queue_Reverse_Length) : (m_pHead->m_iQueueSize - m_pHead->m_iWriteIndex + m_pHead->m_iReadIndex - Message_Queue_Reverse_Length);
	}

	size_t _getUsedSize(void)
	{
		return (GetSize() - _getFreeSize());
	}

	size_t _getMsgLength(void)
	{
		size_t msg_length = 0;
		char* pdst = reinterpret_cast<char*>(&msg_length);
		size_t read = m_pHead->m_iReadIndex;
		char* psrc = m_pMsgBase + read;

		for (size_t i=0; i<Queue_Message_Head_Length; ++i)
		{
			*pdst = *psrc;
			++pdst;
			read = (read + 1) % m_pHead->m_iQueueSize;
			psrc = m_pMsgBase + read;
		}

		return msg_length;
	}

	bool _isFull(void)
	{
		return (0 == _getFreeSize());
	}

	bool _isEmpty(void)
	{
		return (GetSize() == _getFreeSize());
	}

	void _clear(void)
	{
		m_pHead->m_iReadIndex = 0;
		m_pHead->m_iWriteIndex= 0;
	}

	void _check_total_size(size_t msg_length)
	{
		stat_total_size += msg_length;

		if (stat_total_size > 4200000000)
		{
			stat_total_size = 0;
		}
	}
};

