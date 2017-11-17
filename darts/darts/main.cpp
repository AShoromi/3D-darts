#include <windows.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>
#define mmm 50

struct vertex3{ float x; float y; float z;};
struct vertex3 mass[2 * mmm + 1][mmm + 1];	// массив координат

void makeSphere( float r)
{
	int i, j;
	double a, b;
	float x, y, z;
		for(i = 0; i <= 2 * mmm; i++ ){
			for(j = 0; j <= 2 * mmm; j++){
				a = ((2 * M_PI) / (2 * mmm)) * i;
				b = (M_PI / mmm) * j;
						x = cos(a) * sin(b) * r;
						y = cos(b) * r;
						z = sin(a) * sin(b) * r;
						mass[i][j].x = x;
						mass[i][j].y = y;
						mass[i][j].z = z;
					}
				}
	}


void drow_sphere()
{
	int i, j;
	glBegin(GL_QUADS);
	for(i = 0; i < 2 * mmm; i++){
		for(j = 0; j < mmm; j++){
			glColor3f(0, 0, 1);
			glVertex3f(mass[i][j].x, mass[i][j].y, mass[i][j].z);
			glColor3f(1, 0, 1);
			glVertex3f(mass[i + 1][j].x, mass[i + 1][j].y, mass[i + 1][j].z);
			glColor3f(0, 1, 1);
			glVertex3f(mass[i + 1][j + 1].x, mass[i + 1][j + 1].y, mass[i + 1][j + 1].z);
			glColor3f(1, 1, 1);
			glVertex3f(mass[i][j + 1].x, mass[i][j + 1].y, mass[i][j + 1].z);
		}
	}
	glEnd();
}

void renderScene(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(50, 50, 50, 0, 0, 0, 0, 1, 0);
	glTranslatef(5, 2, 8);
	drow_sphere();
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
}	

void changeSize(int w, int h)
{
	if(h == 0)
	h = 1;
	float ratio = w * 1.0 / h; // число с плавающей точкой - НЕЦЕЛОЧИСЛЕННОЕ ДЕЛЕНИЕ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 0.1, 100); // 1 - угол обзора, 2 - высота : ширина, 3 - мин, 4 -кол
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //флаги: цвет | анимация | свет
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	makeSphere( 25);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}
	/** Сфера: 
	*	- отдельная функция, принимающая параметры: радиус сферы и точность для малого отрезка [- pi/2; + pi/2]
	*	- for(большой цикл){for(малый цикл){}} - генерация координат всех точек
	*  x = cos a * sin b * R
	*  y = cos b * R
	*  z = sin a * sin b * R
	* a c [0, 2pi], b c [-pi/2, pi/2] => 2pi/m, pi/m, m = const
	*	- генерация координт нормалей (для хранения - массивы)
	*	- генерация текстурных координат (генерация там, где точки)
	*	- генерация индексов 
	*	- отрисовка

	 массив индексов 
	* (i, j)
	* (i, j + 1)
	* (i + 1, j + 1)
	* (i + 1, j)
	*/
