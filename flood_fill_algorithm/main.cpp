/*
NAME-JATIN GHAI
UE183042
*/
#include <GL/glut.h>
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
using namespace std;

float x1=12,x2=19,y1=12,y2=12,cx=0,cy=0,mouse_click_n0=0,angle=0;int tc=0;
float radius;
int xm=1,ym=1;
int len=700,wid=500;
int len_half=350,wid_half=250;
vector<int> points;
GLfloat red=1;
GLfloat green=1;
GLfloat blue=1;

float col[3];
float tofill[3]={0.0,0.1,0.2};
struct pixel{
    float x, y;
};
vector<pixel> first_buffer;

void getpixel(float x,float y){
    glReadPixels(x+len_half,y+wid_half,1,1,GL_RGB,GL_FLOAT,col);
    col[0]*=10;
    col[1]*=10;
    col[2]*=10;

    col[0]=round(col[0]);
    col[1]=round(col[1]);
    col[2]=round(col[2]);

    col[0]/=10;
    col[1]/=10;
    col[2]/=10;
}

void floodfill(float x,float y){

    getpixel(x,y);
    ///check if pixel has background color and not same color as to be filled
    if ((col[0]==0.0f && col[1]==0.0f && col[2]==0.0f) && !(col[0]==tofill[0] && col[1]==tofill[1] && col[2]==tofill[2]))
    {
        glPointSize(2);
        glBegin(GL_POINTS);
        glColor3f(tofill[0],tofill[1],tofill[2]);
        glVertex2f((float)(x)/len_half,(float)(y)/wid_half);
        glEnd();
        pixel temp;
        temp.x = (float)(x)/len_half;
        temp.y = (float)(y)/wid_half;
        first_buffer.push_back(temp);

        floodfill(x+2,y);
        floodfill(x-2,y);
        floodfill(x,y+2);
        floodfill(x,y-2);
    }
    return;
}

void plot(float theta=0){


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(red,green,blue);
        glVertex2f(-1,0);
        glVertex2f(1,0);
        glVertex2f(0,1);
        glVertex2f(0,-1);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex2f(min(x1,x2)/len_half,max(y1,y2)/wid_half);
        glVertex2f(min(x1,x2)/len_half,min(y1,y2)/wid_half);
        glColor3f(0,1,0);
        glVertex2f(max(x1,x2)/len_half,max(y1,y2)/wid_half);
        glVertex2f(max(x1,x2)/len_half,min(y1,y2)/wid_half);
        glColor3f(1,0,.2);
        glVertex2f(min(x1,x2)/len_half,max(y1,y2)/wid_half);
        glVertex2f(max(x1,x2)/len_half,max(y1,y2)/wid_half);
        glColor3f(0,.5,.5);
        glVertex2f(min(x1,x2)/len_half,min(y1,y2)/wid_half);
        glVertex2f(max(x1,x2)/len_half,min(y1,y2)/wid_half);
    glEnd();

    glPointSize(3);
    for(int i=0; i<first_buffer.size(); i++){
        glBegin(GL_POINTS);
        glColor3f(tofill[0],tofill[1],tofill[2]);
        glVertex2f(first_buffer[i].x , first_buffer[i].y);
        glEnd();
    }
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot();
    glFlush();
}

void OnMouseClick(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mouse_click_n0==0){
            cout<<"x1 y1"<<endl;
            x1= x-len/2;
            y1=-1*y +wid/2;
        }
        if(mouse_click_n0==1){
            cout<<"x2 y2"<<endl;
            x2= x-len/2;
            y2=-1*y +wid/2;
        }
        mouse_click_n0=(mouse_click_n0==0)?1:0;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        cx= x-len/2;
        cy=-1*y +wid/2;
        floodfill(cx,cy);
        glFlush();
    }
}

int main(int argc, char **argv) {

    cout<<"ENTER COLOR INTESITIES OF COLOR TO FILL "<<endl;
    cin>>tofill[0]>>tofill[1]>>tofill[2];

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(700,500);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");
    /// register callbacks
    glutMouseFunc(OnMouseClick);
    glutDisplayFunc(renderScene);
    glutMainLoop();

    return 1;
}
