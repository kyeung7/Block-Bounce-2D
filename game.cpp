#include "graphics.h"
#include "Obstacle.h"
#include "Player.h"
#include "Rectangle.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include <memory>

using namespace std;

// GLOBAL VARIABLES
GLdouble width, height;
int wd;

enum screenState {pending, help, running};
screenState screen = pending;

enum timeOfDay {day, night};
timeOfDay background = day;

//...............................
int moonPosition = 600;
int sunPosition = 600;

double sun_HighX = 600; double sun_LowX = 630; double sun_LowY = 120; double sun_HighY = 150;

double cloud1_HighX = 700; double cloud1_LowX = 630; double cloud1_LowY = 120; double cloud1_HighY = 150;
double cloud2_HighX = 230; double cloud2_LowX = 160; double cloud2_LowY = 80; double cloud2_HighY = 120;
double cloud3_HighX = 430; double cloud3_LowX = 530; double cloud3_LowY = 140; double cloud3_HighY = 180;
double cloud4_HighX = 100; double cloud4_LowX = 30; double cloud4_LowY = 170; double cloud4_HighY = 200;

//night time
void drawBackground_night(){

    glBegin(GL_QUADS);
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

    // night sky
    glColor3f(0.0, 0.0, 0.2);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);

    // clouds
    glColor3f(0.0, 0.0, 0.2);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);

    // stars

    // moon
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

    // day sky
    glColor3f(0.1, 0.8, 1);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);

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
//..............................

// create game window
void init() {
    width = 750;
    height = 500;
}

int health = 100;

// wall / obstacle color
color testColor{1.0, 0.0, 0.0}; // red

// create walls / obstacles
Obstacle wall1(40, 15, 1150, testColor);
Obstacle wall2(30, 15, 1000, testColor);
Obstacle wall3(35, 20, 800, testColor);
Obstacle wall4(30, 10, 500, testColor);

Player player(20, 20, 80, color{1.0, 1.0, 1.0}, 400); // test player on ground (yHeight = 400)

vector<Obstacle> walls{wall1, wall2, wall3, wall4};

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
            string daySelect = "[day]                night"; // day background selected
            glRasterPos2i(xPos - (4 * daySelect.length()), yPos + 40);
            for (const char &letter : daySelect) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
        } else {
            string daySelect = " day                [night]"; // night background selected
            glRasterPos2i(xPos - (4 * daySelect.length()), yPos + 40);
            for (const char &letter : daySelect) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
        }
    } else if (screen == running) {
        //////////////////// COLLISION DETECTION BETWEEN PLAYER AND OBSTACLES ////////////////
        // check for collisions with each generated wall
        for (Obstacle &wall : walls) {
            if (collision(player, wall)) {
                health -= 2; // decrease health
            }
        }
        ///////////////////////////////////////////////////////////////////////////////////////
        if (background == day) {
        // draw day
            drawBackground_day(); // drap map before content
//        spawnBackground_sun();
//        spawnBackground_day_clouds();
        }

        else if(background == night) {
        //draw night
            drawBackground_night(); // drap map before content
//            spawnBackground_stars();
//            spawnBackground_moon();
//            spawnBackground_night_clouds();
        }

        drawHealthbar(health); // draw health bar

        //////////////////// DRAW EACH WALL / OBSTACLE TO SCREEN //////////////////////////

        for (Obstacle &wall : walls) {
            wall.draw();
        }
        ///////////////////////////////////////////////////////////////////////////////////
        player.draw(); // draw player to screen

    }

    else {

        string helpMessage1 = "Press the space bar to jump.";
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

        string helpMessage4 = "(Press 'esc' to go back)";
        glRasterPos2i(xPos - (4 * helpMessage4.length()), yPos + 230 );
        for (const char &letter : helpMessage4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

    }
    glEnd();
    glFlush();  // render now
}

void drawBackground(){
    glBegin(GL_QUADS);
    // grey floor
    glColor3f(0.5, 0.5, 0.5);
    glVertex2i(0, 400);
    glVertex2i(750, 400);
    glVertex2i(750, 415);
    glVertex2i(0, 415);

    // green grass
    glColor3f(0.0, 0.4, 0.0);
    glVertex2i(0, 415);
    glVertex2i(750, 415);
    glVertex2i(750, 500);
    glVertex2i(0, 500);

    // blue sky
    glColor3f(0.18, 0.3, 0.84);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);
}

void drawHealthbar(int health){
    int difference;
    if (health > 0){
        difference = 2 * (100 - health);
    } else {
        difference = 200;
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
            background = day;
            break;
        case GLUT_KEY_RIGHT:
            background = night;
            break;
        case GLUT_KEY_UP:

            break;
    }

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

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);

    glutInitWindowPosition(800, 400); // position the window's initial top-left corner

    /* create the window and store the handle to it */
    wd = glutCreateWindow("Jumper Game"); // title

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

