#include "server.h"


Server::Server(int port)
{
	this->port = port;
	Start();
}

void Server::Send(SOCKET writeSock){
	std::string wBuff;

	while (1) {
		std::getline(std::cin, wBuff);
		if (":q" == (wBuff)) {
			break;
		}
		send(writeSock, wBuff.c_str(), wBuff.length() + 1, 0); 
	}
}

void Server::Receive(SOCKET readSock) {
	char buffer[512] = { 0 };
	int recBytes;

	while (1) {
		recBytes = recv(readSock, buffer, sizeof(buffer) - 1, 0);

		if (recBytes <= 0) {
			std::cout << "::Connection Ended\n" << std::endl;
			break;
		} 

		std::cout << buffer;

		if (recBytes != sizeof(buffer) - 1) { 
			std::cout << "\n";
		}
	}

}

void Server::Start() {
	WSADATA wsaData;
	SOCKET socketfd;
	SOCKADDR_IN serv_addr, cli_addr;

	if (WSAStartup(0x0202, &wsaData) != 0) {
		std::cout << "WSAStartup failed.\n";
	}

	socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketfd == -1) { std::cout << "Socket failed\n"; }

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1337);
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
											
	bind(socketfd, (SOCKADDR *)&serv_addr, sizeof(serv_addr));

	listen(socketfd, SOMAXCONN);

	SOCKET newsockfd = accept(socketfd, (SOCKADDR *)&cli_addr, 0);
	if (newsockfd == -1) { std::cout << "Connection Failed\n"; }

	std::thread rThread(&Server::Receive, this, newsockfd);
	
	Send(newsockfd);

	closesocket(socketfd);
	closesocket(newsockfd);
	WSACleanup();

	rThread.join();
}