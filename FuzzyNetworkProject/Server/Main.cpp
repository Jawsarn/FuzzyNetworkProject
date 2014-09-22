/*fuzzy main*/

#include <WinSock2.h>
#include <iostream>

using namespace std;

/*
AF_INET and PF_INET is the same PF_INET is defined as AF_INET

*/
SOCKET g_ServerSocket;
SOCKET g_ClientSocket;
bool Startup();
void SendData(SOCKET p_Socket, std::string p_Message);
std::string RecieveData(SOCKET p_Socket);



int main(){

	bool StartUpFinished = Startup();

	if (StartUpFinished)
	{
		while (true)
		{

		}
	}

	system("pause");
	closesocket(g_ServerSocket);
	closesocket(g_ClientSocket);
	WSACleanup();
	return 0;
}

bool Startup()
{
	WORD t_Version = MAKEWORD(2, 2);
	WSADATA wsaData = { 0 };

	//startup library
	int t_RetValue = WSAStartup(t_Version, &wsaData);

	if (t_RetValue == SOCKET_ERROR)
	{
		cout << "Failed to startup Winsock Library\n";
		return false;
	}
	cout << "Starting Server...\n";


	//create server socket
	g_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (g_ServerSocket == INVALID_SOCKET)
	{
		cout << "Failed to create server socket\n";
		return false;
	}
	cout << "Server socket creation complete...\n";


	//create server adress
	SOCKADDR_IN t_AddrListen = { 0 };
	t_AddrListen.sin_family = PF_INET;
	t_AddrListen.sin_port = htons(1337); //a socket used for in
	t_AddrListen.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //any adress is allowed to send in


	//bind the socket to the adress
	t_RetValue = bind(g_ServerSocket, (SOCKADDR*)&t_AddrListen, sizeof(SOCKADDR));
	if (t_RetValue == SOCKET_ERROR)
	{
		cout << "Failed to bind server socket to adress\n";
		return false;
	}
	cout << "Server binding complete...\n";


	//tell how many clients the socket can queue
	listen(g_ServerSocket, 5); //the backlock number is how many connections to be expected

	cout << "Listening complete...\n";


	//start accepting a client , it will give us the client socket and adress(which is needed to send messages)
	SOCKADDR_IN t_ClientAdress = { 0 };
	int something = sizeof(SOCKADDR);

	g_ClientSocket = accept(g_ServerSocket, (SOCKADDR*)&t_ClientAdress, &something); //waits for client socket
	if (g_ServerSocket == INVALID_SOCKET)
	{
		cout << "Failed to establish connection with client\n";
		return false;
	}
	cout << "Connection established with client...\n";

	std::string t_SendString = "ping";
	
	

	

	ULONGLONG m_PrevTime = GetTickCount64();
	
	SendData(g_ClientSocket, t_SendString);

	string t_ReturnMessage = RecieveData(g_ClientSocket);
	if (t_ReturnMessage == "ping")
	{
		ULONGLONG t_CurrentTime = GetTickCount64();
		float m_DeltaTime = (t_CurrentTime - m_PrevTime) / 1000.0f;
		cout << "Pinged client for " << m_DeltaTime << " MS\n";
	}
	else
	{
		cout << "Recieved unkown message...\n";
	}

	system("pause");

	return false;

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