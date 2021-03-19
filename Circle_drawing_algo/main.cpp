#include <GL/glut.h>
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
using namespace std;

float x1=12,x2=19,y1=12,y2=12;
int thickness=1;
string pattern="11";
int xm=1,ym=1;
int len=700,wid=500;
int len_half=350,wid_half=250;
int len_line;
vector<int> points;
GLfloat red=.9;
GLfloat green=.9;
GLfloat blue=.9;
void hex(string hex){
    pattern.clear();
    for(int i=0;i<hex.length();i++){
        if(hex[i]=='0')
            pattern.append("0000");
        else if(hex[i]=='1')
            pattern.append("0001");
        else if(hex[i]=='2')
            pattern.append("0010");
        else if(hex[i]=='3')
            pattern.append("0011");
        else if(hex[i]=='4')
            pattern.append("0100");
        else if(hex[i]=='5')
            pattern.append("0101");
        else if(hex[i]=='6')
            pattern.append("0110");
        else if(hex[i]=='7')
            pattern.append("0111");
        else if(hex[i]=='8')
            pattern.append("1000");
        else if(hex[i]=='9')
            pattern.append("1001");
        else if(hex[i]=='A' || hex[i]=='a')
            pattern.append("1010");
        else if(hex[i]=='B' || hex[i]=='b')
            pattern.append("1011");
        else if(hex[i]=='C' || hex[i]=='c')
            pattern.append("1100");
        else if(hex[i]=='D' || hex[i]=='d')
            pattern.append("1101");
        else if(hex[i]=='E' || hex[i]=='e')
            pattern.append("1110");
        else if(hex[i]=='F' || hex[i]=='f')
            pattern.append("1111");
    }

}
void plot(){
    glBegin(GL_POINTS);
    glColor3f(red,green,blue);

    for(int j=2;j<points.size();j+=2){
        int x=points[j-2];
        int y= points[j-1];
        glVertex2f((float)x/len_half,(float)y/wid_half);
    }
    glEnd();
}

void MIDPOINT_CIRCLE_ALGO(float x1,float y1,float x2,float y2){
    int radius = sqrt((y2-y1)*(y2-y1) - (x2-x1)*(x2-x1));
    int pk = 1- radius;
    int xk=0,yk=radius;
    while(x<=y){
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
    int len = points.size();
    for(int i=2;i<len;i+=2){
        points.push_back(points[i-1]);
        points.push_back(points[i-2]);
    }
    int len = points.size();
    for(int i=2;i<len;i+=2){
        points.push_back(points[i-2]);
        points.push_back(-points[i-1]);
    }
    int len = points.size();
    for(int i=2;i<len;i+=2){
        points.push_back(-points[i-2]);
        points.push_back(points[i-1]);
    }
    int len = points.size();
    for(int i=2;i<len;i+=2){
        points[i-2]+=x1;
        points[i-1]+=y1;
    }
}
void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	MIDPOINT_CIRCLE_ALGO(x1,y1,x2,y2);
    plot();
	glutSwapBuffers();
}

void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
     cout<<"Center"<<endl;
     points.clear();
     x1= x-len/2;
     y1=-1*y +wid/2;
     cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<endl;


  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
     cout<<"Radius"<<endl;
     points.clear();
     x2= x-len/2;
     y2=-1*y +wid/2;

  }
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

int main(int argc, char **argv) {

    cout<<endl<<"ENTER COLOR INTENSITIES OF LINE IN RED,GREEN,BLUE ORDER-"<<endl;
    cin>>red>>green>>blue;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(700,500);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	/// register callbacks
	glutReshapeFunc(resize);
	///glutMouseFunc(OnMouseClick);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 1;
}





