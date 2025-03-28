// ---------------------------------------------------------------------------
// echo server
// ---------------------------------------------------------------------------

#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.LIB")

constexpr short SERVER_PORT = 3000;
constexpr char SERVER_ADDR[] = "127.0.0.1"; // constexpr 은 포인터가 안된다.

int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	SOCKET s_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);;

	if (s_socket <= 0)
		std::cout << "ERROR" << "WHY : ";
	else
		std::cout << "Socket Created.\n";

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, SERVER_ADDR, &addr.sin_addr);
	bind(s_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(SOCKADDR_IN));
	listen(s_socket, SOMAXCONN);
	INT addr_size = sizeof(SOCKADDR_IN);
	SOCKET c_socket = WSAAccept(s_socket, reinterpret_cast<sockaddr*>(&addr), &addr_size, NULL, NULL);

	while (true) {
		
		char recv_buffer[1024];
		WSABUF recv_wsabuf[1];
		recv_wsabuf[0].buf = recv_buffer;
		recv_wsabuf[0].len = sizeof(recv_buffer);
		DWORD recv_bytes;
		DWORD recv_flag = 0;

		auto ret = WSARecv(c_socket, recv_wsabuf, 1, &recv_bytes, &recv_flag, NULL, NULL);

		recv_buffer[recv_bytes] = 0;
		std::cout << "From_Client : " << recv_buffer << std::endl;
		
		
		char buffer[1024];
		std::cout << "INPUT : ";
		std::cin.getline(buffer, sizeof(buffer));

		WSABUF wsabuf[1];
		wsabuf[0].buf = buffer;
		wsabuf[0].len = strlen(buffer); // sizeof 쓰면 의미없는 것들도 다 포함하기때문에 안씀
		DWORD size_sent;
		WSASend(c_socket, wsabuf, 1, &size_sent, 0, NULL, NULL);

	}
	closesocket(c_socket);
	WSACleanup();
}
