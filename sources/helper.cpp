#include "../includes/helper.hpp"


bool	checkValidPort(string port)
{
	int i = 0;
	while (port[i])
	{
		if (!std::isdigit(port[i]))
			return (false);
		i++;
	}

	double d_port = std::strtod(port.c_str(), NULL);
	
	if ((d_port >= 6660 && d_port <= 6669) || d_port == 7000)
		return (true);
	return (false);
}

bool    checkValidPassword(string password)
{
    bool    valid_length = false;
    bool    digit = false;
    bool    upper_character = false;
    bool    lower_character = false;

    if (password.size() < 8)
        return (false);
    else
        valid_length = true;

    std::string::iterator it = password.begin();

    for (;it != password.end(); ++it)
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


void	p_error(string error)
{
	cout << RED << error << RESET << endl;
	exit (1);
}