#include "client.h"
#include "server.h"

#pragma comment(lib, "Ws2_32.lib")


void main(){
	std::string input, host;
	int port;

	std::cout << "server or client?" << std::endl;
	std::cin >> input;

	if (input == "client") {
		std::cout << "What is the IP address of the server?" << std::endl;
		std::cin >> host;
		std::cout << "Which port number to be used?" << std::endl;
		std::cin >> port;

		Client newclient(host, port);
	}
	else if(input == "server"){
		std::cout << "Which port number to be used?" << std::endl;
		std::cin >> port;

		Server newServer(port);
	}
	else {
		std::cout << "Type 'server' or 'client'" << std::endl;
	}
}