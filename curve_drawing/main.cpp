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

float mouse_click_n0=0;int tc=0;
vector<float> coordinates;
float radius;
int xm=1,ym=1;
int len=700,wid=500;
int len_half=350,wid_half=250;
vector<float> points;
GLfloat red=1;
GLfloat green=1;
GLfloat blue=1;
int *sq;
float* comb;
float* px;
float* py;

void plot(float theta=0){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(red,green,blue);

    for(int j=2;j<points.size();j+=2){
        float x=points[j-2];
        float y= points[j-1];
        glVertex2f(x/len_half,y/wid_half);
    }
    for(int j=2;j<coordinates.size();j+=2){
        float x=coordinates[j-2];
        float y= coordinates[j-1];
        glVertex2f(x/len_half,y/wid_half);
    }
    glEnd();

}

void CURVE_ALGO(){
    int n= coordinates.size()/2;
    int x=1000;
    for(int t=0;t<=x;t++){
        points.push_back(0.0);
        points.push_back(0.0);
        for(int j=0;j<n;j++){
            float a =pow((float)t/x,j);
            float b =pow((float)(x-t)/x,n-1-j);
            points[t*2]+=px[j]*a*b;
            points[t*2 + 1]+=py[j]*a*b;
        }
        glBegin(GL_POINTS);
        glColor3f(red,green,blue);
        glVertex2f(points[t*2]/len_half,points[t*2 + 1]/wid_half);
        glEnd();
        glFlush();
    }
    plot();
    glFlush();
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot();
	glFlush();
}
float combb(int r,int n){
    int pron=1;
    for(int i=max(n-r+1,r+1);i<=n;i++){
        pron*=i;
    }
    for(int i=1;i<min(n-r+1,r+1);i++){
        pron/=i;
    }
    return pron;
}
void calc(int n){
    for(int i=0;i<n;i++)
        comb[i]=combb(i,n-1);
    for(int i=0;i<n;i++){
        px[i]=coordinates[i*2]*comb[i];
        py[i]=coordinates[i*2+1]*comb[i];
    }
    delete comb;
    CURVE_ALGO();

}
void OnMouseClick(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        coordinates.push_back(x-len/2);
        coordinates.push_back(-1*y +wid/2);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        coordinates.push_back(x-len/2);
        coordinates.push_back(-1*y +wid/2);
        px=new float[coordinates.size()/2];
        py=new float[coordinates.size()/2];
        comb=new float[coordinates.size()/2];
        calc(coordinates.size()/2);
    }
}

void IDLE_function(){
        plot();
        glFlush();
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
    ///glutIdleFunc(IDLE_function);
	glutMainLoop();

	return 1;
}










