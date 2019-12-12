//
// Created by CHBADMIN on 12/11/2019.
//

#ifndef FINALPROJECTMAJOR_KY_JD_CB_OBSTACLE_H
#define FINALPROJECTMAJOR_KY_JD_CB_OBSTACLE_H

#include <vector>
#include "Rectangle.h"

class Obstacle : public Rectangle {

public:
    Obstacle();
    Obstacle(int height, int width, int distance, color objCol);
    void setColor(color colorToSet);
    int getDistance();
    void setDistance(int dist);
    void update();
    void draw() override;
    Point getTopLeft() override;
    Point getBottomRight()override;

};


#endif //FINALPROJECTMAJOR_KY_JD_CB_OBSTACLE_H
