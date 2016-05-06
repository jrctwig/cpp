#pragma once
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>


class Server
{
public:
	Server(int port);
private:
	void Receive(SOCKET writeSock);
	void Send(SOCKET readSock);
	void Start();

	int port;
};

