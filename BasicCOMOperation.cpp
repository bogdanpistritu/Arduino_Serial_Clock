#include "StdAfx.h"
#include "BasicCOMOperation.h"
#include <Windows.h>
#include <iostream>

DWORD byteWritten = 0;
DWORD byteRead = 0;

BasicCOMOperation::BasicCOMOperation(void)
{
}

void BasicCOMOperation::sendByte(char byte, HANDLE commHandle) {
	 WriteFile(commHandle, &byte, 1, &byteWritten, NULL);	 
	 if(!FlushFileBuffers(commHandle))
		std::cout << "Error\n";	 
}

void BasicCOMOperation::writeToCOMM(char buffer[], HANDLE commHandle) { 

     WriteFile(commHandle, buffer, 4, &byteWritten, NULL);
	 if(!FlushFileBuffers(commHandle))
		std::cout << "Error\n";
}

char BasicCOMOperation::readFromCOMM(HANDLE commHandle) { 
	char read;
	if(!ReadFile(commHandle, &read, 1, &byteRead, NULL))
		std::cout << "Errore\n";
	return read;
}

HANDLE BasicCOMOperation::openCOMM(LPCWSTR COM) {

    HANDLE handle;
    handle = CreateFile(COM, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, 0);
    if(handle==INVALID_HANDLE_VALUE) {

		if(GetLastError()==ERROR_FILE_NOT_FOUND) 
			std::cout << "Errore la porta non esiste\n";
		return NULL;
    }    
	if(!SetupComm(handle, 4, 4))
		std::cout << "Error\n";    
	DCB serialParams = {0};    
    if(!GetCommState(handle, &serialParams)) {

		std::cout << "Errore\n";
		return NULL;     
    }
    serialParams.BaudRate = 9600;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY; 
    serialParams.fOutX = FALSE; 
    serialParams.fInX = FALSE; 
    serialParams.fOutxCtsFlow = FALSE;    
	serialParams.fRtsControl = RTS_CONTROL_DISABLE;
    serialParams.fOutxDsrFlow = FALSE;     
	serialParams.fDtrControl = DTR_CONTROL_DISABLE;
    
    if(!SetCommState(handle, &serialParams)) {
		std::cout << "Errore\n";
		return NULL;
    }
	COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    
    if(!SetCommTimeouts(handle, &timeouts)) {
		std::cout << "Errore\n";
		return NULL;
    }
	return handle;
}

BasicCOMOperation::~BasicCOMOperation(void)
{
}
