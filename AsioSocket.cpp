#include "AsioSocket.h"
AsioSocket::AsioSocket(int id, ip::tcp::socket socket) : m_socket(std::move(socket)), m_id(id)
{

}

AsioSocket::~AsioSocket()
{

}

void AsioSocket::AsyncConnect(std::string ip_address, int port)
{
	m_socket.async_connect(ip::tcp::endpoint(ip::make_address(ip_address), port), std::bind(&AsioSocket::OnConnect, this, std::placeholders::_1));
}

void AsioSocket::AsyncReadHeader()
{
	MemoryObj<MsgData>* buffer = MemoryPool<MsgData>::GetInstance().GetObj();
	if (!buffer)
	{
		return;
	}
	async_read(m_socket, boost::asio::buffer(&buffer->GetData<0>().header, sizeof(MsgHeader)), transfer_all(), std::bind(&AsioSocket::OnReaderHeader, this, std::placeholders::_1, std::placeholders::_2, buffer));
	//m_socket.async_read_some(boost::asio::buffer(tmpBuff, MAX_MSG_LEN), std::bind(&AsioSocket::OnRead, this, std::placeholders::_1, std::placeholders::_2));
}

void AsioSocket::OnReaderHeader(system::error_code err, std::size_t bytes, MemoryObj<MsgData>* pBuffer)
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
				m_read_function(this, err, bytes, pBuffer);
			}
		}

		return;
	}
	AsyncReadBody(pBuffer);
}

void AsioSocket::AsyncReadBody(MemoryObj<MsgData>* buffer)
{
	async_read(m_socket, boost::asio::buffer(buffer->GetData<0>().body, 128), transfer_all(), std::bind(&AsioSocket::OnReadBody, this, std::placeholders::_1, std::placeholders::_2, buffer));
}

void AsioSocket::OnReadBody(system::error_code err, std::size_t bytes, MemoryObj<MsgData>* pBuffer)
{
	if (err)
	{
		if (err.value() == try_again || err.value() == would_block || err.value() == interrupted)
		{
			LOG_ERROR(err.message());
			AsyncReadBody(pBuffer);
		}
	}
	if (!m_read_function)
	{
		return;
	}
	m_read_function(this, err, bytes + sizeof(MsgHeader), pBuffer);
}

void AsioSocket::AsyncWrite(std::string str)
{
	//char* tmpBuff = (char*)NetProxy::GetInstance().GetSendBuff();
	char* tmp_buffer = new char[str.size()];
	memmove(tmp_buffer, str.c_str(), str.size());
	async_write(m_socket, boost::asio::buffer(tmp_buffer, MAX_MSG_LEN), transfer_all(), std::bind(&AsioSocket::OnWrite, this, std::placeholders::_1, std::placeholders::_2, tmp_buffer));
}

void AsioSocket::AsyncWrite(char* buff, size_t size)
{
	//char* tmpBuffer = (char*)NetProxy::GetInstance().GetSendBuff();
	char* tmp_buffer = new char[size];
	memmove(tmp_buffer, buff, size);
	async_write(m_socket, boost::asio::buffer(tmp_buffer, size), transfer_all(), std::bind(&AsioSocket::OnWrite, this, std::placeholders::_1, std::placeholders::_2, tmp_buffer));
	//m_socket.async_write_some(buffer(tmpBuff, MAX_MSG_LEN), std::bind(&AsioSocket::OnWrite, this, std::placeholders::_1, std::placeholders::_2));
}





void AsioSocket::OnWrite(system::error_code err, std::size_t bytes, char* buffer)
{
	if (err)
	{
	}
	delete[] buffer;
}

void AsioSocket::OnConnect(system::error_code err)
{
	if (m_connect_function)
	{
		m_connect_function(this, err);
	}
}

void AsioSocket::RegisterReadFunc(std::function<void(AsioSocket*, system::error_code, std::size_t, MemoryObj<MsgData>*)> read_func)
{
	m_read_function = read_func;
}

void AsioSocket::RegisterConnectfunc(std::function<void(AsioSocket*, system::error_code)> connect_func)
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
	m_socket.close(err);
	return true;
}