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

float x1=120,x2=190,y1=12,y2=12,cx=0,cy=0;int tc=0;
int xm=1,ym=1,stop=0;
int len=700,wid=500;
int len_half=350,wid_half=250;
int radius;
int valid =0;
int translation_valid=0;
int Scaling_valid=0;
GLfloat red=1.0;
GLfloat green=1.0;
GLfloat blue=1.0;

vector<vector<float>> coordinates;
vector<vector<float>> pinpoints;
vector<float> demo;
vector<char> key_data;
int curr_curve =0;
char curr_motion = 's';
int polygon_start=0;
float axis_x=0,axis_y=0;
int select_axis=0;
float rotation_point_x=0,rotation_point_y=0;
int rotation_point=0;
vector<float> temporary_data;

void plot(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(4);
    for(int i=0;i<3;i++){

        glBegin(GL_POINTS);
        glColor3f(1.0f,0.0f,0.0f);

        for(int j=2;j<=pinpoints[i].size();j+=2){

            float x=pinpoints[i][j-2];
            float y= pinpoints[i][j-1];
            glVertex2f((float)x/len_half,(float)y/wid_half);

        }
        glEnd();
    }
    glPointSize(2);

    for(int i=0;i<3;i++){

        if(i==0 && polygon_start==0) continue;

        if(i==0) glBegin(GL_POLYGON);

        else glBegin(GL_POINTS);

        glColor3f(red,green,blue);

        if(i==curr_curve && curr_motion != 's' && temporary_data.size()!=0){

            for(int j=2;j<=temporary_data.size();j+=2){

                float x = temporary_data[j-2];
                float y = temporary_data[j-1];
                glVertex2f((float)x/len_half,(float)y/wid_half);
            }

        }else{

            for(int j=2;j<=coordinates[i].size();j+=2){

                float x=coordinates[i][j-2];
                float y= coordinates[i][j-1];
                glVertex2f((float)x/len_half,(float)y/wid_half);
            }
        }
        glEnd();

    }
    glFlush();
}

void MIDPOINT_CIRCLE_ALGO(){

    float x1=coordinates[2][0];
    float y1=coordinates[2][1];
    float x2=coordinates[2][2];
    float y2=coordinates[2][3];
    radius = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    int pk = 1- radius;
    int xk=0,yk=radius;
    coordinates[2].clear();
    while(xk<=yk){
        coordinates[2].push_back(xk);
        coordinates[2].push_back(yk);
        xk++;
        if(pk>=0){
            yk-=1;
            pk+=2*(xk-yk)+1;
        }else{
            pk+=2*xk+1;
        }
    }
    coordinates[2].push_back(xk);
    coordinates[2].push_back(yk);

    int len = coordinates[2].size();
    for(int i=2;i<len;i+=2){
        coordinates[2].push_back(coordinates[2][i-1]);
        coordinates[2].push_back(coordinates[2][i-2]);
    }
    len = coordinates[2].size();
    for(int i=2;i<len;i+=2){
        coordinates[2].push_back(coordinates[2][i-2]);
        coordinates[2].push_back(-coordinates[2][i-1]);
    }
    len = coordinates[2].size();
    for(int i=2;i<len;i+=2){
        coordinates[2].push_back(-coordinates[2][i-2]);
        coordinates[2].push_back(coordinates[2][i-1]);
    }
    len = coordinates[2].size();
    for(int i=2;i<len;i+=2){
        coordinates[2][i-2]+=x1;
        coordinates[2][i-1]+=y1;
    }
    plot();
}

void BRESENHAM_LINE(){

    float xl1=coordinates[1][0];float yl1=coordinates[1][1];float xl2=coordinates[1][2];float yl2=coordinates[1][3];
    coordinates[1].clear();
    int il=coordinates[1].size();
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

    coordinates[1].push_back(xx);
    coordinates[1].push_back(yy);
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
            coordinates[1].push_back(xx);
            coordinates[1].push_back(yy);
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
            coordinates[1].push_back(xx);
            coordinates[1].push_back(yy);
        }

    }
    for(int i=il+2;i<coordinates[1].size();i+=2){
        coordinates[1][i-2]*=xm;
        coordinates[1][i-1]*=ym;
    }

    xl1*=xm;
    xl2*=xm;
    yl1*=ym;
    yl2*=ym;
    plot();
}

void Polygon(){
    plot();
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot();
}

void calculate(){
    if(curr_curve==1){
        BRESENHAM_LINE();
    }else if(curr_curve==2){
        MIDPOINT_CIRCLE_ALGO();
    }else{
        Polygon();
    }
}

void SCALE(float x1, float y1){

    y1-=axis_y;
    x1-=axis_x;

    float sx = x1/rotation_point_x;
    float sy = y1/rotation_point_y;

    temporary_data.clear();
    for(int i=2;i<=coordinates[curr_curve].size();i+=2){
        float xx=coordinates[curr_curve][i-2] - axis_x;
        float yy=coordinates[curr_curve][i-1] - axis_y ;
        temporary_data.push_back( xx*sx+ axis_x);
        temporary_data.push_back( yy*sy + axis_y);
    }
    plot();
}

void TRANSLATE(float x1, float y1){

    y1-=axis_y;
    x1-=axis_x;

    temporary_data.clear();
    for(int i=2;i<=coordinates[curr_curve].size();i+=2){
        float xx=coordinates[curr_curve][i-2];
        float yy=coordinates[curr_curve][i-1];
        temporary_data.push_back( xx + x1);
        temporary_data.push_back( yy + y1);
    }
    plot();
}

void ROTATE(float x1, float y1){

    y1-=axis_y;
    x1-=axis_x;

    float phi = atan2(rotation_point_y,rotation_point_x);

    float theta = atan2(y1,x1);
    theta= theta-phi;
    float coss = cos(theta);
    float sinn = sin(theta);

    temporary_data.clear();
    for(int i=2;i<=coordinates[curr_curve].size();i+=2){
        float xx=coordinates[curr_curve][i-2] - axis_x;
        float yy=coordinates[curr_curve][i-1] - axis_y ;
        temporary_data.push_back( xx*coss - yy*sinn + axis_x);
        temporary_data.push_back( yy*coss + xx*sinn + axis_y);
    }
    plot();
}

void OnMouseClick(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x1 = x-len_half;
        y1 = -1*y +wid_half;


        if(valid){
            if(!select_axis){
                axis_x = x1;
                axis_y = y1;
                select_axis=1;
            }
            else if(select_axis && !rotation_point){
                rotation_point=1;
                rotation_point_x = x1 - axis_x;
                rotation_point_y = y1 - axis_y;
            }
        }
        else if(translation_valid){
            if(!select_axis){
                axis_x = x1;
                axis_y = y1;
                select_axis=1;
            }
        }else if(Scaling_valid){
            if(!select_axis){
                axis_x = x1;
                axis_y = y1;
                select_axis=1;
            }
            else if(select_axis && !rotation_point){
                rotation_point=1;
                rotation_point_x = x1 - axis_x;
                rotation_point_y = y1 - axis_y;
            }
        }
        else{
            coordinates[curr_curve].push_back(x1);
            coordinates[curr_curve].push_back(y1);
            pinpoints[curr_curve].push_back(x1);
            pinpoints[curr_curve].push_back(y1);
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if(curr_curve==0) polygon_start=1;
        calculate();
    }
}

void OnKeyboardClick(unsigned char key,int x,int y){

    if (key == 'i'){

        cout<<"For drawing line left click for first point and last point and then right click,\n";
        cout<<"For drawing circle left click for center point and circumference point and then right click,\n";
        cout<<"For drawing polygon left click for all the vertex and then right click,\n";
        cout<<"1) Press l to create line \n";
        cout<<"2) Press c to create circle \n";
        cout<<"3) Press p to create polygon\n";
        cout<<"4) Press n to clear all coordinates of selected figurine \n";
        cout<<"5) Press r to start rotation\n";
        cout<<"6) Press t to start translation\n";
        cout<<"7) Press m to start scale\n";
        cout<<"8) Press s to stop rotation\n";
        cout<<"9) Press i to print the instructions again\n";

    }
    else if (key == 'p'){

        curr_curve = 0;
        key_data.push_back(key);
        cout << "Polygon Selected" << endl;

    }
    else if (key == 'l'){

        curr_curve = 1;
        key_data.push_back(key);
        cout << "line Selected" << endl;

    }else if (key == 'c'){

        curr_curve = 2;
        key_data.push_back(key);
        cout << "circle Selected" << endl;

    }else if(key == 'n'){

        cout << "coordinates of requested figure cleared. " << endl;
        if(key_data.size()>=1 && key_data[key_data.size()-1]=='p') polygon_start=0;
        coordinates[curr_curve].clear();
        pinpoints[curr_curve].clear();

    }else if(key == 'r'){

        curr_motion= key;
        valid =1;
        cout<<"Rotation Selected"<<endl;
        cout<<"Left click to select the axis of rotation and then select second point to set base and then drag the pointer"<<endl;

    }else if(key == 't'){

        curr_motion= key;
        translation_valid =1;
        cout<<"Translation Selected"<<endl;
        cout<<"Left click on any point to translate then drag the pointer"<<endl;

    }else if(key == 'm'){

        curr_motion= key;
        Scaling_valid =1;
        cout<<"Scaling Selected"<<endl;
        cout<<"Left click on any point to scale then drag the pointer"<<endl;

    }else if(key == 's'){

        temporary_data.clear();
        select_axis=0;
        rotation_point=0;
        curr_motion= key;
        valid =0;
        Scaling_valid =0;
        translation_valid =0;
        cout<<"Transformations stopped"<<endl;
    }
}

void motion_func(int x,int y){

    x1 = x-len_half;
    y1 = -1*y +wid_half;

    if(valid){
        if(curr_motion == 'r'){
            ROTATE(x1,y1);
        }
    }else if(translation_valid){
        if(curr_motion == 't'){
            TRANSLATE(x1,y1);
        }
    }else if(Scaling_valid){
        if(curr_motion == 'm'){
            SCALE(x1,y1);
        }
    }
}

void IDLE_function(){
        plot();
        glFlush();
}

int main(int argc, char **argv) {

    cout<<"For drawing line left click for first point and last point and then right click,\n";
    cout<<"For drawing circle left click for center point and circumference point and then right click,\n";
    cout<<"For drawing polygon left click for all the vertex and then right click,\n";
    cout<<"1) Press l to create line \n";
    cout<<"2) Press c to create circle \n";
    cout<<"3) Press p to create polygon\n";
    cout<<"4) Press n to clear all coordinates of selected figurine \n";
    cout<<"5) Press r to start rotation\n";
    cout<<"6) Press t to start translation\n";
    cout<<"7) Press m to start scale\n";
    cout<<"8) Press s to stop rotation\n";
    cout<<"9) Press i to print the instructions again\n";

    for(int i=0;i<3;i++){
        coordinates.push_back(demo);
        pinpoints.push_back(demo);
    }

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(700,500);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	glutMouseFunc(OnMouseClick);
	glutMotionFunc(motion_func);
	glutKeyboardFunc(OnKeyboardClick);
	glutDisplayFunc(renderScene);
    glutIdleFunc(IDLE_function);
	glutMainLoop();
	return 1;
}










