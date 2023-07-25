#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

bool isGameOver = false;
int obsX, noOfObs, playerX = 20, playerY = 400, score = 0, highScore;
string obsType[2] = {"Spike", "Torpedo"};

FILE *fp;

class Player
{
    int speed;
    char controlKey, jumpStatus;
public:
    Player()
    {
        speed = 6;
        jumpStatus='d';
        //Player Initialization
        bar(playerX,playerY,playerX+40,playerY+40);
    }
    Player(int X, int Y)
    {
        //Player Initialization
        bar(X,Y,X+40,Y+40);
    }
    void jump()
    {
        Player p(playerX,playerY);
        if(kbhit())
        {
            controlKey = getch();
            if(controlKey == ' ')
                jumpStatus = 'u';
        }

        if(jumpStatus == 'u')
        {
            playerY-=speed;
            Player p(playerX,playerY);

            if(playerY<=300)
                jumpStatus = 'd';
        }

        if(jumpStatus == 'd' && playerY<=400)
        {
            playerY+=speed;
            Player p(playerX,playerY);
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


                //Collision Detection
                if(((x+20)>=playerX &&(x+20)<=playerX+40) && (405>=playerY && 405 <= playerY+40))
                    isGameOver = true;

                x+=40;
            }
        }
        else if(type == "Torpedo")
        {
            //Torpedo Initialization
            fillellipse(x,350,20,10);

            //Collision Detection
            if((x>=playerX && x<=playerX+40) && (350>=playerY && 350 <= playerY+40))
                isGameOver = true;
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
            score+=10;
        }
    }

};

void scoreDisplay(int score)
{
    char scoreText[50];
    sprintf(scoreText, "%d", score);
    outtextxy(getmaxx() - 30,25,scoreText);
}

void gameOver(int score)
{
    isGameOver = true;
    char scoreOut[50], highScoreOut[50];

    sprintf(scoreOut, "Your Score is: %d", score);

    //Reading HighScore
    fp = fopen("highscore.txt", "r");
    fscanf(fp, "%d", &highScore);
    fclose(fp);

    outtextxy(300,225,"Game Over!!");
    outtextxy(290,250,scoreOut);


    if(score > highScore)
    {
        fp = fopen("highscore.txt", "w");
        fprintf(fp, "%d", score);
        fclose(fp);
    }

    if(score <= highScore)
    {
        sprintf(highScoreOut, "HighScore: %d", highScore);
        outtextxy(300,275,highScoreOut);
    }
    else
    {
        outtextxy(300,275,"New Highscore!!!");
    }

}

void launchScreen()
{
    readimagefile("assets/launch.jpg", 0, 0, getmaxx(), getmaxy());
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

    launchScreen();
    char startKey = getch();

    if(startKey == ' ')
    {
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
            scoreDisplay(score);
            p.jump();
            o->moveObs();
            o->createObs(obsX, noOfObs);
            delay(1);
            delete g;
            cleardevice();
        }

        delete g;
        delete o;

        gameOver(score);
    }

    getch();
    closegraph();
    return 0;
}
