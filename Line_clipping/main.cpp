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

float cmouse_click_n0=0,mouse_click_n0=0,angle=0;int tc=0;
int jpoints=0;
float x[2]={20,40},y[2]={20,40},cx[2]={35,10},cy[2]={45,25};
int len=700,wid=500;
int len_half=350,wid_half=250;
vector<int> points;
GLfloat red=0;
GLfloat green=1;
GLfloat blue=1;

void LINE_CLIPPING(){
    float p[5]={0},q[5]={0},u1=0,u2=1;
    p[1] = cx[0]-cx[1];
    p[2] = -p[1];
    p[3] = cy[0]-cy[1];
    p[4] = -p[3];
    q[1] = cx[0]-x[0];
    q[2] = x[1]-cx[0];
    q[3] = cy[0]-y[0];
    q[4] = y[1]-cy[0];
    cout<<cy[0]<<" "<<cy[1]<<" "<<cy[0]-cy[1]<<endl;
    if(cy[0]==cy[1]){
            cout<<x[0]<<" "<<y[0]<<" "<<x[1]<<" "<<y[1]<<endl;
        cout<<p[1]<<" "<<p[2]<<" "<<p[3]<<" "<<p[4]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" "<<q[4]<<" "<<endl;
    }
    glBegin(GL_LINES);
    ///if((p[1]==0 || p[3]==0) && (q[1]<0 || q[2]<0 || q[3]<0 || q[4]<0)){
    if((p[1]==0 &&(q[1]<0 || q[2]<0 )) || (p[3]==0 &&(q[3]<0 || q[4]<0 ))){
        glVertex2f((float)cx[0]/len_half,(float)cy[0]/wid_half);
        glVertex2f((float)cx[1]/len_half,(float)cy[1]/wid_half);
        glEnd();
    }else{
        for(int k=1;k<5;k++){
            if(p[k]<0){
                u1=max(u1,q[k]/p[k]);
            }
            if(p[k]>0){

                u2=min(u2,q[k]/p[k]);
            }
        }
        if(u1>u2){
            glVertex2f((float)cx[0]/len_half,(float)cy[0]/wid_half);
            glVertex2f((float)cx[1]/len_half,(float)cy[1]/wid_half);
            glEnd();
        }
        else{
            glColor3f(red,green,blue);
                glVertex2f((float)cx[0]/len_half,(float)cy[0]/wid_half);
                glVertex2f((float)(cx[0]+u1*(cx[1]-cx[0]))/len_half,(float)(cy[0]+u1*(cy[1]-cy[0]))/wid_half);

            glColor3f(1.0f,0.0f,0.0f);
                glVertex2f((float)(cx[0]+u1*(cx[1]-cx[0]))/len_half,(float)(cy[0]+u1*(cy[1]-cy[0]))/wid_half);
                glVertex2f((float)(cx[0]+u2*(cx[1]-cx[0]))/len_half,(float)(cy[0]+u2*(cy[1]-cy[0]))/wid_half);

            glColor3f(red,green,blue);
                glVertex2f((float)(cx[0]+u2*(cx[1]-cx[0]))/len_half,(float)(cy[0]+u2*(cy[1]-cy[0]))/wid_half);
                glVertex2f((float)cx[1]/len_half,(float)cy[1]/wid_half);
        glEnd();
        }
    }
}
void POINT_CLIPPING(){
    glBegin(GL_POINTS);
    if(cx[0]<x[1] && cx[0]>x[0] && cy[0]<y[1] && cy[0]>y[0]){

        glColor3f(1.0f,0.0f,0.0f);
    }else{
        glColor3f(red,green,blue);
    }
    glVertex2f((float)cx[0]/len_half,(float)cy[0]/wid_half);
    glEnd();
}
void SQUARE_ALGO(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(3);
    glLineWidth(2);
    glBegin(GL_LINES);
        /*
        glColor3f(red,green,blue);
        glVertex2f(-1,0);
        glVertex2f(1,0);
        glVertex2f(0,1);
        glVertex2f(0,-1);*/

        glColor3f(red,green,blue);
        glVertex2f((float)x[0]/len_half,(float)y[0]/wid_half);
        glVertex2f((float)x[1]/len_half,(float)y[0]/wid_half);

        glVertex2f((float)x[1]/len_half,(float)y[0]/wid_half);
        glVertex2f((float)x[1]/len_half,(float)y[1]/wid_half);

        glVertex2f((float)x[1]/len_half,(float)y[1]/wid_half);
        glVertex2f((float)x[0]/len_half,(float)y[1]/wid_half);

        glVertex2f((float)x[0]/len_half,(float)y[1]/wid_half);
        glVertex2f((float)x[0]/len_half,(float)y[0]/wid_half);
    glEnd();
    if(jpoints==0)
        LINE_CLIPPING();
    else
        POINT_CLIPPING();
}
void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SQUARE_ALGO();
	glFlush();
}

void OnMouseClick(int button, int state, int xx, int yy){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mouse_click_n0==0){
            cout<<"LOWER LEFT Coordinate"<<endl;
            x[0]= xx-len/2;
            y[0]=-1*yy +wid/2;
        }
        if(mouse_click_n0==1){
            cout<<"UPPER RIGHT Coordinate"<<endl;
            x[1]= xx-len/2;
            y[1]=-1*yy +wid/2;
        }
        float tempx= min(x[0],x[1]);
        x[1]=max(x[0],x[1]);
        x[0]=tempx;


        float tempy= min(y[0],y[1]);
        y[1]=max(y[0],y[1]);
        y[0]=tempy;
        mouse_click_n0=(mouse_click_n0==0)?1:0;

    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
         if(cmouse_click_n0==0 || jpoints==1){
            cout<<"FIRST Coordinate"<<endl;
            cx[0]= xx-len/2;
            cy[0]=-1*yy +wid/2;
        }
        if(cmouse_click_n0==1){
            cout<<"SECOND Coordinate"<<endl;
            cx[1]= xx-len/2;
            cy[1]=-1*yy +wid/2;
        }
        cmouse_click_n0=(cmouse_click_n0==0)?1:0;

    }
}

int main(int argc, char **argv) {

    cout<<"ENTER 0 FOR LINE CLIPPING \nENTER 1 FOR POINT CLIPPING\n";
    cin>>jpoints;
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










