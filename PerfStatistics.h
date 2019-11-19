#pragma once
#include "stdafx.h"
#include "Singleton.h"

class PerfStatistics : public Singleton<PerfStatistics> 
{
public:
	PerfStatistics();

	void AddNetSendBytes(int32_t bytes);
	void AddNetReceiveBytes(int32_t bytes);

	void Reset();

	int32_t GetNetSendBytes();
	int32_t GetNetReceiveBytes();
	int32_t GetNetSendCount();
	int32_t GetNetReceiveCount();
	
private:
	int32_t m_net_receive_bytes;
	int32_t m_net_send_bytes;
	int32_t m_net_receive_count;
	int32_t m_net_send_count;
	int32_t m_total_net_receive_bytes;
	int32_t m_total_net_send_bytes;
	int32_t m_total_net_receive_count;
	int32_t m_total_net_send_count;

};