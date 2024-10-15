#include "../../includes/Client.hpp"
#include "../../includes/Server.hpp"


/**
 * @brief Construct a new Server:: Server object
 */
Server::Server() : _client(new Client())
{
	cout << GREEN << "Server object created." << RESET << endl;
}

/**
 * @brief Destroy the Server:: Server object
 */
Server::~Server() 
{
	delete _client;
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

	// Set the socket to non-blocking mode
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
	{
		handleErrorConnection();
		close(fd);
		return ;
	}

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		handleErrorConnection();
		close(fd);
		return ;
	}

	cout << GREEN << "Server started with IPv4 internet protocol." << RESET << endl;

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(_port);

	if (bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		handleErrorConnection();
		return;
	}

	if (listen(fd, 5) < 0)
	{
		handleErrorConnection();
		return ;
	}

	while (true)
	{
		int client_fd = accept(fd, NULL, NULL);
		_client->setFd(client_fd);
		if (_client->getFd() < 0)
		{
			if (errno == EWOULDBLOCK || errno == EAGAIN)
				continue;
			else
			{
				handleErrorConnection();
				continue ;
			}
		}
		cout << GREEN << "Client connected." << RESET << endl;
		_client->handleDataFromClient(_client->getFd());
	}
	close (fd);
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