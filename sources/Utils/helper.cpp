#include "../../includes/helper.hpp"

bool checkValidPort(string port)
{
	int i = 0;
	while (port[i])
	{
		if (!std::isdigit(port[i]))
			return (false);
		i++;
	}

	double d_port = std::strtod(port.c_str(), NULL);

	if (d_port == 6697)
		return (true);
	return (false);
}

bool checkValidPassword(string password)
{
	bool valid_length = false;
	bool digit = false;
	bool upper_character = false;
	bool lower_character = false;

	if (password.size() < 8)
		return (false);
	else
		valid_length = true;

	std::string::iterator it = password.begin();

	for (; it != password.end(); ++it)
	{
		if (std::isdigit(*it))
			digit = true;
		if (std::isupper(*it))
			upper_character = true;
		if (std::islower(*it))
			lower_character = true;
	}

	if (valid_length && digit && upper_character && lower_character)
		return (true);
	return (false);
}

void p_error(string error)
{
	cout << RED << error << RESET << endl;
	exit(1);
}

/**
 * @brief Handle the error connection
 */
void handleErrorConnection()
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