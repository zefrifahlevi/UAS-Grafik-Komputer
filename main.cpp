#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// sudut rotasi untuk arah kamera
float angle = 0.0f;
// vektor sebenarnya mewakili arah kamera
float lx = 0.0f, lz = -1.0f;
// Posisi XZ kamera
float x = 0.0f, z = 5.0f;
// status kuncinya. Variabel-variabel ini akan menjadi nol
//saat tidak ada tombol yang ditekan
float deltaAngle = 0.0f;
float deltaMove = 0;

void changeSize(int w, int h) {

	// Cegah pembagian dengan nol, ketika jendela terlalu pendek
	// (tidak dapat membuat jendela dengan lebar nol).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Gunakan Matriks Proyeksi
	glMatrixMode(GL_PROJECTION);

	// Setel Ulang Matriks
	glLoadIdentity();

	// Atur area pandang menjadi keseluruhan jendela
	glViewport(0, 0, w, h);

	// Tetapkan perspektif yang benar.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Kembali ke Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawTeapot() {

	glColor3f(0.0f, 1.0f, 1.0f);

	glutWireTeapot(1);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

	void renderScene(void) {

		if (deltaMove)
			computePos(deltaMove);
		if (deltaAngle)
			computeDir(deltaAngle);

		// Hapus Warna dan Buffer Kedalaman
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Setel ulang transformasi
		glLoadIdentity();
		// Atur kamera
		gluLookAt(x, 1.0f, z,
			x + lx, 1.0f, z + lz,
			0.0f, 1.0f, 0.0f);

		glColor3f(0.6f, 0.6f, 0.6f);
		glBegin(GL_QUADS);
		/*
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
		*/
		glEnd();

		// Menggambar Teko

		for (int i = -9; i < 9; i++)
			for (int j = -9; j < 9; j++) {
				glPushMatrix();
				//glTranslatef(i*10.0, 0, j * 10.0);
				drawTeapot();
				glPopMatrix();
			}

		glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_LEFT: deltaAngle = -0.1f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.1f; break;
	case GLUT_KEY_UP: deltaMove = 1.0f; break;
	case GLUT_KEY_DOWN: deltaMove = -1.0f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}

int main(int argc, char **argv) {

	// inisiasi GLUT dan buat jendela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("UAS | Grafik Komputer | 2206068 Zefri Fahlevi Irdiansyah INF-B");

	// mendaftarkan panggilan balik
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutSpecialFunc(pressKey);

	// ini entri baru
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	// OpenGL inisiasi
	glEnable(GL_DEPTH_TEST);

	// masuk ke siklus pemrosesan acara GLUT
	glutMainLoop();

	return 1;
}