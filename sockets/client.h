#pragma once
#include <winsock2.h>
#include <iostream>
#include <stdio.h> //printf, stderr
#include <thread>
#include <string>


class Client
{
public:
	Client(std::string host, int port);
private:
	void Send(SOCKET writeSock);
	void Receive(SOCKET readSock);
	void Start();

	std::string host;
	int port;
};

