#pragma once
#include "Stdafx.h"
#include "boost/asio.hpp"
#include "AsioSocket.h"
#include <iostream>
#include "NetProxy.h"
#include "Logger.h"
using namespace boost::asio;
using namespace boost::system;
class AsioAcceptor
{
public:
	AsioAcceptor(io_context& context);
	~AsioAcceptor();

	void AsyncAccept();
	bool Initilize(std::string ip_address, int port);
	void AcceptHandle(system::error_code ec, ip::tcp::socket socket);
	void RegisterAcceptFunc(std::function<void(system::error_code, ip::tcp::socket&)> func);
private:
	ip::tcp::acceptor m_acceptor;
	std::function<void(system::error_code, ip::tcp::socket&)> m_accept_func;
};
