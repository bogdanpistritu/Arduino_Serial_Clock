#pragma once
#include <Windows.h>
class BasicCOMOperation
{
public:
	BasicCOMOperation(void);	
	~BasicCOMOperation(void);
	HANDLE openCOMM(LPCWSTR);
	void writeToCOMM(char[], HANDLE); //Manda alla porta COM selezionata un array di byte.	
	void sendByte(char, HANDLE);
	char readFromCOMM(HANDLE);
};

