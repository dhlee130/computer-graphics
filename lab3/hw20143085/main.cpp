// hello_world.cpp
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "vec.hpp"
#include "mat.hpp"
#include "transform.hpp"

void init();
void mydisplay();
void myidle();

float position[16] = {
	0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f,
};
float color[16];
int offset = 5;
int sqnum = 2;
bool change = true;
int level = 5;


GLuint create_shader_from_file(const std::string& filename, GLuint shader_type);

GLuint program; // 쉐이더 프로그램 객체의 레퍼런스 값
GLint  loc_a_position;
GLint  loc_a_color;
GLint  loc_u_Model;
float dx, dy;

std::vector<std::vector<std::pair<float, float>>> locate;


void hilbertPoint(float x0, float y0, float xx, float xy, float yx, float yy, int n) {


	if (n > 0) {
		float x1 = x0 + xx + yx; float y1 = y0 + xy + yy;
		float x2 = x0 + xx + 3 * yx; float y2 = y0 + xy + 3 * yy;
		float x4 = x0 + 3 * xx + yx; float y4 = y0 + 3 * xy + yy;
		float x3 = x0 + 3 * xx + 3 * yx; float y3 = y0 + 3 * xy + 3 * yy;

		std::pair<float, float> p1 = std::make_pair(x1, y1);
		locate[6 - n].push_back(p1);
		std::pair<float, float> p2 = std::make_pair(x2, y2);
		locate[6 - n].push_back(p2);
		std::pair<float, float> p3 = std::make_pair(x3, y3);
		locate[6 - n].push_back(p3);
		std::pair<float, float> p4 = std::make_pair(x4, y4);
		locate[6 - n].push_back(p4);

		hilbertPoint(x0 + 2 * yx, y0 + 2 * yy, -yx / 2, -yy / 2, xx / 2, xy / 2, n - 1);
		hilbertPoint(x0 + 2 * yx, y0 + 2 * yy, xx / 2, xy / 2, yx / 2, yy / 2, n - 1);
		hilbertPoint(x0 + 2 * xx + 2 * yx, y0 + 2 * xy + 2 * yy, xx / 2, xy / 2, yx / 2, yy / 2, n - 1);
		hilbertPoint(x0 + 4 * xx, y0 + 4 * xy, yx / 2, yy / 2, -xx / 2, -xy / 2, n - 1);
	}
}

void shuffle() {
	std::pair<float, float> temp;
	int n;
	for (int i = 0; i < 6; i++) {
		int e = locate[i].size();
		for (int j = 0; j < e; j++) {
			n = rand() % (e - 1);
			temp = locate[i][j];
			locate[i][j] = locate[i][n];
			locate[i][n] = temp;
		}
	}
}

void inputColor() {

	float c1 = rand() / (float)RAND_MAX * 1.0f;
	float c2 = rand() / (float)RAND_MAX * 1.0f;
	float c3 = rand() / (float)RAND_MAX * 1.0f;

	for (int loop = 0; loop < 16; loop += 4) {
		color[loop] = c1;
		color[loop + 1] = c2;
		color[loop + 2] = c3;
		color[loop + 3] = 1.0f;
	}
}

void drawSquare(kmuvcl::math::mat4x4f scale, kmuvcl::math::mat4x4f trans) {
	kmuvcl::math::mat4x4f  model_matrix;
	inputColor();

	model_matrix = trans * scale;

	glUniformMatrix4fv(loc_u_Model, 1, GL_FALSE, model_matrix);

	glVertexAttribPointer(loc_a_position, 4, GL_FLOAT, GL_FALSE, 0, position);
	glVertexAttribPointer(loc_a_color, 4, GL_FLOAT, GL_FALSE, 0, color);

	glEnableVertexAttribArray(loc_a_position);
	glEnableVertexAttribArray(loc_a_color);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(loc_a_position);
	glDisableVertexAttribArray(loc_a_color);
}

void drawSquareSet(int offset, kmuvcl::math::mat4x4f scale ,kmuvcl::math::mat4x4f trans) {
	float offval = 1.0f / offset;
	drawSquare(scale, trans);
	for (int loop = 1; loop < offset; loop++) {
		kmuvcl::math::mat4x4f inscale = scale * kmuvcl::math::scale(1.0f - (loop*offval), 1.0f - (loop*offval), 0.0f);
		drawSquare(inscale, trans);
	}
}

void drawNlevel(int level, int num, float l) {

	for (int loop = 0; loop < num; loop++) {
		kmuvcl::math::mat4x4f scale = kmuvcl::math::scale(l, l, 1.0f);
		kmuvcl::math::mat4x4f trans = kmuvcl::math::translate(locate[level][loop].first, locate[level][loop].second, 0.0f);
		drawSquareSet(offset, scale, trans);
	}
}

void drawHilSquare() {
	
	float l[] = { 0.0f, 0.8f, 0.6f, 0.4f, 0.15f, 0.05f };
	for (int loop = 1; loop <= level; loop++) {
		drawNlevel(loop - 1, pow(loop, sqnum) + 3 * loop, l[loop]);
	}
	
}

void myMainMenu(int entry) {
	if (entry == 1) {
		offset = 3; change = true;
	}
	else if (entry == 2) {
		offset = 5; change = true;
	}
	else if (entry == 3) {
		offset = 7; change = true;
	}
	else if (entry == 4) {
		level = 3; change = true;
	}
	else if (entry == 5) {
		level = 4; change = true;
	}
	else if (entry == 6) {
		level = 5; change = true;
	}
	else if (entry == 7) {
		sqnum = 1; change = true;
	}
	else if (entry == 8) {
		sqnum = 2; change = true;
	}
	else if (entry == 9) {
		sqnum = 3; change = true;
	}
	else if (entry == 10) {
		shuffle(); change = true;
	}


	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Hello FreeGLUT");
	srand(time(NULL));
	init();

	GLint myMainMenuID = glutCreateMenu(myMainMenu);
	glutAddMenuEntry("square in set = 3", 1);
	glutAddMenuEntry("square in set = 5", 2);
	glutAddMenuEntry("square in set = 7", 3);
	glutAddMenuEntry("HilbertLevel = 3", 4);
	glutAddMenuEntry("HilbertLevel = 4", 5);
	glutAddMenuEntry("HilbertLevel = 5", 6);
	glutAddMenuEntry("square in N level = n+3n", 7);
	glutAddMenuEntry("square in N level = n^2+3n", 8);
	glutAddMenuEntry("square in N level = n^3+3n", 9);
	glutAddMenuEntry("Relocate square", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(mydisplay);
	
	glutMainLoop();

	return 0;
}


// GLSL 파일을 읽어서 컴파일한 후 쉐이더 객체를 생성하는 함수
GLuint create_shader_from_file(const std::string& filename, GLuint shader_type)
{
	GLuint shader = 0;
	shader = glCreateShader(shader_type);
	std::ifstream shader_file(filename.c_str());
	std::string shader_string;
	shader_string.assign(
		(std::istreambuf_iterator<char>(shader_file)),
		std::istreambuf_iterator<char>());

	const GLchar* shader_src = shader_string.c_str();

	glShaderSource(shader, 1, (const GLchar**)&shader_src, NULL);
	glCompileShader(shader);

	return shader;
}


void init()
{
	glewInit();

	// 정점 쉐이더 객체를 파일로부터 생성
	GLuint vertex_shader
		= create_shader_from_file("./shader/vertex.glsl", GL_VERTEX_SHADER);

	// 프래그먼트 쉐이더 객체를 파일로부터 생성
	GLuint fragment_shader
		= create_shader_from_file("./shader/fragment.glsl", GL_FRAGMENT_SHADER);

	// 쉐이더 프로그램 생성 및 컴파일
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	loc_a_position = glGetAttribLocation(program, "a_position");
	loc_a_color = glGetAttribLocation(program, "a_color");
	loc_u_Model = glGetUniformLocation(program, "u_Model");
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	for (int i = 0; i < 6; i++) {
		std::vector<std::pair<float, float>> p;
		locate.push_back(p);
	}

	hilbertPoint(-1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 0.5f, 6);

	shuffle();

	
}

void mydisplay()
{
	if (change) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);


		drawHilSquare();



		glUseProgram(0);

		glutSwapBuffers();
		change = false;
	}
}

