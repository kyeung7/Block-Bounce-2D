

#include "Player.h"
#include "graphics.h"

Player::Player(int height, int width, int distance, color objCol, int yHeight){
    this->height = height;
    this->width = width;
    this->distance = distance;
    this->objColor = objCol;
    this->yHeight = yHeight;
    this->jumpState = neither;

}

void Player::draw(){
    glColor3f(objColor.r, objColor.g, objColor.b);
    glVertex2i(distance - (width / 2), (yHeight - height));
    glVertex2i(distance + (width / 2), (yHeight - height));
    glVertex2i(distance + (width / 2), yHeight);
    glVertex2i(distance - (width / 2), yHeight);
}

void Player::setColor(bool collision){
    if (collision == true){ // if hit wall
        this->objColor = color{1.0, 0.1, 0.1};
    } else {
        this->objColor = color{1.0, 1.0, 1.0}; // otherwise player goes back to white
    }
}

void Player::jumpListener(){
//    if (jumpState == rising || jumpState == falling){ // if in process of jumping, turn bright purple
//        this->objColor = color{1.0, 0.2, 0.8};
//    } else {
//        this->objColor = color{1.0, 1.0, 1.0}; // otherwise player goes back to white
//    }

    if (jumpState == rising && yHeight > 330){
        this->yHeight -= 8;
        if (yHeight <= 330){
            jumpState = falling;
        }
    }
    if (jumpState == falling && yHeight < 400){
        this->yHeight += 8;
        if (yHeight >= 400){
            yHeight = 400;
            jumpState = neither;
            this->objColor = color{1.0, 1.0, 1.0};
        }
    }
}

void Player::setJumpState(state jumpState){
    this->jumpState = jumpState;
}

Point Player::getTopLeft(){
    int x = this->distance - (width / 2);
    int y = yHeight - this->height;
    return Point{x, y};
}

Point Player::getBottomRight(){
    int x = this->distance + (width / 2);
    int y = yHeight;
    return Point{x, y};
}


