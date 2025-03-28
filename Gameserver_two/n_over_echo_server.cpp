// ---------------------------------------------------------------------------
// over_echo_server < N : 1 >
// ---------------------------------------------------------------------------

#include <iostream>
#include <WS2tcpip.h>
#include <unordered_map>

#pragma comment(lib, "WS2_32.LIB")

constexpr short SERVER_PORT = 3000;
constexpr char SERVER_ADDR[] = "127.0.0.1"; // constexpr �� �����Ͱ� �ȵȴ�.


void CALLBACK g_recv_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK g_send_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

// std::unordered_map<WSAOVERLAPPED*, int>g_over_2_user;

void print_error_message(int s_err)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, s_err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	std::wcout << lpMsgBuf << std::endl;
	while (true);   // ����� ��
	LocalFree(lpMsgBuf);
}

class SESSION {
private:
	SOCKET			_c_socket;
	long long			_id;

	char			_recv_buffer[1024];
	WSABUF			_recv_wsabuf[1];
	WSAOVERLAPPED	_recv_over;
	
	char			_send_buffer[1024];
	WSABUF			_send_wsabuf[1];
	WSAOVERLAPPED	_send_over;

void do_recv()
{
	DWORD recv_flag = 0;
	ZeroMemory(&_recv_over, sizeof(_recv_over));
	_recv_over.hEvent = reinterpret_cast<HANDLE>(_id);
	auto ret = WSARecv(_c_socket, _recv_wsabuf, 1, NULL, &recv_flag, &_recv_over, g_recv_callback);
	if (0 != ret) {
		auto err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no) {
			print_error_message(err_no);
			exit(-1);
		}
	}
}

public:
	SESSION() {
		std::cout << "DEFAULT SESSION CONSTRUCTOR CALLED!! '\n";
		exit(-1);
	}
	SESSION(long long session_id,SOCKET s):_id(session_id),_c_socket(s)
	{
		_recv_wsabuf[0].len = sizeof(_recv_buffer);
		_recv_wsabuf[0].buf = _recv_buffer;

		_send_wsabuf[0].len = 0;
		_send_wsabuf[0].buf = _send_buffer;

		_send_over.hEvent = reinterpret_cast<HANDLE>(session_id);
		_recv_over.hEvent = reinterpret_cast<HANDLE>(session_id);

		do_recv();
			
	}
	~SESSION()
	{
		closesocket(_c_socket);
	}

	void recv_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED p_over, DWORD flag)
	{
		_recv_buffer[num_bytes] = 0;
		std::cout << "From Client[ " << _id << " ] : " << _recv_buffer << std::endl;

		memcpy(_send_buffer, _recv_buffer, num_bytes);
		_send_wsabuf[0].len = num_bytes;
		ZeroMemory(&_send_over, sizeof(_send_over));
		_send_over.hEvent = reinterpret_cast<HANDLE>(_id);
		DWORD size_sent;
		WSASend(_c_socket, _send_wsabuf, 1, &size_sent, 0, &_send_over, g_send_callback);
	}

	void send_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED p_over, DWORD flag)
	{
		do_recv();
	}
};

std::unordered_map<long long, SESSION>g_users;


void CALLBACK g_send_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED p_over, DWORD flag) 
{

	auto my_id = reinterpret_cast <long long>( p_over->hEvent);
	g_users[my_id].send_callback(err, num_bytes, p_over, flag);

}

void CALLBACK g_recv_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED p_over, DWORD flag) 
{
	
	auto my_id = reinterpret_cast <long long>(p_over->hEvent);
	g_users[my_id].recv_callback(err, num_bytes, p_over, flag);

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

	long long client_id = 0;
	while (true) {
		auto c_socket = WSAAccept(s_socket, reinterpret_cast<sockaddr*>(&addr), &addr_size, NULL, NULL);
		HANDLE c_handle = reinterpret_cast<HANDLE>(client_id);
		g_users.try_emplace(client_id, client_id, c_socket);

		client_id++;
	}

	closesocket(s_socket);
	WSACleanup();
}


