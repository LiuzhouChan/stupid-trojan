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
	// ��ַ  
	CString strURL;

	// ��Ӧ��ַ���ʴ���  
	unsigned int nCount;

	bool operator < (const BrowsData &m)const
	{
		return nCount > m.nCount;
	}
};

class PersonInfo
{
public:
	CString url;
	CString username;
	PersonInfo(CString &purl, CString &pname);
};

class SearchInfo
{
public:
	CString term;
	SearchInfo( CString &pname);
};
class BrowsHistory
{
private:
	std::vector<SearchInfo> m_search_info;
	std::vector<PersonInfo> m_person_info;
	std::vector<BrowsData> m_BrowsHistroy;
private:

	void urlFiltrateChrome(CString strUrlName);

	bool IsRunning(CString exe);
	// ����ת��  
	void ConvertUtf8ToGBK(CStringA &strUtf8);
	// ��ȡ�������ʷ��¼  
	void InitHistroy(void);
	// ���̺߳���  
	static void ThreadPro(LPVOID * ptr);
	// �Ի�õ���ַ��������  
	void Sort(void);
public:
	BrowsHistory();
	~BrowsHistory();
	// ��ȡ��ַ�Ľ��̣��Ƿ�ִ���ꣻִ����ʱΪtrue��  
	bool m_bStatus;
	// ��ʼ��  
	void Init(void);
	// ��ȡ�������ʷ��¼  
	std::vector<BrowsData> GetBrowsHistory(void) const;
	std::vector<PersonInfo> GetPersonInfo() const;
	std::vector<SearchInfo> GetSearchInfo() const;
};

