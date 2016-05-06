#include <string>
#include "brute.h"

int main(int argc, char *argv[]){

	if(argc < 2){
		std::cout << "Usage: " << argv[0] << " <MD5 hash>" << std::endl;
		return 0;
	}
	else if(strlen(argv[1]) != 32){
		std::cout << "Not a valid MD5 hash" << std::endl;
		return 0;
	}
	
	//convert hex into decimal
	std::string hex(argv[1]);
	int hexAsDec[16] = { 0 };

	for (int i = 0; i < 16; i++) {
		hexAsDec[i] = strtol(hex.substr(i * 2, 2).c_str(), NULL, 16);
	}
	

	Brute md5Brute(hexAsDec);
}