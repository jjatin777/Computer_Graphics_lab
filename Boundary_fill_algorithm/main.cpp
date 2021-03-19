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
long gtime=99999999;
char ch_key='s';
int xm=1,ym=1,stop=0;
int len=700,wid=500;
int len_half=350,wid_half=250;
vector<int> points;
int radius;
GLfloat red=1.0;
GLfloat green=1.0;
GLfloat blue=1.0;
int ccI=0;
float col[3];
float tofill[4][3]={1.0,0.1,0.2,
                  0.8,1.0,0.2,
                  0.0,0.8,1.0,
                  0.5,0.5,1.0};
struct pixel{
    float x, y;
    int cc;
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

void boundaryfill(float x,float y,int cc){

    getpixel(x,y);
    if (!(col[0]==red && col[1]==green && col[2]==blue) && !(col[0]==tofill[cc][0] && col[1]==tofill[cc][1] && col[2]==tofill[cc][2]))
    {
        glPointSize(2);
        glBegin(GL_POINTS);
        glColor3f(tofill[cc][0],tofill[cc][1],tofill[cc][2]);
        glVertex2f((float)(x)/len_half,(float)(y)/wid_half);
        glEnd();
        pixel temp;
        temp.x = (float)(x)/len_half;
        temp.y = (float)(y)/wid_half;
        temp.cc=cc;
        first_buffer.push_back(temp);

        boundaryfill(x+2,y,cc);
        boundaryfill(x-2,y,cc);
        boundaryfill(x,y+2,cc);
        boundaryfill(x,y-2,cc);
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
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(red,green,blue);

    for(int j=2;j<points.size();j+=2){
        int x=points[j-2];
        int y= points[j-1];
        glVertex2f((float)x/len_half,(float)y/wid_half);
    }
    glEnd();
    for(int i=0; i<first_buffer.size(); i++){
        glBegin(GL_POINTS);
        glColor3f(tofill[first_buffer[i].cc][0],tofill[first_buffer[i].cc][1],tofill[first_buffer[i].cc][2]);
        glVertex2f(first_buffer[i].x , first_buffer[i].y);
        glEnd();
    }
}

void MIDPOINT_CIRCLE_ALGO(float x1,float y1,float x2,float y2){

    int pk = 1- radius;
    int xk=0,yk=radius;
    while(xk<=yk){
        points.push_back(xk);
        points.push_back(yk);
        xk++;
        if(pk>=0){
            yk-=1;
            pk+=2*(xk-yk)+1;
        }else{
            pk+=2*xk+1;
        }
    }
    points.push_back(xk);
    points.push_back(yk);

    int len = points.size();
    for(int i=2;i<len;i+=2){
        points.push_back(points[i-1]);
        points.push_back(points[i-2]);
    }
    len = points.size();
    for(int i=2;i<len;i+=2){
        points.push_back(points[i-2]);
        points.push_back(-points[i-1]);
    }
    len = points.size();
    for(int i=2;i<len;i+=2){
        points.push_back(-points[i-2]);
        points.push_back(points[i-1]);
    }
    len = points.size();
    for(int i=2;i<len;i+=2){
        points[i-2]+=x1;
        points[i-1]+=y1;
    }

}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot();
    glutSwapBuffers();
}

void OnMouseClick(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mouse_click_n0==0){
            cout<<"This is the new Center"<<endl;
            x1= x-len/2;
            y1=-1*y +wid/2;
        }
        if(mouse_click_n0==1){
            cout<<"This is the new Radius"<<endl;
            x2= x-len/2;
            y2=-1*y +wid/2;
        }
        mouse_click_n0=(mouse_click_n0==0)?1:0;
        radius = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
        points.clear();
        MIDPOINT_CIRCLE_ALGO(x1,y1,x2,y2);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        ccI=(ccI+1)%4;
        cx= x-len/2;
        cy=-1*y +wid/2;
        boundaryfill(cx,cy,ccI);
    }
}

int main(int argc, char **argv) {

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










