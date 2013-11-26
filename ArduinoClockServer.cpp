#include "stdafx.h"
#include "BasicCOMOperation.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

HANDLE hndl = NULL; 
time_t t = time(0);
struct tm * hhmmss;
BasicCOMOperation * _COMHandler = new BasicCOMOperation("COM3");

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

void main()
{
	do
	{
		Sleep(1000);	
		system("CLS");
		cout << "Tentativo di aprire la COM3..." << endl;
	}while(!_COMHandler->openCOMM(L"COM3"));
	hndl = _COMHandler->comPort;
	cout << "[ OK ]" << endl << "Aspetto chiamata" << endl;
	while(true)
	{
		//cout << _COMHandler.readFromCOMM(comPort) << endl;
		hhmmss = localtime(&t);
		switch(_COMHandler->readFromCOMM(hndl))
		{
		case 'h':
			{
				cout << "Trasmetto ore [ " << hhmmss->tm_hour << " ]" << endl;
				_COMHandler->sendByte(hhmmss->tm_hour, hndl);				
				break;
			}
		case 'm':
			{
				cout << "Trasmetto minuti [ " << hhmmss->tm_min << " ]"<< endl;
				_COMHandler->sendByte(hhmmss->tm_min, hndl);				
				break;
			}
		case 's':
			{
				cout << "Trasmetto secondi [ " << hhmmss->tm_sec << " ]" << endl;
				_COMHandler->sendByte(hhmmss->tm_sec, hndl);				
				break;
			}		
		}
	}
}

