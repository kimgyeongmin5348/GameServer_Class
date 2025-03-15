#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "chess_server_protocol.h"

// ip_address -> 192.168.40.129

#pragma comment(lib, "Ws2_32.lib")

constexpr short SERVER_PORT = 3000;

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "���� ���� ����: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    std::cout << "������ ��Ʈ " << SERVER_PORT << "���� ��� ���Դϴ�.\n";

    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientSize);

    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Ŭ���̾�Ʈ ���� ����: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    PlayerPosition playerPos = { 0, 0 };

    while (true) {
        MovementDirection direction;
        recv(clientSocket, reinterpret_cast<char*>(&direction), sizeof(direction), 0);

        UpdatePlayerPosition(playerPos, direction, StepSize, WindowWidth, WindowHeight);

        send(clientSocket, reinterpret_cast<char*>(&playerPos), sizeof(playerPos), 0);

        std::cout << "ĳ���� ��ġ ������Ʈ�� (" << playerPos.x << ", " << playerPos.y << ").\n";
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
