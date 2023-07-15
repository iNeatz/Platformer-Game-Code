#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

bool isGameOver = false;
string obstacleType[2] = {"Spike", "Torpedo"};
string obsAnim = "finished";

class Player
{
    int x, y, speed;
    char controlKey, jumpStatus;
public:
    Player()
    {
        x = 20;
        y = 400;
        speed = 6;
        jumpStatus='d';
        //Player Initialization
        bar(x,y,x+40,y+40);
    }
    Player(int X, int Y)
    {
        //Player Initialization
        bar(X,Y,X+40,Y+40);
    }
    void jump()
    {
        Player p(x,y);
        if(kbhit())
        {
            controlKey = getch();
            if(controlKey = ' ')
                jumpStatus = 'u';
        }

        if(jumpStatus == 'u')
        {
            y-=speed;
            Player p(x,y);

            if(y<=300)
                jumpStatus = 'd';
        }

        if(jumpStatus == 'd' && y<=400)
        {
            y+=speed;
            Player p(x,y);
        }
    }
};

class Ground
{
public:
    Ground()
    {
        bar(0,440,650,500);
    }
};

class Obstacle
{
    string type;
public:
    Obstacle()
    {
        type = "Spike";
    }

};

void createObs(int x)
{
    int n=3;
    if(obsAnim == "finished")
    {

        for(int i=0; i<n; i++)
        {
            // Specify the coordinates of the triangle
            int points[] = {x, 440, x+40, 440, x+20, 405, x, 440};

            // Draw a filled triangle
            fillpoly(4, points);

            x+=40;
        }

        obsAnim = "running";
    }
}

void moveObs()
{

    int x = getmaxx();

    if(obsAnim == "running")
    {
        delay(20);
        x-=10;
        createObs(x);

        if((x+40)>=0)
            obsAnim = "finished";
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");


    Player p;
    Ground *g = new Ground();
    createObs(getmaxx());

    while(!isGameOver)
    {
        Ground *g = new Ground();
        p.jump();
        moveObs();
        delay(1);
        delete g;
        cleardevice();
    }

    delete g;

    getch();
    closegraph();
    return 0;
}
