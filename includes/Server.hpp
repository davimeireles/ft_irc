#pragma once

#include "utils.hpp"
#include "helper.hpp"
#include "User.hpp"

class Client;
class User;

class Server
{
private:
	int _port;
	string _password;
	Server(Server const &copy);
	Server &operator=(Server const &rhs);
	Client *_client;

public:
	Server();
	~Server();

	int getPort();
	string getPassword();

	void setPort(int port);
	void setPassword(string password);

	void startServerIPV4();
	void startServerIPV6();
};