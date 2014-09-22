/*this is not a fuzzy main*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>


using namespace std;



void SendData(SOCKET p_Socket, std::string p_Message);
std::string RecieveData(SOCKET p_Socket);


int main(){

	WORD word = MAKEWORD(2, 2);
	WSADATA data;


	int result = WSAStartup(word, &data);

	if (result == SOCKET_ERROR)
		cout << "u not fuzzy at all!\n";
	else
		cout << "awesome!\n";

	SOCKET fuzzySock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN fuzzyAddress;

	fuzzyAddress.sin_family = AF_INET;
	fuzzyAddress.sin_port = htons(1337);
	fuzzyAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	int result2 = connect(fuzzySock, (SOCKADDR*)&fuzzyAddress, sizeof(fuzzyAddress));

	if (result2 == SOCKET_ERROR)
		cout << "u not fuzzy at all!\n";
	else
		cout << "awesome!\n";

	string t_Message = RecieveData(fuzzySock);
	if (t_Message == "ping")
	{
		SendData(fuzzySock, "ping");
	}


	system("pause");
	closesocket(fuzzySock);
	WSACleanup();
	return 0;
}

void SendData(SOCKET p_Socket, std::string p_Message)
{
	//copy string message into char array
	char t_Buffer[512] = { 0 };
	strncpy_s(t_Buffer, p_Message.c_str(), sizeof(t_Buffer));
	t_Buffer[sizeof(t_Buffer)-1] = 0;

	int t_DataLeft = 512;
	int t_DataPos = 0;
	int t_DataSent = 0;

	do
	{
		t_DataSent = send(p_Socket, &t_Buffer[t_DataPos], t_DataLeft, 0);
		t_DataLeft -= t_DataSent;
		t_DataPos += t_DataSent;

	} while (t_DataLeft > 0);

	memset(&t_Buffer, 0, sizeof(t_Buffer));
}

std::string RecieveData(SOCKET p_Socket)
{
	char t_Buffer[512] = { 0 };

	int t_DataLeft = 512;
	int t_DataPos = 0;
	int t_DataSent = 0;

	do
	{
		if (t_DataSent == SOCKET_ERROR)
		{
			cout << "Error receiving data" << endl;
			memset(&t_Buffer, 0, sizeof(t_Buffer));
			break;
		}

		t_DataSent = recv(p_Socket, &t_Buffer[t_DataPos], t_DataLeft, 0);
		t_DataLeft -= t_DataSent;
		t_DataPos += t_DataSent;
	} while (t_DataLeft > 0);

	string text = t_Buffer;

	memset(&t_Buffer, 0, sizeof(t_Buffer));

	return text;
}