#pragma once

#include "utils.hpp"
#include "User.hpp"
#include "Client.hpp"

class Server;
class Client;

class User
{
	private:
		string _nickname;
		string _realname;
	
	public:
		User(string nickname, string realname);
		~User();

		string getNickname();
		string getRealname();

		void setNickname(string nickname);
		void setRealname(string realname);
};