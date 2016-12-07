#pragma once  
#include <iostream>  
#include <algorithm>  
#include <functional>  
#include <vector>  
#include "afxwin.h"  
#include "CppSQLite3.h"  
struct BrowsData
{
public:
	// 网址  
	CString strURL;

	// 对应网址访问次数  
	unsigned int nCount;

	bool operator < (const BrowsData &m)const
	{
		return nCount > m.nCount;
	}
};
class BrowsHistory
{
private:

	// 保存获得的网址和访问次数  
	std::vector<BrowsData> m_BrowsHistroy;
private:

	// Chrome网址过滤，如只取网址com前边的  
	void urlFiltrateChrome(CString strUrlName);

	// 查询进程是否已存在, 返回true表示存在；自动结束其进程  
	bool IsRunning(CString exe);
	// 编码转换  
	void ConvertUtf8ToGBK(CStringA &strUtf8);
	// 获取浏览器历史记录  
	void InitHistroy(void);
	// 多线程函数  
	static void ThreadPro(LPVOID * ptr);
	// 对获得的网址进行排序  
	void Sort(void);
public:
	BrowsHistory();
	~BrowsHistory();
	// 获取网址的进程，是否执行完；执行完时为true；  
	bool m_bStatus;
	// 初始化  
	void Init(void);
	// 获取浏览器历史记录  
	std::vector<BrowsData> GetBrowsHistory(void) const;
};

