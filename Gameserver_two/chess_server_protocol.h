#ifndef PROTOCOL_H
#define PROTOCOL_H

constexpr int WindowWidth = 773;
constexpr int WindowHeight = 780;
constexpr int StepSize = 94;

// ����(enum) ����
enum MovementDirection {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN
};

// �÷��̾� ��ġ ����ü ����
typedef struct {
    int x;
    int y;
} PlayerPosition;

// �÷��̾� ��ġ ������Ʈ �Լ� ���� (�Ű����� ����)
void UpdatePlayerPosition(PlayerPosition& playerPos, MovementDirection direction, int stepSize, int windowWidth, int windowHeight);

#endif