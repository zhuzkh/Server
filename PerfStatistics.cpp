#include "PerfStatistics.h"

PerfStatistics::PerfStatistics()
{
	m_net_receive_bytes = 0;
	m_net_send_bytes = 0;
	m_net_receive_count = 0;
	m_net_send_count = 0;
	m_total_net_receive_bytes = 0;
	m_total_net_send_bytes = 0;
	m_total_net_receive_count = 0;
	m_total_net_send_count = 0;
}

void PerfStatistics::AddNetSendBytes(int32_t bytes)
{
	++m_net_send_count;
	++m_total_net_send_count;
	m_net_send_bytes += bytes;
	m_total_net_send_bytes += bytes;
}

void PerfStatistics::AddNetReceiveBytes(int32_t bytes)
{
	++m_net_receive_count;
	++m_total_net_receive_count;
	m_net_receive_bytes += bytes;
	m_total_net_receive_bytes += bytes;
}

void PerfStatistics::Reset()
{
	m_net_receive_bytes = 0;
	m_net_send_bytes = 0;
	m_net_receive_count = 0;
	m_net_send_count = 0;
}

int32_t PerfStatistics::GetNetSendBytes()
{
	return m_net_send_bytes;
}

int32_t PerfStatistics::GetNetReceiveBytes()
{
	return m_net_receive_bytes;
}

int32_t PerfStatistics::GetNetSendCount()
{
	return m_net_send_count;
}

int32_t PerfStatistics::GetNetReceiveCount()
{
	return m_net_receive_count;
}
