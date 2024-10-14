#include "../includes/utils.hpp"
#include "../includes/helper.hpp"
#include "../includes/Server.hpp"

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		if (checkValidPort(argv[1]) == false)
			p_error("Invalid port. Try to use TCP ports 6660–6669, 7000.");
		if (checkValidPassword(argv[2]) == false)
			p_error("Password must have 8+ chars & include:\n1+ lowercase\n1+ uppercase\n1+ digit");

		Server* _server = new Server();
		_server->setPort(std::atoi(argv[1]));
		_server->setPassword(argv[2]);

		_server->startServerIPV4();

		delete _server;
		return (0);
	}
	else
		p_error("Usage: ./ircserv <port> <password>");
}