#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

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
		handleClient(_client->getFd());
	}
	close (fd);
}

void Server::handleClient(int client_fd)
{
	char buffer[1024];
	while (true)
	{
		ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
		_client->setInfo(buffer);
		
		/**
		 * TODO: Parse the first buffer iteration.
		 * TODO: e.g. Received: CAP LS 302
		 * TODO: PASS Davi282108
		 * TODO: NICK quisk
		 * TODO: USER dmeireles 0 * :Davi
		 */
		
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			cout << ORANGE << "Received: " << buffer << RESET << endl;
		}
		else if (bytes_read == 0)
		{
			cout << "Client disconnected." << endl;
			break ;
		}
		else
		{
			if (errno == EWOULDBLOCK || errno == EAGAIN)
				continue;
			else
			{
				handleErrorConnection();
				break;
			}
		}
	}
	close(client_fd);
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

/**
 * @brief Handle the error connection
 */
void Server::handleErrorConnection()
{
	int op;

	std::map<int,int>errno_map;

	errno_map[EACCES] = 1;
	errno_map[EAFNOSUPPORT] = 2;
	errno_map[EINVAL] = 3;
	errno_map[EMFILE] = 4;
	errno_map[ENFILE] = 5;
	errno_map[ENOBUFS] = 6;
	errno_map[ENOMEM] = 6;
	errno_map[EPROTONOSUPPORT] = 7;

	std::map<int, int>::iterator it = errno_map.find(errno);
	if (it != errno_map.end())
		op = it->second;
	else
		op = 0;

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