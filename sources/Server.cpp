#include "../includes/Server.hpp"

Server::Server()
{
	cout << "Server port and password setted." << endl;
}

Server::~Server() {}

Server &Server::operator=(Server const &rhs)
{
	_port = rhs._port;
	_password = rhs._password;
	return (*this);
}

Server::Server(Server const &copy)
{
	_port = copy._port;
	_password = copy._password;
}

int Server::getPort()
{
	return (_port);
}

string Server::getPassword()
{
	return (_password);
}

void Server::setPort(int port)
{
	_port = port;
}

void Server::setPassword(string password)
{
	_password = password;
}