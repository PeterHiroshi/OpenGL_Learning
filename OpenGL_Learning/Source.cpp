#include "Header.h"
#include <math.h>

//#define USE_PERSPECTIVE
//#define USE_ANTIALIAS

#define PI 3.1415926535898

int win_width = 300;
int win_height = 300;
const int RANGE = 2;
const int WIN_POS_X = 50;
const int WIN_POS_Y = 50;
//const unsigned int DISPLAY_MODE = GLUT_SINGLE | GLUT_RGB;
//const GLbitfield CLEAR_MASK = GL_COLOR_BUFFER_BIT;
const unsigned int DISPLAY_MODE = GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL;
const GLbitfield CLEAR_MASK = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
extern const string FILE_ROOT_PATH = "bvh_files";


//settings for camera and target
static double camera_pos[3] = { 0.0, 0.0, 100.0 };
//static double camera_pos[3] = { 50.0, 0.0, 0.0 };
static double target_pos[3] = { 0.0, 0.0, 0.0 };
static double upDir[3] = { 0.0, 1.0, 0.0 };
static double range = 80.0;
static double z_near = camera_pos[2] - 5;
static double z_far = -100.0;

GLbyte* pixels;
vector<std::string> my_file_name_list;

vector<Mat> mat_list;

//global rotation
float rot_x_angle = 0.0f;
float rot_y_angle = 0.0f;
float rot_z_angle = 0.0f;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(DISPLAY_MODE);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	glutCreateWindow("opengl learning demos");


	//callback functions register
	//glutDisplayFunc(Display1);
	//glutDisplayFunc(Display3);
	//glutDisplayFunc(Display4);
	//glutDisplayFunc(Display5);
	//glutDisplayFunc(Display6);
	//glutDisplayFunc(Display7);
	//glutDisplayFunc(Display8);
	glutDisplayFunc(Display9);
	glutReshapeFunc(Reshape3);
	glutKeyboardFunc(Keyboard); 

	//initialize environment
	//EnvironmentInit();
	//EnvironmentInit3D();
	EnvironmentInit3D_2();

	//SaveAsImg();

	if (pixels != NULL)
		delete[] pixels;

	//main loop
	glutMainLoop();
	
	return 0;
}

void EnvironmentInit()
{
	//set the color of display window to (1.0,1.0,1.0)
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void EnvironmentInit3D()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	//glOrtho(-100.0, 100.0, -100.0, 100.0, 10.0, 125.0);
	glFrustum(-100.0, 100.0, -100.0, 100.0, 20.0, 125.0);

}

void EnvironmentInit3D_2()
{
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearColor(1.0, 1.0, 1.0, 0.0);

}

void Display1()
{
	vector<MyVertex> vertices = { MyVertex(-50.0f, -25.0f), MyVertex(50.0f, -25.0f), 
		MyVertex(0.0f, 50.0f) };
	glClear(GL_COLOR_BUFFER_BIT); //clear display window

	glColor3f(0.0f, 0.0f, 1.0f);
	glViewport(0, 0, (win_width/2), win_height);
	TriangleDraw(vertices);

	//begin rotate
	glColor3f(1.0f, 0.0f, 0.0f);
	glViewport((win_width/2), 0, (win_width/2), win_height);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	TriangleDraw(vertices);

	glFlush();

}

void Display2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);

	glColor3f(0.0f, 0.0f, 1.0f); //set to blue
	glRecti(-50, -50, 50, 50);

	glColor3f(1.0f, 0.0f, 0.0f); //set to red
	glTranslatef(-50.0f, -50.0f, 0.0f);
	glRecti(-50, -50, 50, 50);

	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRecti(-50, -50, 50, 50);

	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glRecti(-50, -50, 50, 50);

	glFlush();
}

void Display3()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glColor3f(0.0f, 0.0f, 1.0f); //set to blue
	glRecti(-50, -50, 50, 50);

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f); //set to red
	glTranslatef(-50.0f, -50.0f, 0.0f);
	glRecti(-50, -50, 50, 50);

	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRecti(-50, -50, 50, 50);

	glPopMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glRecti(-50, -50, 50, 50);

	glFlush();
}

void Display4()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	float z_obj = 20.0f;

	glBegin(GL_QUADS); {
		glVertex3f(-50.0f, -50.0f, z_obj + 10.0f);
		glVertex3f(50.0f, -50.0f, z_obj - 10.0f);
		glVertex3f(50.0f, 50.0f, z_obj - 10.0f);
		glVertex3f(-50.0f, 50.0f, z_obj + 10.0f);
	}
	glEnd();

	glFlush();
}

void Display5()
{
	glClear(CLEAR_MASK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
		target_pos[0], target_pos[1], target_pos[2], 0.0, 1.0, 0.0);

	glPushMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);
	//glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
	//glRotatef(15.0f, 0.0f, 0.0f, -1.0f);
	//glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

	//rotation with keyboard
	//x-axis rotation
	glRotatef(rot_x_angle, 1.0f, 0.0f, 0.0f);
	//y-axis rotation
	glRotatef(rot_y_angle, 0.0f, 1.0f, 0.0f);
	//z-axis rotation
	glRotatef(rot_z_angle, 0.0f, 0.0f, 1.0f);

	glutWireCube(20.0);

	glPopMatrix();

	glutSwapBuffers();

}

void Display6()
{
	GLfloat x, y, z = 0.0f, inc = 0, angle;

	glClear(CLEAR_MASK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
		target_pos[0], target_pos[1], target_pos[2],
		0.0, 1.0, 0.0);

	glPushMatrix(); {
		glColor3f(0.0f, 1.0f, 0.0f);   
		glTranslatef(0.0f, -50.0f, 0.0f);
		glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
		//glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
		glBegin(GL_POINTS); {
			for (angle = 0.0f; angle <= 2.0f * 3.14159f * 3.0f; angle += 0.1f) {
				x = inc * sin(angle);           //计算点的X坐标  
				y = inc * cos(angle);           //计算点的Y坐标  
				glVertex3f(x, y, z);            //绘制点  
				z += 0.5f;                      //Z坐标增量  
				inc += 0.3f;                    //半径增量  
			}
		}
		glEnd();

		//glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
		//glutWireCube(2.0f);

	}
	glPopMatrix();

	glutSwapBuffers();
}

void Display7()
{
	glClear(CLEAR_MASK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
		target_pos[0], target_pos[1], target_pos[2],
		upDir[0], upDir[1], upDir[2]);

	GLUquadric* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glColor3f(0.0f, 1.0f, 0.0f);
	gluCylinder(qobj, 10.0, 20.0, 30.0, 10, 4);

	glutSwapBuffers();
}

void Display8()
{
	glClear(CLEAR_MASK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
		target_pos[0], target_pos[1], target_pos[2],
		upDir[0], upDir[1], upDir[2]);

	//begin drawing
	glColor3f(0.0f, 1.0f, 0.0f);
	DrawCylinder(-50.0f, 0.0f, 0.0f, 20.0f, 20.0f, 50.0f);
	glPushMatrix(); {
		glTranslatef(0.0f, -50.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		DrawCylinder(-50.0f, 0.0f, 0.0f, 20.0f, 20.0f, -50.0f);
	}
	glPopMatrix();

	glutSwapBuffers();
}

void Display9()
{

#ifdef USE_ANTIALIAS
	glEnable(GL_DEPTH_TEST);
	glPointSize(8);
	glLineWidth(5);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif // USE_ANTIALIAS

	glClear(CLEAR_MASK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
		target_pos[0], target_pos[1], target_pos[2],
		upDir[0], upDir[1], upDir[2]);

	//begin drawing
	glTranslatef(-15.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	DrawCylinder(-50.0f, -10.0f, -50.0f, 10.0f, 10.0f, 50.0f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	DrawJointPair(-50.0f, -10.0f, -50.0f, 5.0, 10.0f, 10.0f, 50.0f, 10.0);

	SaveAsImg();

	glutSwapBuffers();
	//glFlush();
}

void DrawCylinder(float x0, float y0, float z0, float x1, float y1, float z1)
{
	double baseRadius = 5.0;
	double topRadius = 10.0;
	double height = 0.0;
	double tmp_len = 0.0;
	int slices = 10;
	int stacks = 4;
	GLUquadric* qObj = NULL;
	if (qObj == NULL)
		qObj = gluNewQuadric();

	double dir_x = x1 - x0;
	double dir_y = y1 - y0;
	double dir_z = z1 - z0;
	tmp_len = height = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);

	double front_x = 0.0;
	double front_y = 0.0;
	double front_z = 1.0;

	glPushMatrix(); {
		//begin translate
		glTranslatef(x0, y0, z0);

		//direction normalization
		if (tmp_len < 0.0001) {
			dir_x = 0.0;
			dir_y = 0.0;
			dir_z = 1.0;
			tmp_len = 1.0;
		}
		dir_x /= tmp_len;
		dir_y /= tmp_len;
		dir_z /= tmp_len;

		//calculate normal vector and normalization
		double normal_x = front_y*dir_z - front_z*dir_y;
		double normal_y = front_z*dir_x - front_x*dir_z;
		double normal_z = front_x*dir_y - front_y*dir_x;
		tmp_len = sqrt(normal_x*normal_x + normal_y*normal_y + normal_z*normal_z);
		if (tmp_len < 0.0001) {
			normal_x = 1.0;
			normal_y = 0.0;
			normal_z = 0.0;
			tmp_len = 1.0;
		}
		normal_x /= tmp_len;
		normal_y /= tmp_len;
		normal_z /= tmp_len;

		//calculate angle
		float angle = acos(front_x*dir_x + front_y*dir_y + front_z*dir_z) * 180.0f / PI;

		//begin rotate
		glRotatef(angle, normal_x, normal_y, normal_z);

		gluQuadricDrawStyle(qObj, GLU_FILL);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluCylinder(qObj, baseRadius, topRadius, height, slices, stacks);
	}
	glPopMatrix();
}

void DrawJointPair(float x0, float y0, float z0, double radius0, float x1, float y1, float z1,
	double radius1)
{
	GLUquadric* joint = NULL;

	if (joint == NULL)
		joint = gluNewQuadric();

	double slices = 10.0;
	double stacks = 10.0;

	//first joint
	glPushMatrix(); {
		glTranslatef(x0, y0, z0);
		gluQuadricDrawStyle(joint, GLU_FILL);
		gluQuadricNormals(joint, GLU_SMOOTH);
		gluSphere(joint, radius0, slices, stacks);
	}
	glPopMatrix();
	//second joint
	glPushMatrix(); {
		glTranslatef(x1, y1, z1);
		gluQuadricDrawStyle(joint, GLU_FILL);
		gluQuadricNormals(joint, GLU_SMOOTH);
		gluSphere(joint, radius1, slices, stacks);
	}
	glPopMatrix();

}

void Reshape(int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
	win_width = new_width;
	win_height = new_height;
}

void Reshape2(int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);

	glMatrixMode(GL_PROJECTION);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 20, 100);
	glMatrixMode(GL_MODELVIEW);

	win_width = new_width;
	win_height = new_height;

}

void Reshape3(int new_width, int new_height)
{
	//float aspect = (float)new_width / (float)new_height;
	
	glViewport(0, 0, new_width, new_height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef USE_PERSPECTIVE
	glFrustum(-range, range, -range, range, -z_near + camera_pos[2], -z_far + camera_pos[2]);
#else
	glOrtho(-range, range, -range, range, -z_near+camera_pos[2], -z_far+camera_pos[2]);
#endif // USE_PERSPECTIVE

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	win_width = new_width;
	win_height = new_height;

}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'f') {
		LoadFilePathList(FILE_ROOT_PATH, my_file_name_list);

		/*for (vector<string>::const_iterator iter = file_name_list.begin();
			iter != file_name_list.end(); ++iter) {
			cout << *iter << endl;
		}
		cout << endl << "file nummber = " << file_name_list.size() << endl;*/
		while (my_file_name_list.size() != 0) {
			cout << my_file_name_list[my_file_name_list.size() - 1] << endl;
			my_file_name_list.pop_back();
		}
	}
	else if (key == 'k') {
		string dstPath;
		PathConvert(srcPath, dstRoot, dstPath);
		cout << dstPath << endl;
	}
	else if (key == 'a') {
		rot_x_angle += 15.0f;
		if (rot_x_angle >= 360.0f)
			rot_x_angle = 0.0f;
	}
	else if (key == 's') {
		rot_y_angle += 15.0f;
		if (rot_y_angle >= 360.0f)
			rot_y_angle = 0.0f;
	}
	else if (key == 'd') {
		rot_z_angle += 15.0f;
		if (rot_z_angle >= 360.0f)
			rot_z_angle = 0.0f;
	}

	//begin re-display
	glutPostRedisplay();

}

void TriangleDraw(vector<MyVertex> vertices)
{
	glBegin(GL_TRIANGLES);
	for (vector<MyVertex>::const_iterator iter = vertices.begin();
		iter != vertices.end(); ++iter) {
		glVertex2f(iter->x, iter->y);
	}
	glEnd();
}

void saveColorData(bytePt& _pt, string& _str) {
	FILE* pFile = NULL;
	//pFile = fopen(_str.c_str(), "wt");

	fopen_s(&pFile, _str.c_str(), "wt");
	if (!pFile) { fprintf(stderr, "error \n"); exit(-1); }


	for (int i = 0; i<win_width * win_height * 3; i++) {
		if (pixels[i] == -1) { pixels[i] = 255; }
	}


	for (int i = 0; i<win_width * win_height * 3; i++) {
		fprintf(pFile, "%d\n", pixels[i]);
	}

	fclose(pFile);
	printf("color data saved! \n");
}

Mat saveColorData2img(bytePt& pixels) {
	cv::Mat img;
	vector<cv::Mat> imgPlanes(1000);
	img.create(win_height, win_width, CV_8UC3);
	cv::split(img, imgPlanes);


	for (int i = 0; i < win_height; i++) {
		uchar* plane0Ptr = imgPlanes[0].ptr<uchar>(i);
		uchar* plane1Ptr = imgPlanes[1].ptr<uchar>(i);
		uchar* plane2Ptr = imgPlanes[2].ptr<uchar>(i);
		for (int j = 0; j < win_width; j++) {
			int k = 3 * (i * win_width + j);
			plane2Ptr[j] = pixels[k];
			plane1Ptr[j] = pixels[k + 1];
			plane0Ptr[j] = pixels[k + 2];
		}
	}
	cv::merge(imgPlanes, img);
	cv::flip(img, img, 0); // !!!
	//cv::imwrite(_str.c_str(), img);
	//cv::imshow("show", img);
	//printf("opencv save opengl img done! \n");

	return img;
}

void SaveAsImg()
{
	int viewPort[4] = { 0 };
	pixels = new GLbyte[win_width * win_height * 3];
	glGetIntegerv(GL_VIEWPORT, viewPort);
	glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_RGB, GL_UNSIGNED_BYTE,
		pixels);
	saveColorData(pixels, (string)"tmpcolor.txt");
	string path = "color.bmp";
	
	Mat imageMat;
	//Mat imageAdjusted;
	Mat imageMatFlip;

	imageMat = saveColorData2img(pixels);

	//to adjust the object into the image be centered
	ImgAdjust(imageMat, imageMat);

	imshow("adj", imageMat);

	flip(imageMat, imageMatFlip, 1);

	//we push 10 image mats, 5 unflipped and 5 flipped
	int count = 5;
	for (int i = 0; i < count; ++i) {
		mat_list.push_back(imageMat);
		mat_list.push_back(imageMatFlip);
	}

	//for (int i = 0; i < mat_list.size(); ++i) {
	//	ostringstream oss;
	//	oss << "win" << i;
	//	imshow(oss.str(), mat_list.at(i));
	//}

	SaveAsImgList(mat_list, path);

	for (int i = 0; i < 60; ++i) {
		cout << (int)pixels[i] << ", ";
	}
	cout << endl;
	
	//Mat testImg = imread("4.bmp");
	//imshow("test", testImg);

	mat_list.clear();

}

void LoadFilePathList(string rootPath, vector<string>& list)
{
	string p;
	struct _finddata_t findData;
	intptr_t hFile;

	if ((hFile = _findfirst(p.assign(rootPath).append("\\*").c_str(), &findData)) != -1) {
		do {

			//when meet a sub directory
			if (findData.attrib & _A_SUBDIR) {
				if ((strcmp(findData.name, ".") != 0) && (strcmp(findData.name, "..") != 0)) {
					LoadFilePathList(p.assign(rootPath).append("\\").append(findData.name), list);
				}
			}
			//when meet a file
			else {
				list.push_back(p.assign(rootPath).append("\\").append(findData.name));
			}

		} while (_findnext(hFile, &findData) == 0);
		_findclose(hFile);
	}

}

string srcPath = "bvh_files\\walk\\walk_000.bvh";
string dstRoot = "image_output";

void PathConvert(const string& srcPath, const string& dstRoot, string& dstPath)
{
	dstPath.assign(srcPath);
	int pos = dstPath.find_first_of('\\');
	dstPath.replace(0, pos, dstRoot);
	pos = dstPath.find('.');
	dstPath.replace(pos+1, dstPath.length(), "bmp");
}

void SaveAsImgList(vector<Mat>& matList, string path)
{

#ifdef SAVE_AS_ONE_ROW
	//save as one row
	int _rows = matList[0].rows;
	int _cols = matList[0].cols * (matList.size());
#else
	//save as two rows
	int _rows = matList[0].rows*2;
	int _cols = matList[0].cols * (matList.size() / 2);
#endif // SAVE_AS_ONE_ROW

	int _type = matList[0].type();

	Mat imgList;
	imgList.create(_rows, _cols, _type);

#ifdef SAVE_AS_ONE_ROW
	//save as one row
	for (int i = 0; i < matList.size(); ++i) {
		Mat tmpMat = matList[i]; //tmpMat is the basic mat from matList
		tmpMat.colRange(0, tmpMat.cols).copyTo(imgList.colRange(i*tmpMat.cols, (i + 1)*tmpMat.cols));
	}
#else
	//save as two rows

	Mat tmpMat;
	Mat imgROI;
	//first row
	for (int i = 0, j=0; i < matList.size(); i += 2, j++) {
		tmpMat = matList[i]; //tmpMat is the basic mat from matList
		//tmpMat.colRange(0, tmpMat.cols).copyTo(imgList.colRange(j*tmpMat.cols, (j + 1)*tmpMat.cols));

		imgROI = imgList(Rect(j*tmpMat.cols, 0, tmpMat.cols, tmpMat.rows));
		tmpMat.colRange(0, tmpMat.cols).copyTo(imgROI);

	}
	//second row
	for (int i = 1, j = 0; i < matList.size(); i += 2, j++) {
		tmpMat = matList[i]; //tmpMat is the basic mat from matList
			
		imgROI = imgList(Rect(j*tmpMat.cols, tmpMat.rows, tmpMat.cols, tmpMat.rows));
		tmpMat.colRange(0, tmpMat.cols).copyTo(imgROI);

	}

#endif // SAVE_AS_ONE_ROW

	imshow("imglist", imgList);
	imwrite(path, imgList);

}

void ImgAdjust(Mat src, Mat& dst)
{
	//imshow("test", src);

	vector<Mat> contours(10000);
	vector<Vec4i> hierarchy(10000);

	Mat src_gray, src_binary;
	Mat src_contoured;
	Mat result;

	cvtColor(src, src_gray, CV_BGR2GRAY);
	threshold(src_gray, src_binary, 127, 255, CV_THRESH_BINARY);
	src_binary.copyTo(src_contoured);
	
	//find contours
	findContours(src_contoured, contours, hierarchy, CV_RETR_CCOMP,
		CV_CHAIN_APPROX_NONE, Point(0, 0));

	cout << "size = " << contours.size() << endl;

	int contourIdx = -1;

	for (int i = 0; i < contours.size(); ++i) {
		double g_dConArea = contourArea(contours[i], true);

		//cout << "area" << i << " = " << g_dConArea << endl;
		if (g_dConArea > 0)
			contourIdx = i;
	}

	//get bounding rectangle
	Mat contour_poly;
	Rect boundRect;
	approxPolyDP(contours[contourIdx], contour_poly, 3, true);
	boundRect = boundingRect(contour_poly);

	result = Mat::zeros(src_binary.size(), CV_8UC3);
	drawContours(result, contours, contourIdx, Scalar(255, 0, 255));
	//rectangle(result, boundRect.tl(), boundRect.br(), Scalar(0, 255, 255), 2, 8, 0);

	//cout << boundRect.tl().x << ", " << boundRect.tl().y << " || ";
	//cout << boundRect.br().x << ", " << boundRect.br().y << endl;

	//get target rectangle which is a little bigger than bound rectangle
	//should make sure that the rectangle is into the source image
	int bigger_offset = 5;
	int tl_x = boundRect.tl().x - bigger_offset <= 0 ? 0 :
		boundRect.tl().x - bigger_offset;
	int tl_y = boundRect.tl().y - bigger_offset <= 0 ? 0 : 
		boundRect.tl().y - bigger_offset;
	int _width = boundRect.width + bigger_offset * 2;
	int _height = boundRect.height + bigger_offset * 2;

	if (tl_x + _width >= src_binary.cols)
		_width = src_binary.cols - tl_x;
	if (tl_y + _height >= src_binary.rows)
		_height = src_binary.rows - tl_y;

	//make target rectangle
	Rect targetRect(tl_x, tl_y, _width, _height);

	//imshow("roi", img_target);
	//rectangle(result, targetRect.tl(), targetRect.br(), Scalar(0, 255, 255), 2, 8, 0);
	//cout << targetRect.tl().x << ", " << targetRect.tl().y << " || ";
	//cout << targetRect.br().x << ", " << targetRect.br().y << endl;

	//imshow("bi", src_binary);
	//imshow("res", src_contoured);
	//imshow("result", result);

	Mat img_target = src(targetRect);
	Mat dstImg(src.size(), src.type(), Scalar(255, 255, 255));
	
	int ctr_x = dstImg.cols / 2;
	int ctr_y = dstImg.rows / 2;
	Mat imgROI = dstImg(Rect(ctr_x - img_target.cols / 2, ctr_y - img_target.rows / 2,
		img_target.cols, img_target.rows));
	img_target.copyTo(imgROI);
	//imshow("dst", dstImg);

	dst = dstImg;

}
