#include "chess_server_protocol.h"

void UpdatePlayerPosition(PlayerPosition& playerPos, MovementDirection direction, int stepSize, int windowWidth, int windowHeight) {
    switch (direction) {
    case MOVE_LEFT:
        playerPos.x -= stepSize;
        if (playerPos.x < 0) playerPos.x = 0; // ��� üũ
        break;

    case MOVE_RIGHT:
        playerPos.x += stepSize;
        if (playerPos.x > windowWidth - 121) playerPos.x = windowWidth - 121; // ��� üũ
        break;

    case MOVE_UP:
        playerPos.y -= stepSize;
        if (playerPos.y < 0) playerPos.y = 0; // ��� üũ
        break;

    case MOVE_DOWN:
        playerPos.y += stepSize;
        if (playerPos.y > windowHeight - 128) playerPos.y = windowHeight - 128; // ��� üũ
        break;

    default:
        break;
    }
}
