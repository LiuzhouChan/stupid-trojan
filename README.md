## This is a trojan which is stupid

when it starts, it will set itself selfstart in the reg. 

And then kill the chrome to get the data. Then save them in a log file.

It download a hosts.txt from a ftp server(such like 192.168.1.103: 2112, you can define yours in the 

get_host_file() function in util.cpp).

In the hosts.txt you can get the ip and port of the server for the stupid trojan to connect.

By using the server, there are some commends U can enter.

"ls" will list the file which can be send to you email(you can change it in sendemail() in util.cpp).

"email" will send the email.

"get pathtofile" can add the file to the email send list.

"bye" will close the connection

"screenfetch" will capture the full screen and then add it in the email send list.

it you type other command, then they will be excuted in the host computer as cmd command.

after the email is sent, all files we generated will been distory. 

