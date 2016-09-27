#include "modelViewer.h"
#include<iostream>
#include<cstdio>
#include <cstdlib>
#include <fstream>
#include <GL/freeglut.h>
#include <eigen3/Eigen/Core>
#include <vector>
#include <exception>
#include <cstring>

using namespace std;
using namespace Eigen;

typedef Vector3d Point;
typedef Vector3d Color;

GLsizei wh = 1000;
GLsizei ww = 1000;

//double pitch =0, yaw =0;
//double mouse_x, mouse_y;

//int mouse_button;
//double fovy=45, near=0, far=1000;
//double dist = -200;

Loader loader;

void Loader::Load(char* filename){
    char line[100];
    char tag[4];
    float x,y,z;
    char *pch;
    vector<int> faceIndex;
    int index;
    
    FILE* fp = fopen(filename, "r");
    V.push_back(Point(0,0,0));
    
    if(!fp){
        cout<< "Couldn't open the file!"<<endl;
        exit(1);
    }
    
    while(fgets(line, 100, fp)){
        switch(line[0]){
            case 'v':
                sscanf(line, "%s %f %f %f", tag, &x, &y, &z);
                V.push_back(Point(x,y,z));
                break;
            case 'f':
                pch = strtok (line," ");
                pch = strtok (NULL," ");
                while (pch != NULL)
                {
                    sscanf(pch, "%d", &index);
                    faceIndex.push_back(index);
                    pch = strtok (NULL, " ");
                }
                F.push_back(faceIndex);
                faceIndex.clear();
                break;
            default:
                break;
        }
    }
}

void Loader::Draw(){
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    for(int i=0, num = F.size(); i<num; ++i){
        for(int j=0, n = F[i].size(); j<n; ++j){
            glVertex3dv(V[F[i][j]].data());
            glVertex3dv(V[F[i][(j+1)%n]].data());
        }
    }
    glEnd();
}

void outObj(char* fileame){
  ofstream file;
  file.open(filename);
  
}

void keyboard(unsigned char c, int x, int y){
  switch(c){
  case 'w':
    outObj();
    break;
  
  }
  
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0,1.0,1.0,1.0);
  glLoadIdentity();
  
  glTranslated(0.0f, -2.75f, -5.0f);
  //glRotated(pitch, 1,0,0);
  //glRotated(yaw,0,1,0);
  
  loader.Draw();
  
  glFlush();
}

void reshape(int w, int h){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)w/(GLfloat)h, 1.0, 100);
  glMatrixMode(GL_MODELVIEW);
  //glTranslated(0,0,-200);
  //glRotated(45, 1,1,1);
  
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(ww, wh) ;
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  
  if(argc != 2){
    cout << "Invalid number of arguments" << endl;
  }
  
  loader.Load(argv[1]);
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape) ;
  glutKeyboardFunc(keyboard);
  glutMainLoop() ;
  return 0;
}

