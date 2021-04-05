#include "stdafx.h"

#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <time.h>
#include <iostream>
#include <fcntl.h>
#include <vector>
#include <mutex>
#pragma comment(lib, "Ws2_32.lib")
#define MAXDATASIZE 700


class TwitchIRC
{

public:
	TwitchIRC();
	TwitchIRC(char * _nick, char * _usr, char * _password);
	~TwitchIRC();
	void checkOnce();
	void start();
	bool isConnected(char *buf);
	char * timeNow();
	bool sendData(const char *msg);
	bool sendChat(const char *msg, const char *channel);
	void msgHandle(char * buf);
	void sendPong(char *buf);
	bool charSearch(char *toSearch, char *searchFor);
	std::string msg;
	std::vector<std::string> v;
	const char* usr;
	const char* nick;
	const char* password;
	const char* channel;
	const char* channelSave;
	int mySocket;
};

