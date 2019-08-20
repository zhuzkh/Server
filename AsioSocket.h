#pragma once
#include "stdafx.h"
#include "boost/asio.hpp"
#include "NetProxy.h"
#include "Logger.h"
#include "MemoryPool.h"
using namespace boost::asio;
using namespace boost::asio::error;
using namespace boost;
class AsioSocket
{
public:
	AsioSocket(int id, ip::tcp::socket socket); 
	AsioSocket(io_context& service);
	~AsioSocket();
	void Release();
	void AsyncConnect(std::string ip_address, int port);
	void AsyncReadHeader();
	void AsyncReadBody(MsgBufferBase* buffer, size_t body_length);
	void AsyncWrite(std::string str);
	void AsyncWrite(char* buff, size_t size);
	void RegisterReadFunc(std::function<void(AsioSocket*, system::error_code, std::size_t, MsgBufferBase*)> read_func);
	void RegisterWriteFunc(std::function<void(AsioSocket*, system::error_code)> write_func);
	void RegisterConnectfunc(std::function<void(AsioSocket*, system::error_code)> connect_func);
	ip::tcp::socket& GetSocket();
	const ip::tcp::endpoint GetEndPoint();
	int GetId();
	bool Close();
private:
	void OnReaderHeader(system::error_code err, std::size_t bytes);
	void OnReadBody(system::error_code err, std::size_t bytes, MsgBufferBase* buffer);
	void OnWrite(system::error_code err, std::size_t bytes, MsgBufferBase* buffer);
	void OnConnect(system::error_code err);

	MsgBufferBase* GetMsgBuffer(size_t msg_len);
	eMSG_BUFFER_LENGTH::e GetMsgBufferLen(size_t msg_len);
private:
	ip::tcp::socket m_socket;
	int m_id;
	MsgHeader m_header_buffer;
	std::function<void(AsioSocket*, system::error_code, std::size_t, MsgBufferBase*)> m_read_function;
	std::function<void(AsioSocket*, system::error_code)> m_write_function;
	std::function<void(AsioSocket*, system::error_code)> m_connect_function;
};

#define GET_MSG_Buffer(len) MsgBuffer<len>* buffer = MemoryPool<MsgBuffer<len>>::GetInstance().GetObj();\
							if (!buffer)\
							{\
								return nullptr;\
							}\
							buffer->m_func = std::bind(&MemoryPool<MsgBuffer<len>>::Recycle, \
								&(MemoryPool<MsgBuffer<len>>::GetInstance()), std::placeholders::_1);\
							return buffer;
