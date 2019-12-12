//
// Created by CHBADMIN on 12/11/2019.
//

#ifndef FINALPROJECTMAJOR_KY_JD_CB_RECTANGLE_H
#define FINALPROJECTMAJOR_KY_JD_CB_RECTANGLE_H

struct color {
    float r;
    float g;
    float b;
};

struct Point { // corner points used for collision detection
    int x, y;
};

class Rectangle {
protected:
    int height;
    int width;
    int distance;
    color objColor;

public:
    virtual void draw() = 0;
    virtual Point getTopLeft() = 0;
    virtual Point getBottomRight() = 0;
};


#endif //FINALPROJECTMAJOR_KY_JD_CB_RECTANGLE_H
