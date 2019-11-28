#include "MessageProcessor.h"

MessageProcessor::MessageProcessor(MessageCirularQueue& send_queue, MessageCirularQueue& receive_queue) : 
	m_send_queue(send_queue),
	m_receive_queue(receive_queue)
{
	memset(m_recive_temp_buffer, 0, MSG_MAX_LEN);
	memset(m_send_temp_buffer, 0, MSG_MAX_LEN);
}

bool MessageProcessor::Initlize()
{
	m_message_handler_map[1] = std::bind(&MessageProcessor::OnCSMsgTest, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	return true;
}

void MessageProcessor::Update()
{
	ReceiveMsg();
}

void MessageProcessor::OnProcessMsg()
{
	MsgHeader header;
	memmove(&header, m_recive_temp_buffer, MSG_HEADER_LEN);
	if (m_message_handler_map.find(header.msg_id) != m_message_handler_map.end())
	{
		m_message_handler_map[header.msg_id](header.player_id, m_recive_temp_buffer + MSG_HEADER_LEN, header.length - MSG_HEADER_LEN);
	}
	else
	{
		LOG_ERROR("err msg id : ", header.msg_id);
	}
	// 	LOG_INFO("receive : {}", body);
}

void MessageProcessor::ReceiveMsg()
{
	bool ret;
	size_t nCodeLength;
	for (int i = 0; i < MAX_HANDLE_MSG_COUNT_ONCE; i++)
	{
		nCodeLength = (size_t)MSG_MAX_LEN;
		ret = m_receive_queue.Pop(m_recive_temp_buffer, nCodeLength);
		if (!ret)
			break;

		if (nCodeLength <= 0)
			break;

		OnProcessMsg();
	}
}

void MessageProcessor::SendMsg2Client(int32_t player_id, char* buf, int32_t length)
{
	MsgHeader header;
	header.length = length + MSG_HEADER_LEN;
	header.player_id = player_id;
	memmove(m_send_temp_buffer, &header, MSG_HEADER_LEN);
	memmove(m_send_temp_buffer + MSG_HEADER_LEN, buf, length);
	m_send_queue.Append(m_send_temp_buffer, header.length);
}

void MessageProcessor::OnCSMsgTest(int32_t player_id, char* buf, int32_t length)
{
	SendMsg2Client(player_id, buf, length);
}
