/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h> //------------------
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Balloons.h"

using namespace std;
int phyWidth=700;
int phyHeight=700; //physical window size
int logWidth=400; //logical width (ortho)
int logHeight=400;

int basketx=45;
//int baskety=15;
//==
int alphaX=0;
int alphaY=0;
int gameTime=20;
int score=0;
int balloonRad=5; //balloons radius
int gameEnd=0; //flag for game start and end
char t[500];
//string s;
Balloons balloon[20];
//===========
void init2D()
{
    glClearColor(0.0,0.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,logWidth,0.0,logHeight);
}
//======================
void make_balloons(){
    //make balloons
    for(int i=0;i<20;i++)
    {
        balloon[i].x=5 + (rand() % 395);
        balloon[i].y=-5;
        balloon[i].activate=false;
        balloon[i].color=0 + (rand() % 2);
        balloon[i].direction=1; //up
    }
}
//================
void reset()
{
    make_balloons();
    score=0;
    gameTime=20;
    gameEnd=0;
}
//======================
void catch_balloon()
{
     int pt2x=basketx-8+alphaX;

    int pt3x=basketx+38+alphaX;

        for(int i = 0; i < 20; i++)
        {

            if(balloon[i].direction==0 &&(balloon[i].y-balloonRad)<=40 && (balloon[i].y-balloonRad)>15)
            {
                if((balloon[i].x-balloonRad)<=pt3x && (balloon[i].x+balloonRad)>=pt2x)
                {

                    score++;
                    balloon[i].y=-200;
                }

            }
        }

}
//=========================
//can't handle special keys
void keyboard(unsigned char key,int x,int y) //key ->keyboard stroke, x==>mouse position ,y==>mouse position
{
    if(key=='a')
        alphaX-=5;
    if(key=='d')
        alphaX+=5;
    //catch balloon
    catch_balloon();
    glutPostRedisplay(); //recall display to draw new shape

}
//===========
void specialkeyboard(int key,int x,int y) //key ->keyboard stroke, x==>mouse position ,y==>mouse position
{
    if(key==GLUT_KEY_LEFT)
        alphaX-=5;
    if(key==GLUT_KEY_RIGHT)
        alphaX+=5;
    if(key==GLUT_KEY_F1)
        reset();
    //catch balloon

    catch_balloon();
    glutPostRedisplay(); //recall display to draw new shape

}
//=====================
void printSome(char *str,int x,int y)
{
    glColor3f(0,1.0,0.0);
    glRasterPos2d(x,y);
    for(int i=0;i<strlen(str);i++) //strlen inc complexity to n^2 a7sbha mara wahda l awel
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);//font and size
    glFlush();
}
//==================================
void mouseClick(int btn, int state, int x, int y)
{
    float mouseXX,mouseYY;
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
         mouseXX = x;
         mouseXX=0.5+1.0*mouseXX*logWidth/phyWidth;
         mouseYY = phyHeight - y;
         mouseYY=0.5+1.0*mouseYY*logHeight/phyWidth;

      //check balloon pop
      for(int i = 0; i < 20; i++)
      {
        if( mouseXX>(balloon[i].x-balloonRad)&&mouseXX<(balloon[i].x+balloonRad)&& mouseYY <(balloon[i].y+balloonRad)&& mouseYY >(balloon[i].y-balloonRad)&&balloon[i].direction==1)
         {

             if(balloon[i].color==1) //yellow=1
                score+=2;
             else //red=0
                score++;
           balloon[i].y=-200;
         }

      }
  glutPostRedisplay();
    }
}
//=======================================
void DrawCircle(float cx,float cy,float r,int num_segments,int color)
{
    if(color==0) //red
       glColor3f(1.0,0.0,0.0);
    else
        glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON); //line loops -->fadya mn gowa// polygon --> solid circle
    for(int i=0;i<num_segments;i++)
    {
        float theta=2.0f*3.1415926f*float(i)/float(num_segments);
        float x=r*cosf(theta);
        float y=r*sinf(theta);
        glVertex2f(x+cx,y+cy);
    }

    glEnd();
}
//=====================================
void move_balloons_Timer(int value) //balloons y axis change
{
    for(int i = 0 ; i <20 ; i++)
    {
      if(balloon[i].y <395 && balloon[i].direction==1 && balloon[i].activate==1)
      {
          balloon[i].y+=1;
        }

      else if(balloon[i].y >= 395 && gameEnd==0) //reverse ball direction
       {
           balloon[i].direction=0;
           score--;
           balloon[i].y-=1;
       }
       else if(balloon[i].direction==0)

         balloon[i].y-=1;
    }

 glutPostRedisplay();
 glutTimerFunc(10, move_balloons_Timer, value);

}
//================================
void activate_balloons_Timer(int value) //deploy balloons one by one
{
     for (int i = 0; i < 20; i++)
    {
       if(balloon[i].activate==0)   //activated
        {
            balloon[i].activate=1;
            break;
        }
    }
//   glutPostRedisplay();
 glutTimerFunc(500, activate_balloons_Timer, value);
}
//==================================
void gameOver_Timer(int value)
{
    gameTime--;
    if(gameTime<=0)
    {
        gameEnd=1;
    }
    glutTimerFunc(1000, gameOver_Timer, value);
}
//=================================
void draw_Balloons()
{
    for(int i=0;i<20;i++)
    {
        if(balloon[i].activate==1)
            DrawCircle(balloon[i].x,balloon[i].y,balloonRad,100,balloon[i].color);
    }
}
//============================
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //===========================
    //grass
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
         glVertex2f(0,0); //45
        glVertex2f(0,30); //41
        glVertex2f(logWidth,30); //60
        glVertex2f(logWidth,0); //56
    glEnd();

    //=====================
    //BOX
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        if(alphaX+basketx+30 >= logWidth)
        {
             alphaX=0;
             int t=logWidth-35;
            basketx=t;
        }
        else if(alphaX+basketx-4 <= 0)
        {
            alphaX=0;
            basketx=8;
        }
        glVertex2f(basketx+alphaX,15); //45
        glVertex2f(basketx-8+alphaX,40); //41
        glVertex2f(basketx+38+alphaX,40); //60
        glVertex2f(basketx+30+alphaX,15); //56
    glEnd();
    //=============================
    //start game
    if(gameEnd==0)
    {
        sprintf(t, "score: %d", score);
        printSome(t,1,390);

        sprintf(t, "Time: %d", gameTime);
        printSome(t,365,390);

        draw_Balloons();
    }
    else if(gameEnd ==1) //gameover
    {
//        glColor3f(0.0,1.0,0.0);
//        glBegin(GL_QUADS);
//            glVertex2f(0,0);
//            glVertex2f(0,400);
//            glVertex2f(400,400);
//            glVertex2f(400,0);
//        glEnd();

         printSome("TIME'S UP",200,200);
         sprintf(t, "YOUR SCORE IS :%d", score);
         printSome(t,190,190);
         printSome("PRESS F1 TO PLAY AGAIN",180,180);

    }
    catch_balloon();
    //=========================
    glutSwapBuffers();
    glFlush();
}
/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(phyWidth,phyHeight);
    glutCreateWindow("Balloon Popper Game");
    init2D();
    //========================
    make_balloons();
    glutDisplayFunc(display);
     move_balloons_Timer(0);
    activate_balloons_Timer(0);
     glutMouseFunc(mouseClick);
     gameOver_Timer(0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    //===========================
    glutMainLoop();
}
