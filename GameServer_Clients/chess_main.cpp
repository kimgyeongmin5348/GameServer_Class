#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <tchar.h>
#include <atlimage.h>
#include <iostream>
#include <unordered_map>
#include "chess_protocol.h"

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_PORT 3000

int x_pos = 0;
int y_pos = 0;
bool isClick = false;

PlayerPosition playerPos = { 0, 0 };

typedef struct BACKGROUND {
    CImage img[3];
} Background;

typedef struct CHARACTER {
    CImage Standlmg[10];
} Character;

enum direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

SOCKET clientSocket;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Server Project";

Background background;
Character Player[10];

void AllDraw(HDC memdc);
void AnimationDraw(HDC memdc);
void ImgLoad();
void CALLBACK AniType(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // 콘솔 창 생성 =====================================================================
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout); // 표준 출력 연결
    freopen_s(&fp, "CONIN$", "r", stdin);  // 표준 입력 연결
    //==================================================================================

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    std::string serverIP;
    std::cout << "아래에 적힌 ip주소는 제가 실행할때 수월하게 하기 위해 적어둔 것입니다." << '\n';
    std::cout << "접속할 서버의 ip를 입력해 주세요(ex. 노트북 : 192.168.40.129 / 데탑 : 192.168.45.14): ";
    std::cin >> serverIP;

    //serverIP = "192.168.45.156";

    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }


    const wchar_t CLASS_NAME[] = L"SampleWindowClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"GS2_2020182006_김경민",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WindowWidth, WindowHeight,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hWnd == NULL) {
        MessageBox(NULL, L"윈도우를 생성할 수 없습니다.", L"오류", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    closesocket(clientSocket);
    WSACleanup();

    // 콘솔 창 닫기
    fclose(fp);
    FreeConsole();

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc, memdc;

    switch (uMsg) {
    case WM_CREATE:
        hdc = GetDC(hWnd);
        ImgLoad();
        SetTimer(hWnd, 1, 1, (TIMERPROC)AniType); // 캐릭터 타이머
        ReleaseDC(hWnd, hdc);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        memdc = CreateCompatibleDC(hdc);
        AllDraw(memdc);
        BitBlt(hdc, 0, 0, WindowWidth, WindowHeight, memdc, 0, 0, SRCCOPY);
        DeleteDC(memdc);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN: {
        MovementDirection direction;
        switch (wParam) {
        case VK_LEFT:
            direction = MOVE_LEFT;
            break;
        case VK_RIGHT:
            direction = MOVE_RIGHT;
            break;
        case VK_UP:
            direction = MOVE_UP;
            break;
        case VK_DOWN:
            direction = MOVE_DOWN;
            break;
        default:
            return 0;
        }


        send(clientSocket, reinterpret_cast<char*>(&direction), sizeof(direction), 0);

        recv(clientSocket, reinterpret_cast<char*>(&playerPos), sizeof(playerPos), 0);

        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}


void CALLBACK AniType(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
    HDC hdc = GetDC(hWnd), memdc;
    static HBITMAP hBitmap;

    hBitmap = CreateCompatibleBitmap(hdc, WindowWidth, WindowHeight);
    memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, hBitmap);

    AllDraw(memdc);

    BitBlt(hdc, 0, 0, WindowWidth, WindowHeight, memdc, 0, 0, SRCCOPY);

    DeleteObject(hBitmap);
    DeleteDC(memdc);

    ReleaseDC(hWnd, hdc);
}

void ImgLoad() {
    background.img[0].Load(TEXT("chess_board.png"));
    Player[0].Standlmg[0].Load(TEXT("player.png"));
}

void AllDraw(HDC memdc) {
    AnimationDraw(memdc);
}

void AnimationDraw(HDC hdc) {
    float width = background.img[0].GetWidth() - 20;
    float height = background.img[0].GetHeight() - 20;

    float p_width = Player[0].Standlmg[0].GetWidth();
    float p_height = Player[0].Standlmg[0].GetHeight();

    background.img[0].Draw(hdc, 0, 0, WindowWidth, WindowHeight, 20, 20, width, height);

    Player[0].Standlmg[0].Draw(hdc,
        playerPos.x,
        playerPos.y,
        100,
        100,
        0,
        0,
        p_width,
        p_height);
}
