#ifndef TEST_GAME_PLAYER_H
#define TEST_GAME_PLAYER_H

#include "Obstacle.h"

using namespace std;
enum state{rising, falling, neither};

class Player : public Rectangle {
private:
    int yHeight;
    state jumpState;
public:
    Player(int height, int width, int distance, color objCol, int yHeight);

    int getHeight();
    int getWidth();
    int getDistance();
    int getYHeight();
    int getJumpState();
    void setColor(bool collision);
    void jumpListener();
    void setJumpState(state jumpState);
    void draw() override;
    Point getTopLeft() override;
    Point getBottomRight() override;

};


#endif //TEST_GAME_PLAYER_H
