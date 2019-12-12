//
// Created by CHBADMIN on 11/30/2019.
//

#include "Obstacle.h"
#include "graphics.h"

Obstacle::Obstacle(){
    this->height = 20;
    this->width = 20;
    this->distance = 100;
    this->objColor = color{1.0, 1.0, 1.0};
}

Obstacle::Obstacle(int height, int width, int distance, color objCol){
    this->height = height;
    this->width = width;
    this->distance = distance;
    this->objColor = objCol;
}

void Obstacle::draw(){
    glColor3f(objColor.r, objColor.g, objColor.b);
    glVertex2i(distance - (width / 2), (400 - height));
    glVertex2i(distance + (width / 2), (400 - height));
    glVertex2i(distance + (width / 2), 400);
    glVertex2i(distance - (width / 2), 400);
}

void Obstacle::update(){
    if (this->distance < 0){
        this->distance = 800;
    } // send all obstacles / walls back to beginning
    this->distance -= 8;
}

Point Obstacle::getTopLeft(){
    int x = this->distance - (width / 2);
    int y = 400 - this->height; // 400 is top of grey ground
    return Point{x, y};
}

Point Obstacle::getBottomRight(){
    int x = this->distance + (width / 2);
    int y = 400; // 400 is top of grey ground
    return Point{x, y};
}

void Obstacle::setColor(color colorToSet) {
    this->objColor = colorToSet;
}

int Obstacle::getDistance(){
    return this->distance;
}

void Obstacle::setDistance(int dist){
    this->distance = dist;
}


