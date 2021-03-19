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
int m=4;
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
int coordinate_start=0,point_start=0;

void plot(float theta=0){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(red,green,blue);
    for(int j=2;j<points.size();j+=2){
        float x=points[j-2];
        float y= points[j-1];
        glVertex2f(x/len_half,y/wid_half);
    }
    glEnd();
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);


    for(int j=0;j<coordinates.size()/2;j++){
        float x = coordinates[j*2];
        float y = coordinates[j*2+1];
        glVertex2f(x/len_half,y/wid_half);

    }
    glEnd();

}
float calct(float t){
    return t;
}
float spline(float t,int k,int m){
    if(m==1){
        if((float)calct(k)<t && (float)calct(k+1)>=t)
            return 1;
        return 0;
    }
    float part1= (t-calct(k))/(calct(k+m-1)-calct(k))*spline(t,k,m-1);
    float part2= (calct(k+m)-t)/(calct(k+m)-calct(k+1))*spline(t,k+1,m-1);
    return part1+part2;
}
void CURVE_ALGO(){
    int n= coordinates.size()/2 - coordinate_start/2;
    int x=n+m-2;
    int ls=0;
    int check=0;
    point_start=points.size();
    points.push_back(0.0);
    points.push_back(0.0);
    for(int t=0;t<=x;t++){
        for(int xtx=0;xtx<1000;xtx+=1){
            for(int j=0;j<n;j++){
                float x1 = coordinates[j*2 +coordinate_start];
                float y1 = coordinates[j*2+1 +coordinate_start];
                float nkm = spline((float)t+((float)xtx/1000),j+m-1,m);
                points[ls*2 + point_start]+=x1*nkm;
                points[ls*2+1 + point_start]+=y1*nkm;
            }
            if(check==1){
                points.push_back(0.0);
                points.push_back(0.0);
                ls++;
            }
            else{
                if(coordinates.size()-coordinate_start>=2
                   && points[ls*2+point_start]-coordinates[coordinate_start]<1
                   && points[ls*2+point_start]-coordinates[coordinate_start]>-1
                   && points[ls*2 +1 +point_start]-coordinates[1+coordinate_start]<1
                   && points[ls*2 +1 +point_start]-coordinates[1+coordinate_start]>-1) check=1;
                points[ls*2+point_start]=0.0;
                points[ls*2 +1 +point_start]=0.0;
            }
        }
    }
    plot();
    glFlush();
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	plot();
    glFlush();
}
void OnMouseClick(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        coordinates.push_back(x-len/2);
        coordinates.push_back(-1*y +wid/2);
        if(coordinates.size()-coordinate_start==2){
            for(int i=1;i<m-1;i++){
                coordinates.push_back(x-len/2);
                coordinates.push_back(-1*y +wid/2);
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        for(int i=0;i<m-1;i++){
            coordinates.push_back(x-len/2);
            coordinates.push_back(-1*y +wid/2);
        }
        CURVE_ALGO();
        coordinate_start=coordinates.size();
    }
}

void IDLE_function(){
        plot();
        glFlush();
}

int main(int argc, char **argv) {

    cin>>m;
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
