//
// Created by CHBADMIN on 12/1/2019.
//

#ifndef TEST_GAME_PLAYER_H
#define TEST_GAME_PLAYER_H

#include "Object.h"
enum state{rising, falling, neither};

class Player : public Object {
private:
    int yHeight;
    state jumpState;
public:

    Player(int height, int width, int distance, color objCol, int yHeight);
    void jumpListener();
    void setJumpState(state jumpState);
    void draw() override;
    Point getTopLeft() override;
    Point getBottomRight() override;

};


#endif //TEST_GAME_PLAYER_H
