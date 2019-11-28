#pragma once
#include "stdafx.h"
#include "boost/asio.hpp"
#include "Logger.h"
#include "MemoryPool.h"
#include <memory>
#include "MsgDefing.h"
using namespace boost::asio;
using namespace boost::asio::error;
using namespace boost;
class AsioSocket : public std::enable_shared_from_this<AsioSocket>
{
public:
	AsioSocket(int id, ip::tcp::socket socket); 
	AsioSocket(io_context& service);
	~AsioSocket();
	void Clear();
	void AsyncConnect(std::string ip_address, int port);
	void AsyncReadHeader();
	void AsyncReadBody(MsgBufferBase* buffer, size_t body_length);
	void AsyncWrite(std::string str);
	void AsyncWrite(char* buff, size_t size);
	void RegisterReadFunc(std::function<void(std::shared_ptr<AsioSocket>, system::error_code, std::size_t, MsgBufferBase*)> read_func);
	void RegisterWriteFunc(std::function<void(std::shared_ptr<AsioSocket>, system::error_code)> write_func);
	void RegisterConnectfunc(std::function<void(std::shared_ptr<AsioSocket>, system::error_code)> connect_func);
	ip::tcp::socket& GetSocket();
	const ip::tcp::endpoint GetEndPoint();
	int GetId();
	bool Close();
#define REGISTER_READ_FUNC(func, instance) RegisterReadFunc(std::bind(func, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
#define REGISTER_WRITE_FUNC(func, instance) RegisterWriteFunc(std::bind(func, instance, std::placeholders::_1, std::placeholders::_2));
#define REGISTER_CONNECT_FUNC(func, instance) RegisterConnectfunc(std::bind(func, instance, std::placeholders::_1, std::placeholders::_2));
private:
	void OnReaderHeader(system::error_code err, std::size_t bytes, MsgHeader* header_buffer);
	void OnReadBody(system::error_code err, std::size_t bytes, MsgBufferBase* buffer);
	void OnWrite(system::error_code err, std::size_t bytes, MsgBufferBase* buffer);
	void OnConnect(system::error_code err);
	MsgBufferBase* GetMsgBuffer(size_t msg_len);
	eMSG_BUFFER_LENGTH::e GetMsgBufferLen(size_t msg_len);
private:
	ip::tcp::socket m_socket;
	int m_id;
	std::function<void(std::shared_ptr<AsioSocket>, system::error_code, std::size_t, MsgBufferBase*)> m_read_function;
	std::function<void(std::shared_ptr<AsioSocket>, system::error_code)> m_write_function;
	std::function<void(std::shared_ptr<AsioSocket>, system::error_code)> m_connect_function;
};

#define GET_MSG_Buffer(len) MsgBuffer<len>* buffer = MemoryPool<MsgBuffer<len>>::GetInstance().GetObj();\
							if (!buffer)\
							{\
								return nullptr;\
							}\
							buffer->m_func = std::bind(&MemoryPool<MsgBuffer<len>>::Recycle, \
								&(MemoryPool<MsgBuffer<len>>::GetInstance()), std::placeholders::_1);\
							return buffer;
