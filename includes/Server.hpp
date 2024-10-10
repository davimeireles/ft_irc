#pragma once

#include "utils.hpp"

class Server
{
    private:
        int     _port;
        string  _password;
        Server(Server const &copy);
        Server& operator=(Server const &rhs);

    public:
        Server();
        ~Server();

        int     getPort();
        string  getPassword();

        void    setPort(int port);
        void    setPassword(string password);
};