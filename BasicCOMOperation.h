#pragma once
#include <Windows.h>
#include <string>
class BasicCOMOperation
{
public:
	HANDLE comPort;
	BasicCOMOperation(std::string s);	
	~BasicCOMOperation(void);
	bool openCOMM(LPCWSTR);
	void writeToCOMM(char[], HANDLE); //Manda alla porta COM selezionata un array di byte.	
	void sendByte(char, HANDLE);
	char readFromCOMM(HANDLE);
};

