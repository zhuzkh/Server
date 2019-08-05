#include "AsioAcceptor.h"

AsioAcceptor::AsioAcceptor(io_context& context) : m_acceptor(context)
{
}

AsioAcceptor::~AsioAcceptor()
{
}

void AsioAcceptor::AsyncAccept()
{
	m_acceptor.async_accept(std::bind(&AsioAcceptor::AcceptHandle, this, std::placeholders::_1, std::placeholders::_2));
}

bool AsioAcceptor::Initilize(std::string ip_address, int port)
{
	ip::tcp::endpoint endpoint(ip::make_address(ip_address), port);
	error_code ec;
	m_acceptor.open(endpoint.protocol(), ec);
	if (ec.value() != 0)
	{
		return false;
	}
	//m_acceptor.set_option(socket_base::reuse_address(true), ec);
	//if (ec.value() != 0)
	//{
	//	return false;
	//}
	m_acceptor.bind(endpoint, ec);
	if (ec.value() != 0)
	{
		LOG_ERROR(ec.message());
		return false;
	}
	m_acceptor.listen(socket_base::max_listen_connections, ec);
	if (ec.value() != 0)
	{
		LOG_ERROR(ec.message());
		return false;
	}
	return true;
}
void AsioAcceptor::AcceptHandle(error_code ec, ip::tcp::socket socket)
{
	if (!m_accept_func)
	{
		return;
	}
	m_accept_func(ec, socket);

	AsyncAccept();
}
void AsioAcceptor::RegisterAcceptFunc(std::function<void(error_code, ip::tcp::socket&)> func)
{
	m_accept_func = func;
}
