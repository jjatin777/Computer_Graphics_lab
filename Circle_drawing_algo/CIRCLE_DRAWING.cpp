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
GLfloat red=0;
GLfloat green=0;
GLfloat blue=0;

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
        glColor3f(tofill[0],tofill[1],tofill[2]);
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
	glFlush();
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

        cx= x-len/2;
        cy=-1*y +wid/2;
        floodfill(cx,cy);
        glFlush();
    }
}

void IDLE_function(){

        plot();
        glFlush();

}



int main(int argc, char **argv) {

    cout<<"ENTER COLOR INTESITIES OF BOUNDARY"<<endl;
    cin>>red>>green>>blue;
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
    glutIdleFunc(IDLE_function);
	glutMainLoop();

	return 1;
}










