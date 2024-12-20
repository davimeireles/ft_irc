#include "../../includes/CommandHandler.hpp"
#include "../../includes/Client.hpp"

CommandHandler::CommandHandler()
{
	_commands["INVITE"] = new Invite();
	_commands["JOIN"] = new Join();
	_commands["KICK"] = new Kick();
	_commands["MODE"] = new Mode();
	_commands["NICK"] = new Nick();
	_commands["PART"] = new Part();
	_commands["PASS"] = new Pass();
	_commands["PRIVMSG"] = new Privmsg();
	_commands["QUIT"] = new Quit();
	_commands["TOPIC"] = new Topic();
	_commands["USER"] = new User();
	_commands["AUTH"] = new Authenticate();
	_commands["PING"] = new Ping();
	_commands["WHO"] = new Who();
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::handleCommand(string command, Client *client)
{

	if (command[0] == ':')
		command = command.substr(1);
	static string newcomand;
	bool canI = true;
	if (command.find("\n") == std::string::npos)
	{
		newcomand += command;
		canI = false;
	}
	else
	{
		newcomand += command;
		canI = true;
	}
	std::stringstream ss(newcomand);
	string cmd;

	while (std::getline(ss, cmd) && canI)
	{
		string command_name = cmd.substr(0, cmd.find(" "));

		for (unsigned int i = 0; i < command_name.length(); i++)
			command_name[i] = std::toupper(command_name[i]);


		std::map<string, Command *>::iterator it = _commands.find(command_name);
		if (command_name == "CAP")
			continue;
		else if (std::strncmp(command_name.c_str(), "AUTH", 4) == 0)
			it = _commands.find("AUTH");
		else if (it == _commands.end())
		{
			ERR_INVALIDCOMMAND(client, cmd);
			continue;
		}
		try
		{
			Command *operation = it->second;
			string argsBuffer = cmd.substr(cmd.find(" ") + 1);
			std::istringstream argsStream(argsBuffer);
			string argument;
			std::list<string> args;
			while (std::getline(argsStream, argument, ' '))
			{
				argument.erase(std::remove_if(argument.begin(), argument.end(), ::isspace), argument.end());
				args.push_back(argument);
			}
			operation->execute(client, args);
			newcomand.clear();
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
			throw std::runtime_error("Error: Cannot handle command");
		}
	}
}

std::map<string, Command*> CommandHandler::getCommands()
{
	return _commands;
}