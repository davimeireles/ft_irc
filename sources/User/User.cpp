#include "../../includes/User.hpp"

/**
 * @brief Construct a new User:: User object
 * 
 * @param nickname 
 * @param realname 
 */

User::User(string nickname, string realname) : _nickname(nickname), _realname(realname)
{
	cout << GREEN << "User object created." << RESET << endl;
}

/**
 * @brief Destroy the User:: User object
 */

User::~User() {}

/**
 * @brief Get the Nickname object
 * 
 * @return string 
 */

string User::getNickname()
{
	return (_nickname);
}

/**
 * @brief Get the Realname object
 * 
 * @return string 
 */

string User::getRealname()
{
	return (_realname);
}

/**
 * @brief Set the Nickname object
 * 
 * @param nickname 
 */

void User::setNickname(string nickname)
{
	_nickname = nickname;
}

/**
 * @brief Set the Realname object
 * 
 * @param realname 
 */

void User::setRealname(string realname)
{
	_realname = realname;
}