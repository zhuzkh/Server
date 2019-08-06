#pragma once
#include "Stdafx.h"
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
	~AsioSocket();

	void AsyncConnect(std::string ip_address, int port);
	void AsyncReadHeader();
	void AsyncReadBody(MSG_DATA* buffer);
	void AsyncWrite(std::string str);
	void AsyncWrite(char* buff, size_t size);
	void RegisterReadFunc(std::function<void(AsioSocket*, system::error_code, std::size_t, MSG_DATA*)> read_func);
	void RegisterConnectfunc(std::function<void(AsioSocket*, system::error_code)> connect_func);
	ip::tcp::socket& GetSocket();
	const ip::tcp::endpoint GetEndPoint();
	int GetId();
	bool Close();
private:
	void OnReaderHeader(system::error_code err, std::size_t bytes, MSG_DATA* buffer);
	void OnReadBody(system::error_code err, std::size_t bytes, MSG_DATA* buffer);
	void OnWrite(system::error_code err, std::size_t bytes, char* buffer);
	void OnConnect(system::error_code err);

private:
	ip::tcp::socket m_socket;
	int m_id;
	std::function<void(AsioSocket*, system::error_code, std::size_t, MSG_DATA*)> m_read_function;
	std::function<void(AsioSocket*, system::error_code, std::size_t)> m_write_function;
	std::function<void(AsioSocket*, system::error_code)> m_connect_function;
};