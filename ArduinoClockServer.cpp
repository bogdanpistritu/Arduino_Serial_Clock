#include "stdafx.h"
#include "BasicCOMOperation.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

HANDLE comPort = NULL; 
time_t t = time(0);
struct tm * hhmmss;
BasicCOMOperation _COMHandler = BasicCOMOperation();

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

void main()
{
	comPort = _COMHandler.openCOMM(L"COM9");
	cout << "Aspetto chiamata..." << endl;
	while(true)
	{
		//cout << _COMHandler.readFromCOMM(comPort) << endl;
		hhmmss = localtime(&t);
		switch(_COMHandler.readFromCOMM(comPort))
		{
		case 'h':
			{
				cout << "Trasmetto ore..." << endl;
				_COMHandler.sendByte(hhmmss->tm_hour, comPort);
				break;
			}
		case 'm':
			{
				cout << "Trasmetto minuti.." << endl;
				_COMHandler.sendByte(hhmmss->tm_min, comPort);
				break;
			}
		case 's':
			{
				cout << "Trasmetto secondi..." << endl;
				_COMHandler.sendByte(hhmmss->tm_sec, comPort);
				break;
			}		
		}
	}
}

