#include "brute.h"
#include <vector>
#include <thread>

bool Brute::finished = 0;

Brute::Brute(int * endHash){
	m_endHash = endHash;
	Start();

}


void Brute::Start() {

	const unsigned int nthreads = std::thread::hardware_concurrency();

	std::vector<std::thread> t(nthreads);

	for (int core = 0; core < nthreads; ++core) {
		t[core] = std::thread(&Brute::Crack, this, core, nthreads);
	}

	for (int i = 0; i < nthreads; i++) {
		t[i].join();
	}
}


bool Brute::CompareHash(int * hash1, unsigned char * hash2) {
	for (int i = 0; i < 16; i++) {
		if (hash1[i] != hash2[i]) {
			return false;
		}
	}

	return true;
}

void Brute::Crack(int coreId, int coreMax){

	int length = 1;
	//calculate the possible combinations and divide by threads
	unsigned long long poss = (pow(26, length) + (coreMax - 1)) / coreMax;
	unsigned long long startN = coreId*poss;
	unsigned long long endN = (coreId + 1)*poss;
	unsigned long long val;

	char startWd[] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };

	MD5 md5;

	while(1){
		for(; startN < endN; ++startN){

			if (finished) return;

			val = startN;

			//26 is the number of lower case characters, 97 is where the alphabet starts in ASCII
			for(char * j = startWd; j < &startWd[length]; j++){ 
				*j = val%26 + 97;
				val /= 26;
			}

			md5.update(startWd, length);
			md5.finalize();	

			if(CompareHash(m_endHash, md5.hexdigest())){
				std::cout << "Hash" << " = " << startWd << std::endl;
				finished = 1;
				return;
			}
		}

		poss = (pow(26, ++length) + (coreMax - 1)) / coreMax; 
		startN = coreId*poss;
		endN = (coreId + 1)*poss;
	}


}


