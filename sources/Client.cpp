#include "../includes/Client.hpp"
#include "../includes/Server.hpp"

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