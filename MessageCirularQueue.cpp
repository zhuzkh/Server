#include "MessageCirularQueue.h"
#include <cstring>
using namespace NetWork;
MessageCirularQueue::MessageCirularQueue()
{
	m_pHead = NULL;
	m_pMsgBase = NULL;

	stat_total_size = 0;
}
bool MessageCirularQueue::Init(size_t iQueueSize, int32_t iMemMode)
{
	size_t iRealMemSize = AllocSize (iQueueSize);
	size_t iRealQueueSize = iQueueSize + Message_Queue_Reverse_Length;
	char* pMem = new char[iRealMemSize];
	memset(pMem, 0, iRealMemSize);
	SMsgQueueHead* pHead = reinterpret_cast<SMsgQueueHead*>(pMem);
	if (!pHead)
	{
		return false;
	}
	if (Mem_Mode_Resume == iMemMode)
	{
		if (pHead->m_iMemSize   != iRealMemSize ||
			pHead->m_iQueueSize != iRealQueueSize)
		{
			return false;
		}
	}
	else
	{
		pHead->m_iMemSize   = iRealMemSize;
		pHead->m_iQueueSize = iRealQueueSize;
	}

	if (pHead->m_iMemSize != iRealMemSize)
	{
		return false;
	}

	m_pHead		= pHead;
	m_pMsgBase	= pMem + sizeof(SMsgQueueHead);

	if(Mem_Mode_Init == iMemMode)
	{
		this->_clear ();
	}

	stat_total_size = 0;

	return true;
}

bool MessageCirularQueue::Append(const char* pMsg, size_t iMsgLength, uint32_t stat_msg_type)
{
	size_t free_size = _getFreeSize ();
	//不足以放下一个包
	if (free_size < (iMsgLength + Queue_Message_Head_Length))
	{
		//DUMP_LOG(log_mask_error, "CMessageCirularQueue::Append error|free_size:%u\n", free_size);

		return false;
	}

	size_t iWrite = m_pHead->m_iWriteIndex;
	char* pDst = m_pMsgBase + iWrite;
	char* pSrc = reinterpret_cast<char*>(&iMsgLength);
	for (size_t i=0; i<Queue_Message_Head_Length; ++i)
	{
		*pDst = *pSrc;
		++pSrc;
		iWrite = (iWrite + 1) % m_pHead->m_iQueueSize;
		pDst = m_pMsgBase + iWrite;
	}

	m_pHead->m_iWriteIndex = (m_pHead->m_iWriteIndex + Queue_Message_Head_Length) % m_pHead->m_iQueueSize;

	// 如果绕圈
	if ((iWrite + iMsgLength) > m_pHead->m_iQueueSize)
	{
		size_t iFirstIndex = m_pHead->m_iQueueSize - m_pHead->m_iWriteIndex;
		size_t iSecond= iMsgLength - iFirstIndex;

		memmove(pDst, pMsg, iFirstIndex);
		memmove(m_pMsgBase, (pMsg + iFirstIndex), iSecond);
		m_pHead->m_iWriteIndex = iSecond;
	}
	else
	{
		memmove(pDst, pMsg, iMsgLength);
		m_pHead->m_iWriteIndex += iMsgLength;
	}

	_check_total_size(iMsgLength);

	//if (stat_msg_type != 0)
	//{
	//	GfxWriteSafeLog(LOG_INFO_FILELINE, "CMessageCirularQueue::Append success",
	//		"|msg_type:", stat_msg_type,
	//		"|msg_size:", iMsgLength);
	//}

	return true;
}

bool MessageCirularQueue::Pop(char* pMsg, size_t& iMsgLength)
{
	size_t iUsedSize = _getUsedSize();
	// 都不足以组成一个包
	if (Min_Message_Chunk_Size > iUsedSize)
	{
		return false;
	}

	size_t iBodySize = _getMsgLength();
	if ((Queue_Message_Head_Length + iBodySize) > iUsedSize)
	{
		return false;
	}

	// 传入的buff不足以放下一个包
	if (iBodySize > iMsgLength)
	{
		return false;
	}

	iMsgLength = iBodySize;
	size_t iReadIndex = m_pHead->m_iReadIndex;

	// 先把read移动到真实数据区
	for (size_t i=0; i<Queue_Message_Head_Length; ++i)
	{
		iReadIndex = (iReadIndex + 1) % m_pHead->m_iQueueSize;
	}

	m_pHead->m_iReadIndex = (m_pHead->m_iReadIndex + Queue_Message_Head_Length) % m_pHead->m_iQueueSize;

	// 如果绕圈
	if ((iReadIndex + iMsgLength) > m_pHead->m_iQueueSize)
	{
		size_t iFirstIndex = m_pHead->m_iQueueSize - iReadIndex;
		size_t iSecondIndex= iMsgLength - iFirstIndex;

		memmove(pMsg, (m_pMsgBase + iReadIndex), iFirstIndex);
		memmove((pMsg + iFirstIndex), m_pMsgBase, iSecondIndex);
		m_pHead->m_iReadIndex = iSecondIndex;
	}
	else
	{
		memmove(pMsg, (m_pMsgBase + iReadIndex), iMsgLength);
		m_pHead->m_iReadIndex += iMsgLength;
	}

	return true;
}




