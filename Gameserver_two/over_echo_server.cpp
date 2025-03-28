// ---------------------------------------------------------------------------
// over_echo_server
// ---------------------------------------------------------------------------

#include <iostream>
#include <WS2tcpip.h>

#pragma comment(lib, "WS2_32.LIB")

constexpr short SERVER_PORT = 3000;
constexpr char SERVER_ADDR[] = "127.0.0.1"; // constexpr 은 포인터가 안된다.
WSABUF recv_wsabuf[1];

char send_buffer[1024];
WSABUF wsabuf[1];
WSAOVERLAPPED send_over;

SOCKET c_socket;

void CALLBACK recv_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

void CALLBACK send_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED p_over, DWORD flag) {

	recv_wsabuf[0].len = sizeof(recv_buffer);
	recv_wsabuf[0].buf = recv_buffer;

	DWORD recv_flag = 0;

	ZeroMemory(&recv_over, sizeof(recv_over));
	WSARecv(c_socket, recv_wsabuf, 1, NULL, &recv_flag, &recv_over, recv_callback);

}

void CALLBACK recv_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED p_over, DWORD flag) {
	recv_buffer[num_bytes] = 0;
	std::cout << "From client: " << recv_buffer << std::endl;

	memcpy(send_buffer, recv_buffer, recv_bytes);
	wsabuf[0].buf = send_buffer;
	wsabuf[0].len = recv_bytes;
	WSAOVERLAPPED send_over;
	ZeroMemory(&send_over, sizeof(send_over));
	DWORD size_sent;
	WSASend(c_socket, send_wsabuf, 1, &size_sent, 0, &send_over, NULL);

}

int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	SOCKET s_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);;

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
	c_socket = WSAAccept(s_socket, reinterpret_cast<sockaddr*>(&addr), &addr_size, NULL, NULL);



	send_callback(0, 0, 0, 0);

	while (true) SleepEx(0, TRUE);

	closesocket(c_socket);
	WSACleanup();
}


