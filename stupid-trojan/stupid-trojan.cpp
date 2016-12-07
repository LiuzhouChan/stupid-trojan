// stupid-trojan.cpp : 定义控制台应用程序的入口点。
//

#include <vector>  
#include "afxwin.h"  
#include "BrowsHistory.h"  

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	BrowsHistory browseHistory;
	browseHistory.Init();
	while (!browseHistory.m_bStatus);	//等待获取完成  
	auto data = browseHistory.GetBrowsHistory();
	auto it = data.begin();

	for (; it<data.end(); ++it)
	{
		wprintf(_T("%s\n"), it->strURL);
	}
	getchar();
	return 0;
}