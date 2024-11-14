/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:31:42 by dmeirele          #+#    #+#             */
/*   Updated: 2024/11/13 17:50:01 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iomanip>
#include <climits>
#include <exception>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <cctype>
#include <ranges>
#include <cstring>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <poll.h>
#include <netdb.h>
#include <csignal>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define PURPLE "\e[35m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

#define ERR_ALREADYREGISTERED(client) client->response(client->getHostname() + " :You may not reregister\r\n");
#define ERR_PASSWDMISMATCH(client) client->response(client->getHostname() + " " + ":Password incorrect\r\n");
#define ERR_PASSREQUIRED(client) client->response("ERROR :You need to setup password before use this command\r\n");
#define ERR_NICKREQUIRED(client) client->response("ERROR :You need to setup password and nickname before use this command\r\n");

#define ERR_NONICKNAMEGIVEN(client) client->response(client->getHostname() + ":No nickname given");
#define ERR_ERRONEUSNICKNAME(client, nickname) client->response(client->getHostname() + nickname + ":Erroneus nickname\r\n");
#define ERR_NICKNAMEINUSE(client, nickname) client->response(client->getHostname() + nickname + ":Nickname is already in use\r\n");

#define ERR_NOSUCHCHANNEL(client, ch_name) client->response(client->getHostname() + client->getNickname() + " " + ch_name + " :No such channel\r\n");
#define ERR_BADCHANNELKEY(client, ch_name) client->response(client->getHostname() + ch_name + ":Cannot join channel (+k)\r\n");
#define ERR_INVITEONLYCHAN(client, ch_name) client->response(client->getHostname() + ch_name + ":Cannot join channel (+i)\r\n");
#define ERR_TOOMANYCHANNELS(client, ch_name) client->response(client->getHostname() + ch_name + ":You have joined too many channels\r\n");
#define ERR_MODEINVITEONLY(client, ch_name) client->response(client->getHostname() + ch_name + ":Channel has invite mode only\r\n");
#define ERR_BANNEDFROMCHAT(client, ch_name) client->response(client->getHostname() + ch_name + ":You have been banned from this channel\r\n");
#define ERR_CHANNELUSERLIMIT(client, ch_name) client->response(client->getHostname() + ch_name + ":Channel reached max number of clients\r\n");
#define ERR_ALREADYJOINED(client, ch_name) client->response(client->getHostname() + ch_name + ":You already joined this channel\r\n");

#define ERR_AUTH(client) client->response("ERROR :Access denied: Authentication required\r\n");
#define ERR_NEEDMOREPARAMS(client, command) client->response(client->getHostname() + " " + command + " :Not enough parameters\r\n");
#define ERROR(client) client->response("ERROR :Connection timeout ;Server closing a client connection because it is unresponsive.\r\n");
#define ERR_INVALIDPARAMETERS(client) client->response("ERROR :Invalid Parameters\r\n");

#define ERR_NOSUCHNICK(client, nickname) client->response(client->getHostname() + " " + client->getNickname() + " :No such nick/channel\r\n");
#define ERR_CANNOTREMOVEUSER(client, nickname) client->response(client->getHostname() + " " + client->getNickname() + " :Cannot remove user\r\n");
#define ERR_NOSUCHNICKONCH(client, nickname) client->response(client->getHostname() + " " + client->getNickname() + " :No such nick on channel\r\n");
#define ERR_NOSUCHSERVER(client) client->response(client->getHostname() + " " + " :No such server\r\n");
#define ERR_CANNOTSENDTOCHAN(client, ch_name) client->response(client->getHostname() + " " + ch_name + " :Cannot send to channel\r\n");
#define ERR_NORECIPIENT(client, command) client->response(client->getHostname() + " :No recipient given " + command + "\r\n");
#define ERR_NOTEXTTOSEND(client) client->response(client->getHostname() + " :No text to send\r\n");

#define RPL_WELCOME(client) client->response("001:Welcome to the ModernIRC Network, " + client->getNickname() + "[!" + client->getUsername() + "@" + client->getHostname() + "]\r\n");
#define RPL_YOURHOST(client) client->response("002:Your host is ModernIRC, running version v1.0\r\n");
#define RPL_CREATED(client) client->response("003:This server was created <datetime>\r\n");
#define RPL_MYINFO(client) client->response("004:MordenIRC v1.0 USERS/OPERATORS +itkol\r\n");
#define RPL_ISUPPORT(client) client->response("005:MordernIRC CHANTYPES=# NICKLEN=8:are supported by this server\r\n");
