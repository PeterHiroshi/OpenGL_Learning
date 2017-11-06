#pragma once

//include files
#include <GL\glut.h>
#include <io.h>
#include <fstream>
#include <iostream>
//#include <string>
#include <vector>

//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>

//libaries
#pragma comment(lib, "glut32.lib")


using namespace std;
using namespace cv;

//global settings
extern int win_width;
extern int win_height;
extern const int RANGE;
extern const unsigned int DISPLAY_MODE;
extern const int WIN_POS_X;
extern const int WIN_POS_Y;
extern const string FILE_ROOT_PATH;

//structures
class MyVertex
{
public:
	MyVertex(GLfloat x, GLfloat y) :
		x(x), y(y) {}
	GLfloat x, y;
};

typedef GLbyte* bytePt;

//functions for opengl
void EnvironmentInit();
void EnvironmentInit3D();
void EnvironmentInit3D_2();
void Display1();
void Display2();
void Display3();
void Display4();
void Display5(); //display cube
void Display6(); //display points
void Display7(); //display cylinder
void Display8(); //display cylinder 2
void Display9(); //display joint pair and cylinder
void DrawCylinder(float x0, float y0, float z0, float x1, float y1, float z1);
void DrawJointPair(float x0, float y0, float z0, double radius0, float x1, float y1, float z1,
	double radius1);
void Reshape(int new_width, int new_height);
void Reshape2(int new_width, int new_height);
void Reshape3(int new_width, int new_height);

void Keyboard(unsigned char key, int x, int y);

void TriangleDraw(vector<MyVertex> vertices);
Mat saveColorData2img(bytePt& pixels);
void SaveAsImg();
void SaveAsImgList(vector<Mat>& matList, string path);
void LoadFilePathList(string rootPath, vector<string>& list);
void PathConvert(const string& srcPath, const string& dstRoot, string& dstPath);

extern string srcPath;
extern string dstRoot;

//#define SAVE_AS_ONE_ROW
