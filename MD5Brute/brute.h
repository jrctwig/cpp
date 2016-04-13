#pragma once
#include "md5.h"

class Brute
{
private:
	int * m_endHash;
	static bool finished;

	void Start();
	void Crack(int coreId, int coreMax);
	bool CompareHash(int * hash1, unsigned char * hash2);

public:
	Brute(int * endHash);
	
};
