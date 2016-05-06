#include "client.h"


Client::Client(std::string host, int port)
{
	this->host = host;
	this->port = port;
	Start();
}

void Client::Send(SOCKET writeSock) {
	std::string wBuff;

	while (1) {
		std::getline(std::cin, wBuff);

		if (":q" == (wBuff)) {
			break;
		}

		send(writeSock, wBuff.c_str(), wBuff.length() + 1, 0); 
	}
}

void Client::Receive(SOCKET readSock) {
	char buffer[512] = { 0 };
	int recBytes;

	while (1) { 
		recBytes = recv(readSock, buffer, sizeof(buffer) - 1, 0);

		if (recBytes <= 0) {
			std::cout << "::Connection Ended\n"; 
			break;
		}

		std::cout << buffer;

		if (recBytes != sizeof(buffer) - 1) { 
			std::cout << "\n";
		}

	}
}

void Client::Start() { 
	WSADATA wsaData;
	SOCKET mSocket;
	SOCKADDR_IN target;

	if (WSAStartup(0x0202, &wsaData) != 0) {
		std::cout << "WSAStartup failed.\n";
	}

	target.sin_family = AF_INET; 
	target.sin_port = htons(1337); 
	target.sin_addr.s_addr = inet_addr(host.c_str()); 

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
	if (mSocket == -1) { std::cout << "::Socket Creation Failed" << std::endl; }

	if(connect(mSocket, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR){
		std::cout<<"::Connection Failed\n";
	}else{
		std::cout<<"::Connected to server, type ':q' to quit\n";
	}

	std::thread rThread(&Client::Receive, this, mSocket);

	Send(mSocket);

	closesocket(mSocket);
	WSACleanup();

	rThread.join();
}