/*this is not a fuzzy main*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>

 
using namespace std;





int main(){

	WORD word = MAKEWORD(2, 2);
	WSADATA data;
	

	int result = WSAStartup(word,&data);

	if (result != 0)
		cout << "u not fuzzy at all!\n";
	else
		cout << "awesome!\n";

	SOCKET fuzzySock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN fuzzyAddress;

	fuzzyAddress.sin_family = AF_INET;
	fuzzyAddress.sin_port = htons(1337);
	fuzzyAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	int result2 = connect(fuzzySock, (SOCKADDR*)&fuzzyAddress, sizeof(fuzzyAddress));

	if (result2 != 0)
		cout << "u not fuzzy at all!\n";
	else
		cout << "awesome!\n";



	system("pause");
	closesocket(fuzzySock);
	WSACleanup(); 
	return 0;
}