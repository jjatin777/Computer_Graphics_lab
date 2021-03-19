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

    ///cx= x;
    ///cy +wid-y;

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
    glPointSize(4);
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

void BRESENHAM_LINE(float xl1,float yl1,float xl2,float yl2){
    int il=points.size();
    xm=1;ym=1;
    float p0=0;
    if(xl2<xl1 && yl2>=yl1)
        xm=-1;
    else if(xl2<=xl1 && yl2<yl1){
        xm=-1;
        ym=-1;
    }
    else if(xl2>xl1 && yl2<=yl1)
        ym=-1;
    xl1*=xm;
    xl2*=xm;
    yl1*=ym;
    yl2*=ym;
    float xx=xl1,yy=yl1;
    float dx=xl2-xl1;
    float dy=yl2-yl1;
    float slope=dy/dx;

    points.push_back(xx);
    points.push_back(yy);
    if(slope<=1 && slope>=0){
        p0=(2*dy)-dx;
        while(xx<=xl2){
            if(p0>=0){
                xx+=1;
                yy+=1;
                p0=p0+2*(dy-dx);

            }else{
                p0=p0+2*dy;
                xx+=1;
            }
            points.push_back(xx);
            points.push_back(yy);
        }
    }else if(slope>1){
        p0=2*dx-dy;
        while(yy<=yl2){

            if(p0>=0){
                xx+=1;
                yy+=1;
                p0+=2*(dx-dy);
            }else{
                p0+=2*dx;
                yy+=1;
            }
            points.push_back(xx);
            points.push_back(yy);
        }

    }
    for(int i=il+2;i<points.size();i+=2){
        points[i-2]*=xm;
        points[i-1]*=ym;
    }
    for(int i=il+2;i<points.size();i+=2){
        points[i-2]+=x1;
        points[i-1]+=y1;
    }
    xl1*=xm;
    xl2*=xm;
    yl1*=ym;
    yl2*=ym;
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
        BRESENHAM_LINE(-radius,0,radius,0);
        BRESENHAM_LINE(0,radius,0,-radius);
        BRESENHAM_LINE(-1*radius*.7071,-1*radius*.7071,radius*.7071,radius*.7071);
        BRESENHAM_LINE(-1*radius*.7071,radius*.7071,radius*.7071,-1*radius*.7071);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        ccI=(ccI+1)%4;
        cx= x-len/2;
        cy=-1*y +wid/2;
        boundaryfill(cx,cy,ccI);
        glFlush();
    }
}

void IDLE_function(){
    if(ch_key=='x'){
        for(int i=0; i<first_buffer.size(); i++){
            first_buffer[i].cc =(first_buffer[i].cc+1)%4;
        }
        plot();
        long time=gtime;
        while(time>0){
            time--;
        glFlush();
        }
    }
    else if(ch_key=='c'){
        for(int i=0; i<first_buffer.size(); i++){
            first_buffer[i].cc =first_buffer[i].cc-1;
            if(first_buffer[i].cc==-1) first_buffer[i].cc=3;
        }
        plot();
        long time=gtime;
        while(time>0){
            time--;
        }
        glFlush();
    }
    else if(ch_key=='s'){
        plot();
        glFlush();
    }
}

void OnKeyboardClick(unsigned char key,int x,int y){

    if(key=='i'){
        gtime-=gtime/2;
        cout<<"You increased the speed"<<endl;
    }else if(key=='d'){
        gtime+=gtime/2;
        cout<<"YOu decreased the speed"<<endl;
    }else{
        ch_key=key;
    }
}

int main(int argc, char **argv) {

    cout<<"Right click in the sectors to fill color\n"
          "First Left click will pick the position of center\n"
          "Second Left click will pick the position of radius\n"
          "Press c for Clockwise motion of the wheel\n"
          "Press x for CounterClockwise motion of the wheel\n"
          "Press s to stop motion of the wheel\n"
          "Press i to increase speed of the wheel\n"
          "Press d to decrease speed of the wheel\n"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(700,500);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");
	/// register callbacks
	glutMouseFunc(OnMouseClick);
	glutKeyboardFunc(OnKeyboardClick);
	glutDisplayFunc(renderScene);
    glutIdleFunc(IDLE_function);
	glutMainLoop();

	return 1;
}










