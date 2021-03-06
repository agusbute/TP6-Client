#include "stdafx.h"
#include "Client.h"

client::client()
{
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

client::~client()
{
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}

bool client::startConnection(const char* host)
{
	bool ret = true;
	endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(host, PORT));
	boost::system::error_code error;
	boost::asio::connect(*socket_forClient, endpoint, error);

	if (error)
	{
		cout << "Error connecting to: " << host << " Error Message: " << error.message() << endl;
		if (error.value() == boost::asio::error::connection_refused)
		{
			cout << host << " is not listening." << endl;
			ret = false;
		}
		
	}
	socket_forClient->non_blocking(true);
	return ret;
}

char * client:: receive_message()
{
	boost::system::error_code error;
	char buf[1500];
	size_t len = 0;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);
		if (!error)
		{
			buf[len] = '\0';
		}
	} while (error.value() == WSAEWOULDBLOCK);
	if (!error)
	{
		return &buf[0];
	}
	else
	{
		cout << "Error while trying to connect to server " << error.message() << std::endl;
		return NULL;
	}

}


bool client::send_message(char * ip,char * path)
{
	bool ret = true;
	string line1 = "GET ";		
	string line2(path);					
	string line2a = " HTTP/1.1\r\n";
	string line3 = "Host: ";
	string line3a(ip);
	string CLRF = "\r\n";

	string str = line1 + line2 + line2a + line3 + line3a + CLRF + CLRF;		//armo el mensaje con todas las partes

	char * buf = new char[str.size() + 1];
	strcpy(buf, str.c_str());

	size_t len = 0;
	boost::system::error_code error;

	do
	{
		len += socket_forClient->write_some(boost::asio::buffer(buf, strlen(buf)), error);
	} while ((error.value() == WSAEWOULDBLOCK) && len < strlen(buf));				//lo mando y me fijo que sea todo entero
	if (error)
	{
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		ret = false;
	}
	return ret;
}