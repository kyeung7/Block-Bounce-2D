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

enum screenState {pending, running};
screenState screen = pending;

enum timeOfDay {day, night};
timeOfDay background = day;

//...............................


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
}

//day time
void drawBackground_day(){

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

    //day sky
    glColor3f(0.1, 0.8, 1);
    glVertex2i(0, 0);
    glVertex2i(750, 0);
    glVertex2i(750, 400);
    glVertex2i(0, 400);
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
    } else {
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

