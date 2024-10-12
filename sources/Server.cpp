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

void Server::startServerIPV4()
{
	int fd = socket(AF_INET, SOCK_NONBLOCK, 0);

	if (fd != -1)
	{
		cout << GREEN << "Server started with IPv4 internet protocol." << RESET << endl;
		return;
	}
	handleErrorConnection();
}

void Server::startServerIPV6()
{
	int fd = socket(AF_INET6, SOCK_NONBLOCK, 0);

	if (fd != -1)
	{
		cout << GREEN << "Server started with IPv6 internet protocol." << RESET << endl;
		return;
	}
	handleErrorConnection();
}

void Server::handleErrorConnection()
{
	int op;

	if (errno == EACCES)
		op = 1;
	else if (errno == EAFNOSUPPORT)
		op = 2;
	else if (errno == EINVAL)
		op = 3;
	else if (errno == EMFILE)
		op = 4;
	else if (errno == ENFILE)
		op = 5;
	else if (errno == ENOBUFS || errno == ENOMEM)
		op = 6;
	else if (errno == EPROTONOSUPPORT)
		op = 7;

	switch (op)
	{
	case 1:
		cout << RED << "Permission to create a socket of the specified type and/or protocol is denied." << RESET << endl;
		break;
	case 2:
		cout << RED << "The implementation does not support the specified address family." << RESET << endl;
		break;
	case 3:
		cout << RED << "Unknown protocol, or protocol family not available/or invalid flags in type." << RESET << endl;
		break;
	case 4:
		cout << RED << "The per-process limit on the number of open file descriptors has been reached." << RESET << endl;
		break;
	case 5:
		cout << RED << "The system-wide limit on the total number of open files has been reached." << RESET << endl;
		break;
	case 6:
		cout << RED << "Insufficient memory is available. The socket cannot be created until sufficient resources are freed." << RESET << endl;
		break;
	case 7:
		cout << RED << "The protocol type or the specified protocol is not supported within this domain." << RESET << endl;
		break;
	default:
		cout << RED << "Underlying protocol modules" << RESET << endl;
		break;
	}
}