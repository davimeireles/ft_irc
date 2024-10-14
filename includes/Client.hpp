#pragma once

#include "utils.hpp"
#include "User.hpp"

class User;

class Client
{
	private:
		int _fd;
		string _info;
		User *_user;

	public:
		Client(int fd);
		Client();
		~Client();

		int getFd();
		string getInfo();
		void setFd(int fd);
		void setInfo(string info);
		void setUser(User *user);
		User *getUser();
};