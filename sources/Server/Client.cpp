#include "../../includes/Client.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"

/**
 * @brief Construct a new Client:: Client object
 *
 * @param fd
 */

Client::Client(string hostname, uint16_t port, int fd, Server *server)
{
	_fd = fd;
	_port = port;
	_hostname = hostname;
	_nickname = "";
	_username = "";
	_realname = "~guest";
	_password = "";
	_authenticated = false;
	_hasPassword = false;
	_hasNickname = false;
	_hasUsername = false;
	_server = server;
}

/**
 * @brief Destroy the Client:: Client object
 */

Client::~Client()
{
}

/**
 * @brief Get the Fd object
 *
 * @return int
 */

int Client::getFd() const
{
	return (_fd);
}

/**
 * @brief Get the Nickname object
 *
 * @return string
 */

string Client::getNickname() const
{
	return (_nickname);
}

/**
 * @brief Get the Username object
 *
 * @return string
 */

string Client::getUsername() const
{
	return (_username);
}

/**
 * @brief Get the Realname object
 *
 * @return string
 */

string Client::getRealname() const
{
	return (_realname);
}

/**
 * @brief Overload of the << operator
 *
 * @param os
 * @param client
 * @return std::ostream&
 */

std::ostream &operator<<(std::ostream &os, Client const &client)
{

	os << "Client: " << endl;
	os << "fd: " << client.getFd() << endl;
	os << "nickname: " << client.getNickname() << endl;
	os << "username: " << client.getUsername() << endl;
	os << "realname: " << client.getRealname() << endl;
	return (os);
}

/**
 * @brief Send a message to the client
 *
 * @param message
 */

void Client::response(string message)
{
	send(_fd, message.c_str(), message.size(), 0);
}

/**
 * @brief Get the Channel object
 *
 * @param name
 * @return Channel*
 */

Channel *Client::getChannel(string name)
{
	std::vector<Channel *>::iterator it;
	for (it = invited_channels.begin(); it != invited_channels.end(); it++)
	{
		if ((*it)->getName() == name)
			return (*it);
	}
	return (NULL);
}

/**
 * @brief Get the hostname from client
 *
 * @return hostname
 */

string Client::getHostname() const
{
	return (_hostname);
}

/**
 * @brief Set the Nickname object
 *
 * @param nickname
 */

void Client::setNickname(string nickname)
{
	_nickname = nickname;
}

/**
 * @brief Set the Username object
 *
 * @param username
 */

void Client::setUsername(string username)
{
	_username = username;
}

/**
 * @brief Set the Realname object
 *
 * @param realname
 */

void Client::setRealname(string realname)
{
	_realname = realname;
}

/**
 * @brief Set the Hostname object
 *
 * @param hostname
 */

void Client::setHostname(string hostname)
{
	_hostname = hostname;
}

/**
 * @brief Set the Password object
 *
 * @param password
 */

void Client::setPassword(string password)
{
	_password = password;
}

/**
 * @brief Get the Password object
 *
 * @return string
 */

string Client::getPassword() const
{
	return (_password);
}

/**
 * @brief Get the Server object
 *
 * @return Server*
 */

Server *Client::getServer()
{
	return (_server);
}

bool Client::isAuthenticated() const
{
	return (_authenticated);
}

void Client::setAuthenticated(bool authenticated)
{
	_authenticated = authenticated;
}

bool Client::hasPassword() const
{
	return (_hasPassword);
}
bool Client::hasNickname() const
{
	return (_hasNickname);
}
bool Client::hasUsername() const
{
	return (_hasUsername);
}

void Client::authenticatePassword(bool authenticated)
{
	_hasPassword = authenticated;
}
void Client::authenticateNickname(bool authenticated)
{
	_hasNickname = authenticated;
}
void Client::authenticateUsername(bool authenticated)
{
	_hasUsername = authenticated;
}