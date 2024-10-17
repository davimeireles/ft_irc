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
	size_t max_clients_limit;
	string _password;
	sockaddr_in _server_sockIPV4;
	sockaddr_in6 _server_sockIPV6;
	std::map<int, Client*> _clients;

	Server(Server const &copy);
	Server &operator=(Server const &rhs);

public:
	Server(int port, string password);
	~Server();

	int getPort();
	string getPassword();

	void setPort(int port);
	void setPassword(string password);

	void startServerIPV4();
	void startServerIPV6();

	bool addClient(int fd);
};