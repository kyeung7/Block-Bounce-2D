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

int Player::getHeight(){
    return height;
}

int Player::getWidth(){
    return width;
}

int Player::getDistance(){
    return distance;
}

int Player::getYHeight(){
    return yHeight;
}

int Player::getJumpState(){
    if (jumpState == rising) {
        return 1; // jumping
    } else
        return 0; // still on ground or falling
}

void Player::draw(){
    glColor3f(objColor.r, objColor.g, objColor.b);
    glVertex2i(distance - (width / 2), (yHeight - height));
    glVertex2i(distance + (width / 2), (yHeight - height));
    glVertex2i(distance + (width / 2), yHeight);
    glVertex2i(distance - (width / 2), yHeight);

//    //eyes 1
//    glColor3f(0,0,0);
//    glVertex2i(distance - (width / 2) + 5, (yHeight - height) + 5); //top left corner
//    glVertex2i(distance + (width / 2) - 10, (yHeight - height) + 5); // top right
//    glVertex2i(distance + (width / 2) - 10, yHeight - 10);
//    glVertex2i(distance - (width / 2) + 5, yHeight - 10);
//
//    //eyes 2
//    glVertex2i(distance - (width / 2) + 13, (yHeight - height) + 5); //top left corner
//    glVertex2i(distance + (width / 2) - 2, (yHeight - height) + 5); // top right
//    glVertex2i(distance + (width / 2) - 2, yHeight - 10);
//    glVertex2i(distance - (width / 2) + 13, yHeight - 10);
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

//        //eyes 1 -- BLINKING
//        glColor3f(0,0,0);
//        glVertex2i(distance - (width / 2) + 5, (yHeight - height)); //top left corner
//        glVertex2i(distance + (width / 2) - 10, (yHeight - height)); // top right
//        glVertex2i(distance + (width / 2) - 10, yHeight - 10);
//        glVertex2i(distance - (width / 2) + 5, yHeight - 10);
//
//        //eyes 2
//        glVertex2i(distance - (width / 2) + 13, (yHeight - height)); //top left corner
//        glVertex2i(distance + (width / 2) - 2, (yHeight - height)); // top right
//        glVertex2i(distance + (width / 2) - 2, yHeight - 10);
//        glVertex2i(distance - (width / 2) + 13, yHeight - 10);

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


