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

	return false;

}