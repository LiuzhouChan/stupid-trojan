// // FileName: BrowsHistory.cpp  
#include "BrowsHistory.h"
#include <wininet.h>  
#include <shlobj.h>   
#include "Shlwapi.h"  
#include "tlhelp32.h"  
#include <atlconv.h>  
#include <dpapi.h>

#pragma  comment(lib,"Shlwapi.lib")  
#pragma comment(lib,"Common/sqlite3.lib")  

BrowsHistory::BrowsHistory()
{
	m_bStatus = false;
}
BrowsHistory::~BrowsHistory()
{
}

void BrowsHistory::urlFiltrateChrome(CString strUrlName)
{
	// 删除开始的"https://"  

	if (strUrlName.Find(_T("https://")) != -1)
	{
		strUrlName.Delete(0, 8);
	}
	else if (strUrlName.Find(_T("http://")) != -1)
	{
		strUrlName.Delete(0, 7);
	}
	int nIndex = strUrlName.Find(_T("/"));
	BrowsData browsDate;
	browsDate.nCount = 0;
	std::vector<BrowsData>::iterator iter;
	if (nIndex != -1)
	{
		for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); iter++)
		{
			if (iter->strURL == strUrlName.Left(nIndex))
			{
				iter->nCount += 1;
				return;
			}
		}
		browsDate.strURL = strUrlName.Left(nIndex);
		browsDate.nCount = 1;
		m_BrowsHistroy.push_back(browsDate);
	}
	else
	{
		for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); ++iter)
		{
			if (iter->strURL == strUrlName)
			{
				iter->nCount += 1;
				return;
			}
		}
		browsDate.strURL = strUrlName;
		browsDate.nCount = 1;
		m_BrowsHistroy.push_back(browsDate);
	}
}

bool BrowsHistory::IsRunning(CString exe)
{
	PROCESSENTRY32 pe32;
	HANDLE hprocess;
	hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hprocess, &pe32))
	{
		do
		{
			HANDLE h_id;
			h_id = OpenProcess(PROCESS_TERMINATE, false, pe32.th32ProcessID);
			CString exefile;
			exefile = pe32.szExeFile;
			exefile.MakeLower();
			exe.MakeLower();
			if (exefile == exe)
			{
				if (TerminateProcess(h_id, 0) != 0)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		} while (Process32Next(hprocess, &pe32));
	}
	return false;
}
void BrowsHistory::ConvertUtf8ToGBK(CStringA &strUtf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, (LPWSTR)wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	strUtf8 = szGBK;
	delete[] szGBK;
	delete[] wszGBK;
}


void BrowsHistory::Init(void)
{
	// 创建一个线程  
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPro, this, 0, NULL);
}
void BrowsHistory::InitHistroy(void)
{
	m_bStatus = false;
	m_BrowsHistroy.clear();

	char path[MAX_PATH];
	char pathlog[MAX_PATH];

	::SHGetSpecialFolderPathA(NULL, path, CSIDL_LOCAL_APPDATA, FALSE);
	::SHGetSpecialFolderPathA(NULL, pathlog, CSIDL_LOCAL_APPDATA, FALSE);
	strcat_s(path, "\\google\\chrome\\User Data\\default\\History");
	strcat_s(pathlog, "\\google\\chrome\\User Data\\default\\Login Data");

	if (PathFileExistsA(path))
	{
		// 谷歌浏览器正在运行，强制关闭；关闭后才能得到谷歌浏览器的历史记录  
		if (!IsRunning(_T("chrome.exe")))
		{
			try
			{
				CppSQLite3DB db;
				CppSQLite3Query query;
				db.open(path);
				query = db.execQuery("select url from urls");
				while (!query.eof())
				{
					CStringA utf8url=query.fieldValue("url");
					ConvertUtf8ToGBK(utf8url);
					urlFiltrateChrome((CString)utf8url);
					query.nextRow();
				}

				query = db.execQuery("select term from keyword_search_terms");
				while(!query.eof())
				{
					CStringA term= query.fieldValue("term");
					ConvertUtf8ToGBK(term);
					SearchInfo search_info(static_cast<CString>(term));
					m_search_info.push_back(search_info);
					query.nextRow();
				}
				db.close();
			}
			catch (CppSQLite3Exception& e)
			{

			}
		}
	}
	Sort();

	if (PathFileExistsA(pathlog))
	{
		if (!IsRunning(_T("chrome.exe")))
		{
			try
			{
				CppSQLite3DB db;
				CppSQLite3Query query;
				db.open(pathlog);
				query = db.execQuery("select origin_url,username_value from logins");
				while (!query.eof())
				{
					CStringA utf8url = query.fieldValue("origin_url");
					CString user_name = query.fieldValue("username_value");
					ConvertUtf8ToGBK(utf8url);
					PersonInfo person_info(static_cast<CString>(utf8url), user_name);
					m_person_info.push_back(person_info);
					query.nextRow();
				}
				db.close();
			}
			catch (CppSQLite3Exception& e)
			{
				return;
			}
		}
	}

	
}
void BrowsHistory::ThreadPro(LPVOID * ptr)
{
	auto pBrowsHistroy = (BrowsHistory*)ptr;
	pBrowsHistroy->InitHistroy();

	// 获取网址的函数执行完了  
	pBrowsHistroy->m_bStatus = true;
}
std::vector<BrowsData> BrowsHistory::GetBrowsHistory(void) const
{
	return m_BrowsHistroy;
}
std::vector<PersonInfo>BrowsHistory::GetPersonInfo() const
{
	return m_person_info;
}

std::vector<SearchInfo>BrowsHistory::GetSearchInfo() const
{
	return m_search_info;
}

void BrowsHistory::Sort(void)
{
	stable_sort(m_BrowsHistroy.begin(), m_BrowsHistroy.end(), std::less<BrowsData>());
}

PersonInfo::PersonInfo(CString& purl, CString& pname): url(purl),username(pname)
{
}
SearchInfo::SearchInfo( CString& pname) : term(pname)
{
}