#include "../../includes/Client.hpp"
#include "../../includes/Server.hpp"

/**
 * @brief Construct a new Server:: Server object
 */
Server::Server(int port, string password)
{
	this->_port = port;
	this->_password = password;
	this->max_clients_limit = 5;
	
	this->_server_sockIPV4.sin_family = AF_INET;
	this->_server_sockIPV4.sin_addr.s_addr = INADDR_ANY;
	this->_server_sockIPV4.sin_port = htons(_port);

	this->_server_sockIPV6.sin6_family = AF_INET6;
	this->_server_sockIPV6.sin6_addr = in6addr_any;
	this->_server_sockIPV6.sin6_port = htons(_port);

	cout << GREEN << "Server object created." << RESET << endl;
}

/**
 * @brief Destroy the Server:: Server object
 */
Server::~Server() 
{
	cout << RED << "Server object destroyed." << RESET << endl;
}

/**
 * @brief Overload of the = operator
 * 
 * @param rhs 
 * @return Server& 
 */
Server &Server::operator=(Server const &rhs)
{
	_port = rhs._port;
	_password = rhs._password;
	return (*this);
}

/**
 * @brief Copy constructor
 * 
 * @param copy 
 */
Server::Server(Server const &copy)
{
	_port = copy._port;
	_password = copy._password;
}

/**
 * @brief Get the Port object
 * 
 * @return int 
 */
int Server::getPort()
{
	return (_port);
}

/**
 * @brief Get the Password object
 * 
 * @return string 
 */
string Server::getPassword()
{
	return (_password);
}

/**
 * @brief Set the Port object
 * 
 * @param port 
 */
void Server::setPort(int port)
{
	_port = port;
	cout << GREEN << "Port set to " << port << "." << RESET << endl;
}

/**
 * @brief Set the Password object
 * 
 * @param password 
 */
void Server::setPassword(string password)
{
	_password = password;
	cout << GREEN << "Password set to " << password << "." << RESET << endl;
}

/**
 * @brief Start the server with the IPv4 internet protocol
 */
void Server::startServerIPV4()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd == -1)
	{
		handleErrorConnection();
		return ;
	}
	cout << GREEN << "socket() is OK!" << endl;


	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		handleErrorConnection();
		return;
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
		handleErrorConnection();
		return;
	}

	if (bind(fd, (struct sockaddr *)&_server_sockIPV4, sizeof(_server_sockIPV4)) != 0)
	{
		handleErrorConnection();
		return ;
	}

	cout << GREEN << "bind() is OK!" << endl;

	if (listen(fd, max_clients_limit) < 0)
	{
		handleErrorConnection();
		return ;
	}

	cout << GREEN << "listen() is OK, and waiting for connections..." << endl;

	while (true)
	{
		int client_fd = accept(fd, NULL, NULL);
		if (client_fd < 0)
		{
			if (errno == EWOULDBLOCK || errno == EAGAIN)
				continue;
			else
			{
				handleErrorConnection();
				continue ;
			}
		}
		cout << GREEN << "Client trying to connect." << RESET << endl;
		if (!addClient(client_fd))
		{
			/**
			 * TODO: This loop just work for accept fds inside the server, now need to make the clients to do something inside the server and keep testing, but need to know how to do that with that loop working
			 * 
			 */
			std::cerr << RED << "Reached the limit of clients inside the server." << RESET << endl;
			continue ;
		}
	}
	close (fd);
}

bool  Server::addClient(int fd)
{
	static int index = 0;
	if (_clients.size() >= max_clients_limit)
	{
		close(fd);
		return (false);
	}
	Client* new_client = new Client(fd);
	_clients[index++] = new_client;
	return (true);
}

/**
 * @brief Start the server with the IPv6 internet protocol
 */
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