//
// Created by CHBADMIN on 11/30/2019.
//

#include "Object.h"
#include "graphics.h"

Object::Object(){
    this->height = 20;
    this->width = 20;
    this->distance = 100;
    this->objColor = color{1.0, 1.0, 1.0};
}

Object::Object(int height, int width, int distance, color objCol){
    this->height = height;
    this->width = width;
    this->distance = distance;
    this->objColor = objCol;
}

void Object::draw(){
    glColor3f(objColor.r, objColor.g, objColor.b);
    glVertex2i(distance - (width / 2), (400 - height));
    glVertex2i(distance + (width / 2), (400 - height));
    glVertex2i(distance + (width / 2), 400);
    glVertex2i(distance - (width / 2), 400);
}

void Object::update(){
    if (this->distance < 0){
        this->distance = 800;
    } // send all obstacles / walls back to beginning
    this->distance -= 8;
}

Point Object::getTopLeft(){
    int x = this->distance - (width / 2);
    int y = 400 - this->height; // 400 is top of grey ground
    return Point{x, y};
}

Point Object::getBottomRight(){
    int x = this->distance + (width / 2);
    int y = 400; // 400 is top of grey ground
    return Point{x, y};
}

void Object::setColor(color colorToSet) {
    this->objColor = colorToSet;
}


