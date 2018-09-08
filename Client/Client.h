#pragma once

#include <iostream>
#include <cstdio>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

using namespace std;

#define PORT "80"
#define SERVER_IP "127.0.0.1"

class client
{
public:
	client();
	bool startConnection(const char* host);
	char * receive_message();
	bool send_message(char*,char *);
	~client();

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};