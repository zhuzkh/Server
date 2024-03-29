#include "AsioSocket.h"
#include "PerfStatistics.h"

std::vector<eMSG_BUFFER_LENGTH::e> MSG_LENGTH_VEC = {
	eMSG_BUFFER_LENGTH::BYTES_32,
	eMSG_BUFFER_LENGTH::BYTES_64,
	eMSG_BUFFER_LENGTH::BYTES_128,
	eMSG_BUFFER_LENGTH::BYTES_256,
	eMSG_BUFFER_LENGTH::BYTES_512,
	eMSG_BUFFER_LENGTH::BYTES_1024,
	eMSG_BUFFER_LENGTH::BYTES_2048,
	eMSG_BUFFER_LENGTH::BYTES_4096,
	eMSG_BUFFER_LENGTH::BYTES_MAX
};


AsioSocket::AsioSocket(int id, ip::tcp::socket socket) : m_socket(std::move(socket)), m_id(id)
{
	Clear();
	m_socket.set_option(ip::tcp::no_delay(true));
	m_socket.set_option(socket_base::reuse_address(true));
}

AsioSocket::AsioSocket(io_context& service) : m_socket(service), m_id(0)
{
	Clear();
}

AsioSocket::~AsioSocket()
{
	Clear();
}

void AsioSocket::Clear()
{
	m_read_function = nullptr;
	m_write_function = nullptr;
	m_connect_function = nullptr;
}

void AsioSocket::AsyncConnect(std::string ip_address, int port)
{
	m_socket.async_connect(ip::tcp::endpoint(ip::make_address(ip_address), port), std::bind(&AsioSocket::OnConnect, this, std::placeholders::_1));
}

void AsioSocket::AsyncReadHeader()
{
	MsgHeader* header_buffer = MemoryPool<MsgHeader>::GetInstance().GetObj();
	if (!header_buffer)
	{
		return;
	}
	memset(header_buffer, 0, MSG_HEADER_LEN);
	async_read(m_socket, boost::asio::buffer(header_buffer, MSG_HEADER_LEN), transfer_all(), std::bind(&AsioSocket::OnReaderHeader, this, std::placeholders::_1, std::placeholders::_2, header_buffer));
}

void AsioSocket::OnReaderHeader(system::error_code err, std::size_t bytes, MsgHeader* header_buffer)
{
	if (err)
	{
		if (err.value() == try_again || err.value() == would_block || err.value() == interrupted)
		{
			LOG_ERROR(err.message());
			AsyncReadHeader();
		}
		else
		{
			if (m_read_function)
			{
				m_read_function(shared_from_this(), err, bytes, nullptr);
			}
		}
	}
	else
	{
		header_buffer->player_id = m_id;
		if (header_buffer->length > MSG_BODY_LEN)
		{
			//todo, read err 是否需要关闭连接
			LOG_ERROR("read msg out of size; size[{}], msg id[{}]", header_buffer->length, 0);
			return;
		}
		int32_t body_length = header_buffer->length - MSG_HEADER_LEN;
		if (body_length < 0)
		{
			LOG_ERROR("read body msg out of size; size[{}], msg id[{}]", body_length, 0);
			return;
		}
		MsgBufferBase* buffer = GetMsgBuffer(header_buffer->length);
		if (!buffer)
		{
			LOG_ERROR("get msg buffer err; size[{}], msg id[{}]", header_buffer->length, 0);
			return;
		}
		memmove(buffer->p_data, header_buffer, MSG_HEADER_LEN);
		AsyncReadBody(buffer, body_length);
	}

	MemoryPool<MsgHeader>::GetInstance().Recycle(header_buffer);
}

void AsioSocket::AsyncReadBody(MsgBufferBase* buffer, size_t body_length)
{
	async_read(m_socket, boost::asio::buffer(buffer->p_data + MSG_HEADER_LEN, body_length), transfer_all(), std::bind(&AsioSocket::OnReadBody, shared_from_this(), std::placeholders::_1, std::placeholders::_2, buffer));
}

void AsioSocket::OnReadBody(system::error_code err, std::size_t bytes, MsgBufferBase* pBuffer)
{
	if (err)
	{
		if (err.value() == try_again || err.value() == would_block || err.value() == interrupted)
		{
			LOG_ERROR(err.message());
			AsyncReadBody(pBuffer, bytes);
		}
	}
	if (m_read_function)
	{
		m_read_function(shared_from_this(), err, bytes, pBuffer);
	}
	PerfStatistics::GetInstance().AddNetReceiveBytes(bytes + MSG_HEADER_LEN);
	pBuffer->Recycle();
}

void AsioSocket::AsyncWrite(std::string str)
{
	uint32_t str_size = str.size() + MSG_HEADER_LEN;
	MsgHeader header = { 0 };
	header.length = str_size;
	if (str_size > MSG_MAX_LEN)
	{
		LOG_ERROR("string out of size; size[{}], msg id[{}]", str_size, header.msg_id);
		return;
	}
	MsgBufferBase* buffer = GetMsgBuffer(str_size);
	if (!buffer)
	{
		return;
	}

	memmove(buffer->p_data, &header, MSG_HEADER_LEN);
	memmove(buffer->p_data + MSG_HEADER_LEN, str.c_str(), str.size());
	async_write(m_socket, boost::asio::buffer(buffer->p_data, header.length), transfer_all(), std::bind(&AsioSocket::OnWrite, shared_from_this(), std::placeholders::_1, std::placeholders::_2, buffer));
	PerfStatistics::GetInstance().AddNetSendBytes(str_size);
}

void AsioSocket::AsyncWrite(char* str, size_t size)
{
	uint32_t str_size = size + MSG_HEADER_LEN;	
	MsgHeader header = { 0 };
	header.length = str_size;
	header.msg_id = 1;
	if (str_size > MSG_MAX_LEN)
	{
		LOG_ERROR("write msg out of size; size[{}], msg id[{}]", str_size, header.msg_id);
		return;
	}
	MsgBufferBase* buffer = GetMsgBuffer(str_size);
	if (!buffer)
	{
		return;
	}
	memmove(buffer->p_data, &header, MSG_HEADER_LEN);
	memmove(buffer->p_data + MSG_HEADER_LEN, str, size);
	async_write(m_socket, boost::asio::buffer(buffer->p_data, header.length), transfer_all(), std::bind(&AsioSocket::OnWrite, shared_from_this(), std::placeholders::_1, std::placeholders::_2, buffer));
	PerfStatistics::GetInstance().AddNetSendBytes(str_size);
}

void AsioSocket::OnWrite(system::error_code err, std::size_t bytes, MsgBufferBase* buffer)
{
	if (err)
	{
		LOG_ERROR(err.message());
	}
	if (m_write_function)
	{
		m_write_function(shared_from_this(), err);
	}
	buffer->Recycle();
}

void AsioSocket::OnConnect(system::error_code err)
{
	if (m_connect_function)
	{
		m_connect_function(shared_from_this(), err);
	}
}

MsgBufferBase* AsioSocket::GetMsgBuffer(size_t msg_len)
{
	eMSG_BUFFER_LENGTH::e buffer_len = GetMsgBufferLen(msg_len);
	if ((size_t)buffer_len < msg_len)
	{
		LOG_ERROR("size err! buffer_size[{}], msg_size[{}]", (size_t)buffer_len, msg_len);
		return nullptr;
	}
	switch (buffer_len)
	{
	case eMSG_BUFFER_LENGTH::BYTES_32:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_32);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_64:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_64);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_128:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_128);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_256:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_256);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_512:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_512);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_1024:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_1024);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_2048:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_2048);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_4096:
	{	
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_4096);
	}
	break;
	case eMSG_BUFFER_LENGTH::BYTES_MAX:
	default:
	{
		GET_MSG_Buffer(eMSG_BUFFER_LENGTH::BYTES_MAX);
	}
	break;
	}

	return nullptr;
}

eMSG_BUFFER_LENGTH::e AsioSocket::GetMsgBufferLen(size_t msg_len)
{
	size_t vec_size = MSG_LENGTH_VEC.size();
	for (size_t i = 0; i != vec_size; ++i)
	{
		if (msg_len <= (size_t)MSG_LENGTH_VEC[i])
		{
			return MSG_LENGTH_VEC[i];
		}
	}
	return eMSG_BUFFER_LENGTH::BYTES_MAX;
}

void AsioSocket::RegisterReadFunc(std::function<void(std::shared_ptr<AsioSocket>, system::error_code, std::size_t, MsgBufferBase*)> read_func)
{
	m_read_function = read_func;
}

void AsioSocket::RegisterWriteFunc(std::function<void(std::shared_ptr<AsioSocket>, system::error_code)> write_func)
{
	m_write_function = write_func;
}

void AsioSocket::RegisterConnectfunc(std::function<void(std::shared_ptr<AsioSocket>, system::error_code)> connect_func)
{
	m_connect_function = connect_func;
}

ip::tcp::socket& AsioSocket::GetSocket()
{
	return m_socket;
}

const boost::asio::ip::tcp::endpoint AsioSocket::GetEndPoint()
{
	return m_socket.remote_endpoint();
}

int AsioSocket::GetId()
{
	return m_id;
}

bool AsioSocket::Close()
{
	system::error_code err;
	//m_socket.close(err);
	m_socket.shutdown(socket_base::shutdown_both, err);
	Clear();
	return true;
}