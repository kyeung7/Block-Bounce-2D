//
// Created by CHBADMIN on 11/30/2019.
//

#ifndef TEST_GAME_OBJECT_H
#define TEST_GAME_OBJECT_H
#include <vector>

struct color {
    float r;
    float g;
    float b;
};

struct Point { // corner points used for collision detection
    int x, y;
};

class Object {
protected:
    int height;
    int width;
    int distance;
    color objColor;

public:
    Object();
    Object(int height, int width, int distance, color objCol);
    void setColor(color colorToSet);
    int getDistance();
    void setDistance(int dist);
    virtual void draw();
    virtual void update();
    virtual Point getTopLeft();
    virtual Point getBottomRight();


};


#endif //TEST_GAME_OBJECT_H
