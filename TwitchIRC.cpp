#include "stdafx.h"
#include "TwitchIRC.h"

bool setup = false;
char* port;



using namespace std;
recursive_timed_mutex mtx;

TwitchIRC::TwitchIRC()
{
	channel = "";
	channelSave = "";
	nick = "";
	usr = "";
	password = "";
	mySocket = 0;
}

TwitchIRC::TwitchIRC(char * _nick, char * _usr, char * _password)
{
	nick = _nick;
	usr = _usr;
	password = _password;
	channel = "";
	channelSave = "";
	mySocket = 0;
}

TwitchIRC::~TwitchIRC()
{
	closesocket(mySocket);
}




void TwitchIRC::start()
{
	struct addrinfo hints, *servinfo;

	setup = true;

	port = "6667";

	//Ensure that servinfo is clear
	memset(&hints, 0, sizeof hints); //make sure the struct is empty

	//setup hints
	hints.ai_family = AF_UNSPEC;    //IPv4 or IPv6 doesnt matter
	hints.ai_socktype = SOCK_STREAM;        //TCP stream sockets

	//Start WSA to be able to make DNS lookup
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//Setup the structs if error, print why
	int res;
	if ((res = getaddrinfo("irc.twitch.tv", port, &hints, &servinfo)) != 0)
	{
		setup = false;
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
		WSACleanup();
	}

	//setup socket
	if ((mySocket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)))
	{
		perror("client: socket");
	}

	//Connect
	if (connect(mySocket, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		closesocket(mySocket);
		perror("Client Connected");
	}

	//We dont need this anymore
	freeaddrinfo(servinfo);

	u_long mode = -1;
	int ret = ioctlsocket(mySocket, FIONBIO, &mode);


	int count = 0;
	while (count < 5)
	{
		count++;

		switch (count)
		{
		case 1:
			//after 3 receives send data to server (as per IRC prot)
			sendData(password);
			sendData(nick);
			sendData(usr);
			break;
		case 2:
			//Join a channel after we connect
			sendData(channel);
			break;
		default:
			break;
		}
	}
	msg = "bread";

}

bool TwitchIRC::isConnected(char *buf)
{
	if (charSearch(buf, "/MOTD"))
		return true;

	return false;
}

char * TwitchIRC::timeNow()
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return asctime(timeinfo);
}






bool TwitchIRC::sendData(const char *msg)
{
	int len = strlen(msg);
	int bytes_sent = send(mySocket, msg, len, NULL);

	if (bytes_sent == 0)
		return false;

	return true;
}



bool TwitchIRC::sendChat(const char *msg, const char *channel)
{
	string c = channel;
	string s = "PRIVMSG #" + c + " :"+msg + "\r\n";
	sendData(s.c_str());
	return false;
}

void TwitchIRC::msgHandle(char * buf)
{
	if (charSearch(buf, "hay"))
	{
		sendData("PRIVMSG #ubuntu :I am awake\r\n");
	}
}

void TwitchIRC::sendPong(char *buf)
{
	//Get the reply address
	//loop through bug and find the location of PING
	//Search through each char in toSearch

	char * toSearch = "PING ";

	for (int i = 0; i < strlen(buf); i++)
	{
		//If the active char is equal to the first search item then search toSearch
		if (buf[i] == toSearch[0])
		{
			bool found = true;
			//search the char array for search field
			for (int x = 1; x < 4; x++)
			{
				if (buf[i + x] != toSearch[x])
				{
					found = false;
				}
			}

			//if found return true;
			if (found == true)
			{
				int count = 0;
				//Count the chars
				for (int x = (i + strlen(toSearch)); x < strlen(buf); x++)
				{
					count++;
				}

				//Create the new char array
				char* returnHost = new char[count + 5];
				returnHost[0] = 'P';
				returnHost[1] = 'O';
				returnHost[2] = 'N';
				returnHost[3] = 'G';
				returnHost[4] = ' ';

				count = 0;
				//set the hostname data
				for (int x = (i + strlen(toSearch)); x < strlen(buf); x++)
				{
					returnHost[count + 5] = buf[x];
					count++;
				}

				//send the pong
				if (sendData(returnHost))
				{
					cout << timeNow() << "  Ping Pong" << endl;
				}

				delete returnHost;
			}
		}
	}
}

bool TwitchIRC::charSearch(char *toSearch, char *searchFor)
{
	int len = strlen(toSearch);
	int forLen = strlen(searchFor); //The length of the searchfor field

	//Search through each char in toSearch
	for (int i = 0; i < len; i++)
	{
		bool found = true;

		//search the char array for search field
		for (int a = 0; a < forLen; a++)
		{
			if (searchFor[a] != toSearch[i + a])
			{
				found = false;
			}
		}

		if (found)
			return 1;
	}
	return 0;
}



void TwitchIRC::checkOnce() {

	//Recv some data
	int numbytes;
	char buf[MAXDATASIZE];
	
	mtx.lock();
		//Recv & print Data
		numbytes = recv(mySocket, buf, MAXDATASIZE - 1, 0);
		// msg = "**********************************************toast\n";

		if (numbytes > 0) {
			buf[numbytes] = '\0';
			cout << buf;
		}
		if (numbytes > 3) {
			msg = buf;
			//v.push_back(msg);
		}
		else {
			return;
		}
		//buf is the data that is received

		//pass buf to the message handler
		msgHandle(buf);

		//if ping received
		if (charSearch(buf, "PING"))
		{
			sendPong(buf);
		}

		//break if connection closed
		if (numbytes == 0)
		{
			cout << "---------------------CONNECTION CLOSED---------------------";
			cout << timeNow() << endl;
		}
		mtx.unlock();
}
/*int main()
{
	TwitchIRC bot = TwitchIRC("NICK prabot\r\n", "USER prabot\r\n", "PASS oauth:f4pij3ehsuaypw1yrdh2me6y1djjhy\r\n");
	bot.start();

	return 0;
}*/

