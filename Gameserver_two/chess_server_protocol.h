#ifndef PROTOCOL_H
#define PROTOCOL_H

constexpr int WindowWidth = 773;
constexpr int WindowHeight = 780;
constexpr int StepSize = 94;

// 방향(enum) 정의
enum MovementDirection {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN
};

// 플레이어 위치 구조체 정의
typedef struct {
    int x;
    int y;
} PlayerPosition;

// 플레이어 위치 업데이트 함수 선언 (매개변수 수정)
void UpdatePlayerPosition(PlayerPosition& playerPos, MovementDirection direction, int stepSize, int windowWidth, int windowHeight);

#endif