#include "chess_protocol.h"

// 플레이어 위치 업데이트 함수 구현
void UpdatePlayerPosition(PlayerPosition& playerPos, MovementDirection direction, int StepSize, int windowWidth, int windowHeight) {
    switch (direction) {
    case MOVE_LEFT:
        playerPos.x -= StepSize;
        if (playerPos.x < 0) playerPos.x = 0; // 경계 체크
        break;

    case MOVE_RIGHT:
        playerPos.x += StepSize;
        if (playerPos.x > windowWidth - 121) playerPos.x = windowWidth - 121; // 경계 체크
        break;

    case MOVE_UP:
        playerPos.y -= StepSize;
        if (playerPos.y < 0) playerPos.y = 0; // 경계 체크
        break;

    case MOVE_DOWN:
        playerPos.y += StepSize;
        if (playerPos.y > windowHeight - 128) playerPos.y = windowHeight - 128; // 경계 체크
        break;

    default:
        break;
    }
}
