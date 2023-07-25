#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

bool isGameOver = false;
int obsX, noOfObs;
string obsType[2] = {"Spike", "Torpedo"};

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
            if(controlKey == ' ')
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
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
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

class Obstacle : public Player
{
    string type;
public:
    Obstacle()
    {
        srand(time(0));
        //randomize obstacle type
        int p = rand()%2;
        type = obsType[p];
    }
    void createObs(int x, int n)
    {
        if(type == "Spike")
        {
            for(int j=0; j<n; j++)
            {
                // Specify the coordinates of the triangle
                int points[] = {x, 440, x+40, 440, x+20, 405, x, 440};

                // Draw a filled triangle
                fillpoly(4, points);

                x+=40;


            }
        }
        else if(type == "Torpedo")
        {
            bar(x, 350, x+20, 370);
        }
    }
    void moveObs()
    {
        if(obsX > -120)
            obsX-=7;
        else
        {
            obsX = getmaxx();
            noOfObs = 1 + rand() % 3;
            int p = rand()%2;
            type = obsType[p];
        }
    }

};


int main()
{
    int gd = DETECT, gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

    obsX = getmaxx();
    srand(time(0));
    noOfObs = 1 + rand() % 3;

    Player p;
    Ground *g = new Ground();
    Obstacle *o = new Obstacle();
    o->createObs(obsX, noOfObs);

    while(!isGameOver)
    {
        Ground *g = new Ground();
        p.jump();
        o->moveObs();
        o->createObs(obsX, noOfObs);
        delay(1);
        delete g;
        cleardevice();
    }

    delete g;
    delete o;

    getch();
    closegraph();
    return 0;
}
