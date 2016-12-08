// stupid-trojan.cpp : 定义控制台应用程序的入口点。
//

#include <vector>  
#include "afxwin.h"  
#include "BrowsHistory.h"  
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
	BrowsHistory browseHistory;
	browseHistory.Init();
	while (!browseHistory.m_bStatus);	//等待获取完成  
	auto data = browseHistory.GetBrowsHistory();
	
	wofstream outfile("log");
	for (auto it = data.begin(); it<data.end(); ++it)
	{
		wcout << it->strURL.GetString() << "  " << it->nCount << endl;
		outfile << it->strURL.GetString() << "  " << it->nCount << endl;
	}

	outfile.close();
	getchar();
	return 0;
}