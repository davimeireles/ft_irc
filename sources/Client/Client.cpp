#include "../../includes/Client.hpp"
#include "../../includes/Server.hpp"

/**
 * @brief Construct a new Client:: Client object
 * 
 * @param fd 
 */

Client::Client(int fd)
{
	_fd = fd;
	_user = new User("default", "default");
}

/**
 * @brief Construct a new Client:: Client object
 */

Client::Client()
{
	_fd = -1;
	_user = new User("default", "default");
}

/**
 * @brief Destroy the Client:: Client object
 */

Client::~Client()
{
	delete _user;
}

/**
 * @brief Get the Fd object
 * 
 * @return int 
 */

int Client::getFd()
{
	return (_fd);
}

/**
 * @brief Get the Info object
 * 
 * @return string 
 */

string Client::getInfo()
{
	return (_info);
}

/**
 * @brief Set the Fd object
 * 
 * @param fd 
 */

void Client::setFd(int fd)
{
	_fd = fd;
}

/**
 * @brief Set the Info object
 * 
 * @param info 
 */

void Client::setInfo(string info)
{
	_info = info;
}

/**
 * @brief Get the User object
 * 
 * @return User* 
 */

User *Client::getUser()
{
	return (_user);
}

/**
 * @brief Set the User object
 * 
 * @param user 
 */

void Client::setUser(User *user)
{
	_user = user;
}

void Client::handleDataFromClient(int client_fd)
{
	char buffer[1024];

	while (true)
	{
		ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
	
		if (bytes_read > 0)
		{
			this->setInfo(buffer);
			buffer[bytes_read] = '\0';
			ssize_t bytes_sent = send(client_fd, buffer, bytes_read, 0);
			cout << ORANGE << "Received: " << buffer << RESET << endl;
			if (bytes_sent < 0)
				cout << RED << "Failed to send data to client." << RESET << endl;
			cout << ORANGE << "Sent: " << bytes_sent << RESET << endl;
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