#include "graphics.h"
#include "Obstacle.h"
#include "Player.h"
#include "Rectangle.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// GLOBAL VARIABLES
int highscore;      // overall highscore from past games
int currentScore = 0;   // current score user has in the game
int counter = 0;

GLdouble width, height;
int wd;
bool playerHit = false;
enum screenState {pending, help, running, gameover};
screenState screen = pending;

enum timeOfDay {day, night, holiday};
timeOfDay background = day;

//...............................
int menuKeyTracker = 0;
bool xmas = false; // only activated if holiday map chosen

double sun_HighX = 600; double sun_LowX = 630; double sun_LowY = 120; double sun_HighY = 150;
double moon_HighX = 500; double moon_LowX = 520; double moon_LowY = 90; double moon_HighY = 110;

double star1_HighX = 50; double star1_LowX = 52; double star1_LowY = 20; double star1_HighY = 22;
double star2_HighX = 130; double star2_LowX = 132; double star2_LowY = 190; double star2_HighY = 192;
double star3_HighX = 220; double star3_LowX = 222; double star3_LowY = 120; double star3_HighY = 122;
double star4_HighX = 260; double star4_LowX = 262; double star4_LowY = 220; double star4_HighY = 222;
double star5_HighX = 350; double star5_LowX = 352; double star5_LowY = 50; double star5_HighY = 52;
double star6_HighX = 490; double star6_LowX = 492; double star6_LowY = 80; double star6_HighY = 82;
double star7_HighX = 520; double star7_LowX = 522; double star7_LowY = 160; double star7_HighY = 162;
double star8_HighX = 580; double star8_LowX = 582; double star8_LowY = 60; double star8_HighY = 62;
double star9_HighX = 700; double star9_LowX = 702; double star9_LowY = 120; double star9_HighY = 122;

double cloud1_HighX = 700; double cloud1_LowX = 540; double cloud1_LowY = 120; double cloud1_HighY = 150;
double cloud2_HighX = 230; double cloud2_LowX = 140; double cloud2_LowY = 80; double cloud2_HighY = 120;
double cloud3_HighX = 430; double cloud3_LowX = 120; double cloud3_LowY = 140; double cloud3_HighY = 145;
double cloud4_HighX = 100; double cloud4_LowX = 10; double cloud4_LowY = 130; double cloud4_HighY = 160;
double cloud5_HighX = 760; double cloud5_LowX = 440; double cloud5_LowY = 30; double cloud5_HighY = 125;
double cloud6_HighX = 500; double cloud6_LowX = 290; double cloud6_LowY = 10; double cloud6_HighY = 150;
double cloud7_HighX = 330; double cloud7_LowX = 200; double cloud7_LowY = 70; double cloud7_HighY = 135;
double cloud8_HighX = 500; double cloud8_LowX = 290; double cloud8_LowY = 110; double cloud8_HighY = 140;
double cloud9_HighX = 330; double cloud9_LowX = 200; double cloud9_LowY = 70; double cloud9_HighY = 130;

// peak values for mountain
double mountain1_TopX = 20; double mountain1_TopY = 300;
double mountain2_TopX = 80; double mountain2_TopY = 280;
double mountain3_TopX = 190; double mountain3_TopY = 320;
double mountain4_TopX = 245; double mountain4_TopY = 250;
double mountain5_TopX = 440; double mountain5_TopY = 290;
double mountain6_TopX = 650; double mountain6_TopY = 240;


//night time
void drawBackground_night(){

    // animates clouds and resets
    cloud1_HighX -= 0.6; cloud1_LowX -= 0.6;
    cloud2_HighX -= 1; cloud2_LowX -= 1;
    cloud3_HighX -= 0.3; cloud3_LowX -= 0.3;
    cloud4_HighX -= 0.05; cloud4_LowX -= 0.05;

    //resets clouds when left boundries reached, replaces outside screen on right
    if (cloud1_HighX <= -100) {
        cloud1_HighX = 750 + (cloud1_HighX - cloud1_LowX);;
        cloud1_LowX = 750;
    } else if (cloud2_HighX <= -100) {
        cloud2_HighX = 750 + (cloud2_HighX - cloud2_LowX);;
        cloud2_LowX = 750;
    } else if (cloud3_HighX <= -100) {
        cloud3_HighX = 750 + (cloud3_HighX - cloud3_LowX);;
        cloud3_LowX = 750;
    } else if (cloud4_HighX <= -100) {
        cloud4_HighX = 750 + (cloud4_HighX - cloud4_LowX);;
        cloud4_LowX = 750;
    }

    glBegin(GL_QUADS);

    // night sky
    glColor3f(0.0, 0.0, 0.2);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);

    // mountain
    glColor3f(0.0, 0.0, 0.1);
    glVertex2i(mountain1_TopX, mountain1_TopY); // top
    glVertex2i(mountain1_TopX + 200, mountain1_TopY + 100); //right
    glVertex2i(mountain1_TopX, mountain1_TopY + 500); //bottom
    glVertex2i(mountain1_TopX - 200 , mountain1_TopY + 100); //  left

    glVertex2i(mountain2_TopX, mountain2_TopY); // top
    glVertex2i(mountain2_TopX + 200, mountain2_TopY + 100); //right
    glVertex2i(mountain2_TopX, mountain2_TopY + 500); //bottom
    glVertex2i(mountain2_TopX - 200 , mountain2_TopY + 100); //  left

    glVertex2i(mountain3_TopX, mountain3_TopY); // top
    glVertex2i(mountain3_TopX + 200, mountain3_TopY + 100); //right
    glVertex2i(mountain3_TopX, mountain3_TopY + 500); //bottom
    glVertex2i(mountain3_TopX - 200 , mountain3_TopY + 100); //  left

    glVertex2i(mountain4_TopX, mountain4_TopY); // top
    glVertex2i(mountain4_TopX + 200, mountain4_TopY + 100); //right
    glVertex2i(mountain4_TopX, mountain4_TopY + 500); //bottom
    glVertex2i(mountain4_TopX - 200 , mountain4_TopY + 100); //  left

    glVertex2i(mountain5_TopX, mountain5_TopY); // top
    glVertex2i(mountain5_TopX + 200, mountain5_TopY + 100); //right
    glVertex2i(mountain5_TopX, mountain5_TopY + 500); //bottom
    glVertex2i(mountain5_TopX - 200 , mountain5_TopY + 100); //  left

    glVertex2i(mountain6_TopX, mountain6_TopY); // top
    glVertex2i(mountain6_TopX + 200, mountain6_TopY + 100); //right
    glVertex2i(mountain6_TopX, mountain6_TopY + 500); //bottom
    glVertex2i(mountain6_TopX - 200 , mountain6_TopY + 100); //  left

    // grey floor
    glColor3f(0.5, 0.5, 0.5);
    glVertex2i(0, 400);
    glVertex2i(750, 400);
    glVertex2i(750, 415);
    glVertex2i(0, 415);

    // dark green grass
    glColor3f(0.0, 0.2, 0.1);
    glVertex2i(0, 415);
    glVertex2i(750, 415);
    glVertex2i(750, 500);
    glVertex2i(0, 500);

    // moon
    glColor3f(0.9, 0.8, 0.6);
    glVertex2i(moon_LowX + (rand() % 2), moon_LowY + (rand() % 2));
    glVertex2i(moon_HighX + (rand() % 2), moon_LowY + (rand() % 2));
    glVertex2i(moon_HighX + (rand() % 2), moon_HighY + (rand() % 2));
    glVertex2i(moon_LowX + (rand() % 2), moon_HighY + (rand() % 2));

    // stars
    glColor3f(1, 1, 1);
    glVertex2i(star1_LowX + rand() % 2, star1_LowY + rand() % 2);
    glVertex2i(star1_HighX + rand() % 2, star1_LowY + rand() % 2);
    glVertex2i(star1_HighX + rand() % 2, star1_HighY + rand() % 2);
    glVertex2i(star1_LowX + rand() % 2, star1_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star2_LowX + rand() % 2, star2_LowY + rand() % 2);
    glVertex2i(star2_HighX + rand() % 2, star2_LowY + rand() % 2);
    glVertex2i(star2_HighX + rand() % 2, star2_HighY + rand() % 2);
    glVertex2i(star2_LowX + rand() % 2, star2_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star3_LowX + rand() % 2, star3_LowY + rand() % 2);
    glVertex2i(star3_HighX + rand() % 2, star3_LowY + rand() % 2);
    glVertex2i(star3_HighX + rand() % 2, star3_HighY + rand() % 2);
    glVertex2i(star3_LowX + rand() % 2, star3_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star4_LowX + rand() % 2, star4_LowY + rand() % 2);
    glVertex2i(star4_HighX + rand() % 2, star4_LowY + rand() % 2);
    glVertex2i(star4_HighX + rand() % 2, star4_HighY + rand() % 2);
    glVertex2i(star4_LowX + rand() % 2, star4_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star5_LowX + rand() % 2, star5_LowY + rand() % 2);
    glVertex2i(star5_HighX + rand() % 2, star5_LowY + rand() % 2);
    glVertex2i(star5_HighX + rand() % 2, star5_HighY + rand() % 2);
    glVertex2i(star5_LowX + rand() % 2, star5_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star6_LowX + rand() % 2, star6_LowY + rand() % 2);
    glVertex2i(star6_HighX + rand() % 2, star6_LowY + rand() % 2);
    glVertex2i(star6_HighX + rand() % 2, star6_HighY + rand() % 2);
    glVertex2i(star6_LowX + rand() % 2, star6_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star7_LowX + rand() % 2, star7_LowY + rand() % 2);
    glVertex2i(star7_HighX + rand() % 2, star7_LowY + rand() % 2);
    glVertex2i(star7_HighX + rand() % 2, star7_HighY + rand() % 2);
    glVertex2i(star7_LowX + rand() % 2, star7_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star8_LowX + rand() % 2, star8_LowY + rand() % 2);
    glVertex2i(star8_HighX + rand() % 2, star8_LowY + rand() % 2);
    glVertex2i(star8_HighX + rand() % 2, star8_HighY + rand() % 2);
    glVertex2i(star8_LowX + rand() % 2, star8_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star9_LowX + rand() % 2, star9_LowY + rand() % 2);
    glVertex2i(star9_HighX + rand() % 2, star9_LowY + rand() % 2);
    glVertex2i(star9_HighX + rand() % 2, star9_HighY + rand() % 2);
    glVertex2i(star9_LowX + rand() % 2, star9_HighY + rand() % 2);

    // Cloud groups 1
    glColor3f(0.7, 0.7, 0.8);
    glVertex2i(cloud1_LowX, cloud1_LowY); // top left
    glVertex2i(cloud1_HighX, cloud1_LowY); //top right
    glVertex2i(cloud1_HighX, cloud1_HighY); //bottom right
    glVertex2i(cloud1_LowX, cloud1_HighY); // bottom left

    glVertex2i(cloud1_LowX-30, cloud1_LowY+10); // top left
    glVertex2i(cloud1_HighX-30, cloud1_LowY+10); //top right
    glVertex2i(cloud1_HighX-30, cloud1_HighY+10); //bottom right
    glVertex2i(cloud1_LowX-30, cloud1_HighY+10); // bottom left

    // Cloud groups 2
    glVertex2i(cloud2_LowX, cloud2_LowY); // top left
    glVertex2i(cloud2_HighX, cloud2_LowY); //top right
    glVertex2i(cloud2_HighX, cloud2_HighY); //bottom right
    glVertex2i(cloud2_LowX, cloud2_HighY); // bottom left

    glVertex2i(cloud2_LowX-40, cloud2_LowY+10); // top left
    glVertex2i(cloud2_HighX-40, cloud2_LowY+10); //top right
    glVertex2i(cloud2_HighX-40, cloud2_HighY+10); //bottom right
    glVertex2i(cloud2_LowX-40, cloud2_HighY+10); // bottom left

    // Cloud groups 3

    glVertex2i(cloud3_LowX, cloud3_LowY); // top left
    glVertex2i(cloud3_HighX, cloud3_LowY); //top right
    glVertex2i(cloud3_HighX, cloud3_HighY); //bottom right
    glVertex2i(cloud3_LowX, cloud3_HighY); // bottom left

    glVertex2i(cloud3_LowX-60, cloud3_LowY+20); // top left
    glVertex2i(cloud3_HighX-60, cloud3_LowY+20); //top right
    glVertex2i(cloud3_HighX-60, cloud3_HighY+20); //bottom right
    glVertex2i(cloud3_LowX-60, cloud3_HighY+20); // bottom left

    glVertex2i(cloud3_LowX+30, cloud3_LowY+10); // top left
    glVertex2i(cloud3_HighX+30, cloud3_LowY+10); //top right
    glVertex2i(cloud3_HighX+30, cloud3_HighY+10); //bottom right
    glVertex2i(cloud3_LowX+30, cloud3_HighY+10); // bottom left

    // Cloud groups 4
    glVertex2i(cloud4_LowX, cloud4_LowY); // top left
    glVertex2i(cloud4_HighX, cloud4_LowY); //top right
    glVertex2i(cloud4_HighX, cloud4_HighY); //bottom right
    glVertex2i(cloud4_LowX, cloud4_HighY); // bottom left

    glVertex2i(cloud4_LowX+20, cloud4_LowY-10); // top left
    glVertex2i(cloud4_HighX+20, cloud4_LowY-10); //top right
    glVertex2i(cloud4_HighX+20, cloud4_HighY-10); //bottom right
    glVertex2i(cloud4_LowX+20, cloud4_HighY-10); // bottom left

}

//day time
void drawBackground_day(){

    // animates clouds and resets
    cloud1_HighX -= 0.6; cloud1_LowX -= 0.6;
    cloud2_HighX -= 1; cloud2_LowX -= 1;
    cloud3_HighX -= 0.3; cloud3_LowX -= 0.3;
    cloud4_HighX -= 0.05; cloud4_LowX -= 0.05;

    //resets clouds when left boundries reached, replaces outside screen on right
    if (cloud1_HighX <= -100) {
        cloud1_HighX = 750 + (cloud1_HighX - cloud1_LowX);;
        cloud1_LowX = 750;
    } else if (cloud2_HighX <= -100) {
        cloud2_HighX = 750 + (cloud2_HighX - cloud2_LowX);;
        cloud2_LowX = 750;
    } else if (cloud3_HighX <= -100) {
        cloud3_HighX = 750 + (cloud3_HighX - cloud3_LowX);;
        cloud3_LowX = 750;
    } else if (cloud4_HighX <= -100) {
        cloud4_HighX = 750 + (cloud4_HighX - cloud4_LowX);;
        cloud4_LowX = 750;
    }
    glBegin(GL_QUADS);

    // day sky
    glColor3f(0.1, 0.8, 1);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);

    // mountain
    glColor3f(0.6, 0.7, 0.3);
    glVertex2i(mountain1_TopX, mountain1_TopY); // top
    glVertex2i(mountain1_TopX + 200, mountain1_TopY + 100); //right
    glVertex2i(mountain1_TopX, mountain1_TopY + 500); //bottom
    glVertex2i(mountain1_TopX - 200 , mountain1_TopY + 100); //  left

    glVertex2i(mountain2_TopX, mountain2_TopY); // top
    glVertex2i(mountain2_TopX + 200, mountain2_TopY + 100); //right
    glVertex2i(mountain2_TopX, mountain2_TopY + 500); //bottom
    glVertex2i(mountain2_TopX - 200 , mountain2_TopY + 100); //  left

    glVertex2i(mountain3_TopX, mountain3_TopY); // top
    glVertex2i(mountain3_TopX + 200, mountain3_TopY + 100); //right
    glVertex2i(mountain3_TopX, mountain3_TopY + 500); //bottom
    glVertex2i(mountain3_TopX - 200 , mountain3_TopY + 100); //  left

    glVertex2i(mountain4_TopX, mountain4_TopY); // top
    glVertex2i(mountain4_TopX + 200, mountain4_TopY + 100); //right
    glVertex2i(mountain4_TopX, mountain4_TopY + 500); //bottom
    glVertex2i(mountain4_TopX - 200 , mountain4_TopY + 100); //  left

    glVertex2i(mountain5_TopX, mountain5_TopY); // top
    glVertex2i(mountain5_TopX + 200, mountain5_TopY + 100); //right
    glVertex2i(mountain5_TopX, mountain5_TopY + 500); //bottom
    glVertex2i(mountain5_TopX - 200 , mountain5_TopY + 100); //  left

    glVertex2i(mountain6_TopX, mountain6_TopY); // top
    glVertex2i(mountain6_TopX + 200, mountain6_TopY + 100); //right
    glVertex2i(mountain6_TopX, mountain6_TopY + 500); //bottom
    glVertex2i(mountain6_TopX - 200 , mountain6_TopY + 100); //  left

    // floor
    glColor3f(0.6, 0.6, 0.6);
    glVertex2i(0, 400);
    glVertex2i(750, 400);
    glVertex2i(750, 415);
    glVertex2i(0, 415);

    // grass
    glColor3f(0.0, 0.8, 0.1);
    glVertex2i(0, 415);
    glVertex2i(750, 415);
    glVertex2i(750, 500);
    glVertex2i(0, 500);

    // sun
    glColor3f(0.8, 1, 0.0);
    glVertex2i(sun_LowX + (rand() % 3), sun_LowY + (rand() % 3));
    glVertex2i(sun_HighX + (rand() % 3), sun_LowY + (rand() % 3));
    glVertex2i(sun_HighX + (rand() % 3), sun_HighY + (rand() % 3));
    glVertex2i(sun_LowX + (rand() % 3), sun_HighY + (rand() % 3));

    // Cloud groups 1
    glColor3f(1, 1, 1);
    glVertex2i(cloud1_LowX, cloud1_LowY); // top left
    glVertex2i(cloud1_HighX, cloud1_LowY); //top right
    glVertex2i(cloud1_HighX, cloud1_HighY); //bottom right
    glVertex2i(cloud1_LowX, cloud1_HighY); // bottom left

    glColor3f(1, 1, 1);
    glVertex2i(cloud1_LowX-30, cloud1_LowY+10); // top left
    glVertex2i(cloud1_HighX-30, cloud1_LowY+10); //top right
    glVertex2i(cloud1_HighX-30, cloud1_HighY+10); //bottom right
    glVertex2i(cloud1_LowX-30, cloud1_HighY+10); // bottom left

    // Cloud groups 2
    glColor3f(1, 1, 1);
    glVertex2i(cloud2_LowX, cloud2_LowY); // top left
    glVertex2i(cloud2_HighX, cloud2_LowY); //top right
    glVertex2i(cloud2_HighX, cloud2_HighY); //bottom right
    glVertex2i(cloud2_LowX, cloud2_HighY); // bottom left

    glVertex2i(cloud2_LowX-40, cloud2_LowY+10); // top left
    glVertex2i(cloud2_HighX-40, cloud2_LowY+10); //top right
    glVertex2i(cloud2_HighX-40, cloud2_HighY+10); //bottom right
    glVertex2i(cloud2_LowX-40, cloud2_HighY+10); // bottom left

    // Cloud groups 3
    glColor3f(1, 1, 1);
    glVertex2i(cloud3_LowX, cloud3_LowY); // top left
    glVertex2i(cloud3_HighX, cloud3_LowY); //top right
    glVertex2i(cloud3_HighX, cloud3_HighY); //bottom right
    glVertex2i(cloud3_LowX, cloud3_HighY); // bottom left

    glVertex2i(cloud3_LowX-60, cloud3_LowY+20); // top left
    glVertex2i(cloud3_HighX-60, cloud3_LowY+20); //top right
    glVertex2i(cloud3_HighX-60, cloud3_HighY+20); //bottom right
    glVertex2i(cloud3_LowX-60, cloud3_HighY+20); // bottom left

    glVertex2i(cloud3_LowX+30, cloud3_LowY+10); // top left
    glVertex2i(cloud3_HighX+30, cloud3_LowY+10); //top right
    glVertex2i(cloud3_HighX+30, cloud3_HighY+10); //bottom right
    glVertex2i(cloud3_LowX+30, cloud3_HighY+10); // bottom left

    // Cloud groups 4
    glColor3f(1, 1, 1);
    glVertex2i(cloud4_LowX, cloud4_LowY); // top left
    glVertex2i(cloud4_HighX, cloud4_LowY); //top right
    glVertex2i(cloud4_HighX, cloud4_HighY); //bottom right
    glVertex2i(cloud4_LowX, cloud4_HighY); // bottom left

    glColor3f(1, 1, 1);
    glVertex2i(cloud4_LowX+20, cloud4_LowY-10); // top left
    glVertex2i(cloud4_HighX+20, cloud4_LowY-10); //top right
    glVertex2i(cloud4_HighX+20, cloud4_HighY-10); //bottom right
    glVertex2i(cloud4_LowX+20, cloud4_HighY-10); // bottom left
}

//holiday time
void drawBackground_holiday(){

    // animates clouds and resets
    cloud1_HighX -= 0.4; cloud1_LowX -= 0.4;
    cloud2_HighX -= 0.06; cloud2_LowX -= 0.06;
    cloud3_HighX -= 0.3; cloud3_LowX -= 0.3;
    cloud4_HighX -= 0.05; cloud4_LowX -= 0.05;
    cloud5_HighX -= 0.1; cloud5_LowX -= 0.1;
    cloud6_HighX -= 0.5; cloud6_LowX -= 0.5;
    cloud7_HighX -= 0.3; cloud7_LowX -= 0.3;
    cloud8_HighX -= 0.1; cloud8_LowX -= 0.1;
    cloud9_HighX -= 0.2; cloud9_LowX -= 0.2;

    //resets clouds when left boundries reached, replaces outside screen on right
    if (cloud1_HighX <= -100) {
        cloud1_HighX = 750 + (cloud1_HighX - cloud1_LowX);;
        cloud1_LowX = 750;
    } else if (cloud2_HighX <= -100) {
        cloud2_HighX = 750 + (cloud2_HighX - cloud2_LowX);;
        cloud2_LowX = 750;
    } else if (cloud3_HighX <= -100) {
        cloud3_HighX = 750 + (cloud3_HighX - cloud3_LowX);;
        cloud3_LowX = 750;
    } else if (cloud4_HighX <= -100) {
        cloud4_HighX = 750 + (cloud4_HighX - cloud4_LowX);;
        cloud4_LowX = 750;
    }

    glBegin(GL_QUADS);

    // night sky
    glColor3f(0.0, 0.0, 0.2);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);

    // mountain
    glColor3f(0.0, 0.0, 0.1);
    glVertex2i(mountain1_TopX, mountain1_TopY); // top
    glVertex2i(mountain1_TopX + 200, mountain1_TopY + 100); //right
    glVertex2i(mountain1_TopX, mountain1_TopY + 500); //bottom
    glVertex2i(mountain1_TopX - 200 , mountain1_TopY + 100); //  left

    glVertex2i(mountain2_TopX, mountain2_TopY); // top
    glVertex2i(mountain2_TopX + 200, mountain2_TopY + 100); //right
    glVertex2i(mountain2_TopX, mountain2_TopY + 500); //bottom
    glVertex2i(mountain2_TopX - 200 , mountain2_TopY + 100); //  left

    glVertex2i(mountain3_TopX, mountain3_TopY); // top
    glVertex2i(mountain3_TopX + 200, mountain3_TopY + 100); //right
    glVertex2i(mountain3_TopX, mountain3_TopY + 500); //bottom
    glVertex2i(mountain3_TopX - 200 , mountain3_TopY + 100); //  left

    glVertex2i(mountain4_TopX, mountain4_TopY); // top
    glVertex2i(mountain4_TopX + 200, mountain4_TopY + 100); //right
    glVertex2i(mountain4_TopX, mountain4_TopY + 500); //bottom
    glVertex2i(mountain4_TopX - 200 , mountain4_TopY + 100); //  left

    glVertex2i(mountain5_TopX, mountain5_TopY); // top
    glVertex2i(mountain5_TopX + 200, mountain5_TopY + 100); //right
    glVertex2i(mountain5_TopX, mountain5_TopY + 500); //bottom
    glVertex2i(mountain5_TopX - 200 , mountain5_TopY + 100); //  left

    glVertex2i(mountain6_TopX, mountain6_TopY); // top
    glVertex2i(mountain6_TopX + 200, mountain6_TopY + 100); //right
    glVertex2i(mountain6_TopX, mountain6_TopY + 500); //bottom
    glVertex2i(mountain6_TopX - 200 , mountain6_TopY + 100); //  left

    // grey floor
    glColor3f(0.5, 0.5, 0.5);
    glVertex2i(0, 400);
    glVertex2i(750, 400);
    glVertex2i(750, 415);
    glVertex2i(0, 415);

    // dark green grass
    glColor3f(0.0, 0.2, 0.1);
    glVertex2i(0, 415);
    glVertex2i(750, 415);
    glVertex2i(750, 500);
    glVertex2i(0, 500);

    // moon
    glColor3f(0.9, 0.8, 0.6);
    glVertex2i(moon_LowX + (rand() % 2), moon_LowY + (rand() % 2));
    glVertex2i(moon_HighX + (rand() % 2), moon_LowY + (rand() % 2));
    glVertex2i(moon_HighX + (rand() % 2), moon_HighY + (rand() % 2));
    glVertex2i(moon_LowX + (rand() % 2), moon_HighY + (rand() % 2));

    // stars
    glColor3f(1, 1, 1);
    glVertex2i(star1_LowX + rand() % 2, star1_LowY + rand() % 2);
    glVertex2i(star1_HighX + rand() % 2, star1_LowY + rand() % 2);
    glVertex2i(star1_HighX + rand() % 2, star1_HighY + rand() % 2);
    glVertex2i(star1_LowX + rand() % 2, star1_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star2_LowX + rand() % 2, star2_LowY + rand() % 2);
    glVertex2i(star2_HighX + rand() % 2, star2_LowY + rand() % 2);
    glVertex2i(star2_HighX + rand() % 2, star2_HighY + rand() % 2);
    glVertex2i(star2_LowX + rand() % 2, star2_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star3_LowX + rand() % 2, star3_LowY + rand() % 2);
    glVertex2i(star3_HighX + rand() % 2, star3_LowY + rand() % 2);
    glVertex2i(star3_HighX + rand() % 2, star3_HighY + rand() % 2);
    glVertex2i(star3_LowX + rand() % 2, star3_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star4_LowX + rand() % 2, star4_LowY + rand() % 2);
    glVertex2i(star4_HighX + rand() % 2, star4_LowY + rand() % 2);
    glVertex2i(star4_HighX + rand() % 2, star4_HighY + rand() % 2);
    glVertex2i(star4_LowX + rand() % 2, star4_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star5_LowX + rand() % 2, star5_LowY + rand() % 2);
    glVertex2i(star5_HighX + rand() % 2, star5_LowY + rand() % 2);
    glVertex2i(star5_HighX + rand() % 2, star5_HighY + rand() % 2);
    glVertex2i(star5_LowX + rand() % 2, star5_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star6_LowX + rand() % 2, star6_LowY + rand() % 2);
    glVertex2i(star6_HighX + rand() % 2, star6_LowY + rand() % 2);
    glVertex2i(star6_HighX + rand() % 2, star6_HighY + rand() % 2);
    glVertex2i(star6_LowX + rand() % 2, star6_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star7_LowX + rand() % 2, star7_LowY + rand() % 2);
    glVertex2i(star7_HighX + rand() % 2, star7_LowY + rand() % 2);
    glVertex2i(star7_HighX + rand() % 2, star7_HighY + rand() % 2);
    glVertex2i(star7_LowX + rand() % 2, star7_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star8_LowX + rand() % 2, star8_LowY + rand() % 2);
    glVertex2i(star8_HighX + rand() % 2, star8_LowY + rand() % 2);
    glVertex2i(star8_HighX + rand() % 2, star8_HighY + rand() % 2);
    glVertex2i(star8_LowX + rand() % 2, star8_HighY + rand() % 2);

    glColor3f(1, 1, 1);
    glVertex2i(star9_LowX + rand() % 2, star9_LowY + rand() % 2);
    glVertex2i(star9_HighX + rand() % 2, star9_LowY + rand() % 2);
    glVertex2i(star9_HighX + rand() % 2, star9_HighY + rand() % 2);
    glVertex2i(star9_LowX + rand() % 2, star9_HighY + rand() % 2);

    // Cloud groups 1
    glColor3f(0.7, 0.7, 0.8);
    glVertex2i(cloud1_LowX, cloud1_LowY); // top left
    glVertex2i(cloud1_HighX, cloud1_LowY); //top right
    glVertex2i(cloud1_HighX, cloud1_HighY); //bottom right
    glVertex2i(cloud1_LowX, cloud1_HighY); // bottom left

    glVertex2i(cloud1_LowX-30, cloud1_LowY+10); // top left
    glVertex2i(cloud1_HighX-30, cloud1_LowY+10); //top right
    glVertex2i(cloud1_HighX-30, cloud1_HighY+10); //bottom right
    glVertex2i(cloud1_LowX-30, cloud1_HighY+10); // bottom left

    // Cloud groups 2
    glVertex2i(cloud2_LowX, cloud2_LowY); // top left
    glVertex2i(cloud2_HighX, cloud2_LowY); //top right
    glVertex2i(cloud2_HighX, cloud2_HighY); //bottom right
    glVertex2i(cloud2_LowX, cloud2_HighY); // bottom left

    glVertex2i(cloud2_LowX-40, cloud2_LowY+10); // top left
    glVertex2i(cloud2_HighX-40, cloud2_LowY+10); //top right
    glVertex2i(cloud2_HighX-40, cloud2_HighY+10); //bottom right
    glVertex2i(cloud2_LowX-40, cloud2_HighY+10); // bottom left

    // Cloud groups 3

    glVertex2i(cloud3_LowX, cloud3_LowY); // top left
    glVertex2i(cloud3_HighX, cloud3_LowY); //top right
    glVertex2i(cloud3_HighX, cloud3_HighY); //bottom right
    glVertex2i(cloud3_LowX, cloud3_HighY); // bottom left

    glVertex2i(cloud3_LowX-60, cloud3_LowY+20); // top left
    glVertex2i(cloud3_HighX-60, cloud3_LowY+20); //top right
    glVertex2i(cloud3_HighX-60, cloud3_HighY+20); //bottom right
    glVertex2i(cloud3_LowX-60, cloud3_HighY+20); // bottom left

    glVertex2i(cloud3_LowX+30, cloud3_LowY+10); // top left
    glVertex2i(cloud3_HighX+30, cloud3_LowY+10); //top right
    glVertex2i(cloud3_HighX+30, cloud3_HighY+10); //bottom right
    glVertex2i(cloud3_LowX+30, cloud3_HighY+10); // bottom left

    // Cloud groups 4
    glVertex2i(cloud4_LowX, cloud4_LowY); // top left
    glVertex2i(cloud4_HighX, cloud4_LowY); //top right
    glVertex2i(cloud4_HighX, cloud4_HighY); //bottom right
    glVertex2i(cloud4_LowX, cloud4_HighY); // bottom left

    glVertex2i(cloud4_LowX+20, cloud4_LowY-10); // top left
    glVertex2i(cloud4_HighX+20, cloud4_LowY-10); //top right
    glVertex2i(cloud4_HighX+20, cloud4_HighY-10); //bottom right
    glVertex2i(cloud4_LowX+20, cloud4_HighY-10); // bottom left

    // Cloud groups 5
    glVertex2i(cloud5_LowX, cloud5_LowY); // top left
    glVertex2i(cloud5_HighX, cloud5_LowY); //top right
    glVertex2i(cloud5_HighX, cloud5_HighY); //bottom right
    glVertex2i(cloud5_LowX, cloud5_HighY); // bottom left

    glVertex2i(cloud5_LowX+20, cloud5_LowY-10); // top left
    glVertex2i(cloud5_HighX+20, cloud5_LowY-10); //top right
    glVertex2i(cloud5_HighX+20, cloud5_HighY-10); //bottom right
    glVertex2i(cloud5_LowX+20, cloud5_HighY-10); // bottom left

    // Cloud groups 6
    glVertex2i(cloud6_LowX, cloud6_LowY); // top left
    glVertex2i(cloud6_HighX, cloud6_LowY); //top right
    glVertex2i(cloud6_HighX, cloud6_HighY); //bottom right
    glVertex2i(cloud6_LowX, cloud6_HighY); // bottom left

    glVertex2i(cloud6_LowX+20, cloud6_LowY-10); // top left
    glVertex2i(cloud6_HighX+20, cloud6_LowY-10); //top right
    glVertex2i(cloud6_HighX+20, cloud6_HighY-10); //bottom right
    glVertex2i(cloud6_LowX+20, cloud6_HighY-10); // bottom left

    // Cloud groups 7
    glVertex2i(cloud7_LowX, cloud7_LowY); // top left
    glVertex2i(cloud7_HighX, cloud7_LowY); //top right
    glVertex2i(cloud7_HighX, cloud7_HighY); //bottom right
    glVertex2i(cloud7_LowX, cloud7_HighY); // bottom left

    glVertex2i(cloud7_LowX+20, cloud7_LowY-10); // top left
    glVertex2i(cloud7_HighX+20, cloud7_LowY-10); //top right
    glVertex2i(cloud7_HighX+20, cloud7_HighY-10); //bottom right
    glVertex2i(cloud7_LowX+20, cloud7_HighY-10); // bottom left

    // Cloud groups 8
    glVertex2i(cloud8_LowX, cloud8_LowY); // top left
    glVertex2i(cloud8_HighX, cloud8_LowY); //top right
    glVertex2i(cloud8_HighX, cloud8_HighY); //bottom right
    glVertex2i(cloud8_LowX, cloud8_HighY); // bottom left

    glVertex2i(cloud8_LowX+20, cloud8_LowY-10); // top left
    glVertex2i(cloud8_HighX+20, cloud8_LowY-10); //top right
    glVertex2i(cloud8_HighX+20, cloud8_HighY-10); //bottom right
    glVertex2i(cloud8_LowX+20, cloud8_HighY-10); // bottom left

    // Cloud groups 9
    glVertex2i(cloud9_LowX, cloud9_LowY); // top left
    glVertex2i(cloud9_HighX, cloud9_LowY); //top right
    glVertex2i(cloud9_HighX, cloud9_HighY); //bottom right
    glVertex2i(cloud9_LowX, cloud9_HighY); // bottom left

    glVertex2i(cloud9_LowX+20, cloud9_LowY-10); // top left
    glVertex2i(cloud9_HighX+20, cloud9_LowY-10); //top right
    glVertex2i(cloud9_HighX+20, cloud9_HighY-10); //bottom right
    glVertex2i(cloud9_LowX+20, cloud9_HighY-10); // bottom left

}

//..............................

// create game window
void init() {
    width = 750;
    height = 500;
}

int health = 100;

// wall / obstacle color
//color testColor{1.0, 0.0, 0.1}; // red
color testColor{1, 0, 0.2}; // red

// create walls / obstacles
Obstacle wall1(40, 15, 1600, testColor);
Obstacle wall2(30, 15, 1200, testColor);
Obstacle wall3(35, 20, 1000, testColor);
Obstacle wall4(30, 10, 400, testColor);

Player player(20, 20, 80, color{1.0, 1.0, 1.0}, 400); // test player on ground (yHeight = 400)

vector<Obstacle> walls{wall1, wall2, wall3, wall4};
void updatePlayerItems(){
    double playerDistance = player.getDistance();
    double playerHeight = player.getHeight();
    double playerWidth = player.getWidth();
    double playerYHeight = player.getYHeight();

    if (player.getJumpState() == 1){ //blinking eye from jump
                //eyes 1 -- BLINKING
        glColor3f(0,0,0);
        glVertex2i(playerDistance - (playerWidth / 2) + 5, (playerYHeight - playerHeight)); //top left corner
        glVertex2i(playerDistance + (playerWidth / 2) - 10, (playerYHeight - playerHeight)); // top right
        glVertex2i(playerDistance + (playerWidth / 2) - 10, playerYHeight - 10);
        glVertex2i(playerDistance - (playerWidth / 2) + 5, playerYHeight - 10);

        //eyes 2
        glVertex2i(playerDistance - (playerWidth / 2) + 13, (playerYHeight - playerHeight)); //top left corner
        glVertex2i(playerDistance + (playerWidth / 2) - 2, (playerYHeight - playerHeight)); // top right
        glVertex2i(playerDistance + (playerWidth / 2) - 2, playerYHeight - 10);
        glVertex2i(playerDistance - (playerWidth / 2) + 13, playerYHeight - 10);

        //this blocks initial grounded eye animation
        //eyes 1, regular on ground
        glColor3f(1, 1, 1);
        glVertex2i(playerDistance - (playerWidth / 2) + 5, (playerYHeight - playerHeight) + 5); //top left corner
        glVertex2i(playerDistance + (playerWidth / 2) - 10, (playerYHeight - playerHeight) + 5); // top right
        glVertex2i(playerDistance + (playerWidth / 2) - 10, playerYHeight - 10);
        glVertex2i(playerDistance - (playerWidth / 2) + 5, playerYHeight - 10);

        //eyes 2
        glVertex2i(playerDistance - (playerWidth / 2) + 13, (playerYHeight - playerHeight) + 5); //top left corner
        glVertex2i(playerDistance + (playerWidth / 2) - 2, (playerYHeight - playerHeight) + 5); // top right
        glVertex2i(playerDistance + (playerWidth / 2) - 2, playerYHeight - 10);
        glVertex2i(playerDistance - (playerWidth / 2) + 13, playerYHeight - 10);


        if (xmas){
            //draw hat on player in air
            glColor3f(1, 0, 0.1);
            glVertex2i(playerDistance - (playerWidth / 2) - 13, (playerYHeight - playerHeight) - 11); //top
            glVertex2i(playerDistance + (playerWidth / 2) - 10, (playerYHeight - playerHeight) - 10); // right
            glVertex2i(playerDistance - (playerWidth / 2), (playerYHeight - playerHeight)); //bottom left
            glVertex2i(playerDistance + (playerWidth / 2), (playerYHeight - playerHeight)); //  bottom right

            //draw hat ball
            glColor3f(1, 1, 1);
            glVertex2i(playerDistance - (playerWidth / 2) - 10, (playerYHeight - playerHeight) - 9);
            glVertex2i(playerDistance - (playerWidth / 2) - 15, (playerYHeight - playerHeight) - 9);
            glVertex2i(playerDistance - (playerWidth / 2) - 15, (playerYHeight - playerHeight) - 13);
            glVertex2i(playerDistance - (playerWidth / 2) - 10, (playerYHeight - playerHeight) - 13);
        }

    } else {
        //eyes 1, regular on ground
        glColor3f(0, 0, 0);
        glVertex2i(playerDistance - (playerWidth / 2) + 5, (playerYHeight - playerHeight) + 5); //top left corner
        glVertex2i(playerDistance + (playerWidth / 2) - 10, (playerYHeight - playerHeight) + 5); // top right
        glVertex2i(playerDistance + (playerWidth / 2) - 10, playerYHeight - 10);
        glVertex2i(playerDistance - (playerWidth / 2) + 5, playerYHeight - 10);

        //eyes 2
        glVertex2i(playerDistance - (playerWidth / 2) + 13, (playerYHeight - playerHeight) + 5); //top left corner
        glVertex2i(playerDistance + (playerWidth / 2) - 2, (playerYHeight - playerHeight) + 5); // top right
        glVertex2i(playerDistance + (playerWidth / 2) - 2, playerYHeight - 10);
        glVertex2i(playerDistance - (playerWidth / 2) + 13, playerYHeight - 10);

        if (xmas){
            //draw hat on player on ground
            glColor3f(1, 0, 0.1);
            glVertex2i(playerDistance - (playerWidth / 2) - 13, (playerYHeight - playerHeight) - 16); //top
            glVertex2i(playerDistance + (playerWidth / 2) - 10, (playerYHeight - playerHeight) - 15); // right
            glVertex2i(playerDistance - (playerWidth / 2), (playerYHeight - playerHeight)); //bottom left
            glVertex2i(playerDistance + (playerWidth / 2), (playerYHeight - playerHeight)); //  bottom right

            //draw hat ball
            glColor3f(1, 1, 1);
            glVertex2i(playerDistance - (playerWidth / 2) - 10, (playerYHeight - playerHeight) - 14);
            glVertex2i(playerDistance - (playerWidth / 2) - 15, (playerYHeight - playerHeight) - 14);
            glVertex2i(playerDistance - (playerWidth / 2) - 15, (playerYHeight - playerHeight) - 18);
            glVertex2i(playerDistance - (playerWidth / 2) - 10, (playerYHeight - playerHeight) - 18);
        }

    }
}
//vector<unique_ptr<class Rectangle>> gameObjects{make_unique<Obstacle>(40, 15, 1150, testColor),
//        make_unique<Obstacle>(30, 15, 1000, testColor), make_unique<Obstacle>(35, 20, 800, testColor),
//                make_unique<Obstacle>(30, 10, 500, testColor),
//                        make_unique<Player>(20, 20, 80, color{1.0, 1.0, 1.0}, 400)};

// initialize OpenGL graphics
void initGL() {
    glClearColor(0, 0, 0, 0); // background color - black opaque
}

void display() {
    int xPos = width / 2; // for user messages
    int yPos = height / 2;

    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // clear the color buffer with current clearing color
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (screen == pending) {
        string welcome = "Welcome to Block Bounce!"; // welcome message for user
        glRasterPos2i(xPos - (4 * welcome.length()), yPos - 50);
        for (const char &letter : welcome) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message = "Use arrow keys to select the time of day. Press enter to continue."; // welcome message for user
        glRasterPos2i(xPos - (4 * message.length()), yPos + 7);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string userHelp = "Press 'h' for help"; // welcome message for user
        glRasterPos2i(xPos - (4 * userHelp.length()), yPos + 80);
        for (const char &letter : userHelp) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        if (background == day) {
            string daySelect = "[day]                night                holiday"; // day background selected
            glRasterPos2i(xPos - (4 * daySelect.length()), yPos + 40);
            health = 100; // resets health
            currentScore = 0;
            for (const char &letter : daySelect) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
        } else if (background == holiday){
            string daySelect = "day                night                [holiday]"; // holiday background selected
            glRasterPos2i(xPos - (4 * daySelect.length()), yPos + 40);
            health = 100; // resets health
            currentScore = 0;
            for (const char &letter : daySelect) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
        } else {
            string daySelect = "day                [night]                holiday"; // night background selected
            glRasterPos2i(xPos - (4 * daySelect.length()), yPos + 40);
            health = 100; // resets health
            currentScore = 0;
            for (const char &letter : daySelect) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
        }
    } else if (screen == running) {
        counter += 1;
        //////////////////// COLLISION DETECTION BETWEEN PLAYER AND OBSTACLES ////////////////
        // check for collisions with each generated wall
        for (Obstacle &wall : walls) {
            if (collision(player, wall)) {
                playerHit = true;
                player.setColor(playerHit);
                health -= 2; // decrease health
            }
            else if (counter > 10){ // colors player when hit wall
                counter = 0;
                playerHit = false;
                player.setColor(playerHit);
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////


        if (background == day) {
            xmas = false;
            drawBackground_day(); // drap map before content
        } else if(background == night) {
            xmas = false;
            drawBackground_night(); // drap map before content
        } else if(background == holiday) {
            xmas = true;
            drawBackground_holiday(); // drap map before content
        }

        drawHealthbar(health); // draw health bar

        updatePlayerItems();



        string userScoreMessage = to_string(currentScore);
        glRasterPos2i(xPos - (4 * userScoreMessage.length()), yPos + 7);
        for (const char &letter : userScoreMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        //////////////////// DRAW EACH WALL / OBSTACLE TO SCREEN //////////////////////////

        for (Obstacle &wall : walls) {
            wall.draw();
        }
        ///////////////////////////////////////////////////////////////////////////////////
        player.draw(); // draw player to screen
        //updatePlayerItems();


        ///////////////////////////

    }
    else if (screen == gameover){
        string endMessage = "Game Over, You Ran Out of Health!"; // welcome message for user
        glRasterPos2i(xPos - (4 * endMessage.length()), yPos - 50);
        for (const char &letter : endMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string yourScoreMessage = "Your score was: " + to_string(currentScore); // currentScore message
        glRasterPos2i(xPos - (4 * yourScoreMessage.length()), yPos + 10);
        for (const char &letter : yourScoreMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string bestScoreMessage = "The high score is: " + to_string(highscore); // high score message
        glRasterPos2i(xPos - (4 * bestScoreMessage.length()), yPos + 30);
        for (const char &letter : bestScoreMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string returnMessage = "Press [esc] to return to the main menu. "; // return message
        glRasterPos2i(xPos - (4 * returnMessage.length()), yPos + 60);
        for (const char &letter : returnMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    else {

        string helpMessage1 = "Press the [space bar] to jump.";
        glRasterPos2i(xPos - (4 * helpMessage1.length()), yPos - 13);
        for (const char &letter : helpMessage1) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string helpMessage2 = "Avoid obstacles to maintain your health.";
        glRasterPos2i(xPos - (4 * helpMessage2.length()), yPos + 17);
        for (const char &letter : helpMessage2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string helpMessage3 = "Use the arrow keys to change the time of day.";
        glRasterPos2i(xPos - (4 * helpMessage3.length()), yPos + 47);
        for (const char &letter : helpMessage3) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string helpMessage4 = "(Press [esc] to go back)";
        glRasterPos2i(xPos - (4 * helpMessage4.length()), yPos + 230 );
        for (const char &letter : helpMessage4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

    }

    glEnd();
    glFlush();  // render now
}


void drawHealthbar(int health){
    int difference;
    if (health > 0){
        difference = 2 * (100 - health);

        // increase their current score
        currentScore += 1;
        // compare scores
        if (currentScore > highscore){
            highscore = currentScore;
        }

    } else {
        difference = 200;
        // Game is over -> write updated highscore to file
        ofstream fileOut;
        fileOut.open("highscore.txt");
        if (fileOut){
            fileOut << highscore;
        }
        fileOut.close();

        // gameover
        screen = gameover;
    }

    // red back health bar back splash
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(275, 450);
    glVertex2i(475, 450);
    glVertex2i(475, 470);
    glVertex2i(275, 470);

    // green health bar
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(275, 450);
    glVertex2i(475 - difference, 450); // alter
    glVertex2i(475 - difference, 470); // alter
    glVertex2i(275, 470);

}

bool collision(Player player, Obstacle obstacle){
    Point l1 = player.getTopLeft();
    Point r1 = player.getBottomRight();
    Point l2 = obstacle.getTopLeft();
    Point r2 = obstacle.getBottomRight();

    // If one rectangle is on left side of other
    if (l1.x > r2.x || l2.x > r1.x)
        return false;

    // If one rectangle is above other
    if (l1.y > r2.y || l2.y > r1.y)
        return false;

    return true;
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            menuKeyTracker -= 1;
            break;
        case GLUT_KEY_RIGHT:
            menuKeyTracker += 1;
            break;
        case GLUT_KEY_UP:
            break;
    }

    //cycles if user presses left or right
    if (menuKeyTracker < 0)
        menuKeyTracker = 2;
    else if (menuKeyTracker > 2)
        menuKeyTracker = 0;

    // selects background mode depending on keytracker
    if (menuKeyTracker == 0)
        background = day;
    else if (menuKeyTracker == 1)
        background = night;
    else if (menuKeyTracker == 2)
        background = holiday;

    glutPostRedisplay();
}

void kbd(unsigned char key, int x, int y)
{

    if (key == 32 && player.getBottomRight().y == 400) { // 'd' key, can only jump from ground
        player.setJumpState(rising);
    }

    if (key == 13){ // enter key to start game
        screen = running;
    }

    if (key == 'h'){ // display help message
        screen = help;
    }

    if (key == 27){ // esc for going back to main screen
        screen = pending;
    }

    glutPostRedisplay();

}

void cursor(int x, int y) {

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int dummy) {
    if (screen == running) {
        // update all wall positions (move them to the left)
        for (Obstacle &wall : walls) {
            wall.update();
        }

        ////////////////////////////////////////////////////
        player.jumpListener();
    }
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    // Read in old highscore from highscore.txt file
    ifstream infile;
    infile.open("highscore.txt");
    string fileLine;
    if(infile){
        getline(infile, fileLine);
        stringstream oldScore(fileLine);
        oldScore >> highscore;
    }
    infile.close();

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);

    glutInitWindowPosition(800, 400); // position the window's initial top-left corner

    /* create the window and store the handle to it */
    wd = glutCreateWindow("Block Bounce"); // title

    // register callback handler for window re-paint event
    glutDisplayFunc(display);

    // our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}

