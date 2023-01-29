/*
    Simple TinyGL program for the Amiga
    Tested with AmiKit
*/

#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

int counter = 0;

GLfloat copydiffColors[5][4] = { {0.5f, 0.5f, 0.9f, 1.0f},
                                 {0.9f, 0.5f, 0.5f, 1.0f},
                                 {0.5f, 0.9f, 0.3f, 1.0f},
                                 {0.3f, 0.8f, 0.9f, 1.0f},
                                 {0.5f, 0.5f, 0.9f, 1.0f} };

float angle = M_PI / 180.0f;

int colorRow = 0;

GLfloat red = 0.5f;
GLfloat green = 0.5f;
GLfloat blue = 0.9f;

float currentRed;
float currentGreen;
float currentBlue;

float radd, gadd, badd;

void init (GLvoid)
{
    GLfloat lightpos[4] = {-0.2F,0.2F,0.2F,0.0F};
    GLfloat lightamb[4] = {0.3F,0.3F,0.3F,1.0F};
    GLfloat lightdif[4] = {0.8F,0.8F,0.8F,1.0F};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightamb);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightdif);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


}

void draw(void)
{
    int i;
    float normal[3];

    GLfloat diffColor[4] = {red, green, blue, 1.0};

	// Define specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
	GLfloat Lt0pos[] = {1.0f, 1.0f, 5.0f, 1.0f};

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
	// Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &diffColor[0]);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

    glPushMatrix();

    glScalef(0.5f, 0.5f, 0.5f);
    
    glTranslatef(cos(angle / 100.0f), 0.0f, sin(angle / 100.0f) * 1.25f + 5.5f);
    
    
    glRotatef(angle, angle/2.0f, angle/4.0f, 0.0f);

    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.5f,-0.5f, -1.0f);
		glVertex3f(-0.5f,0.5f, -1.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f,0.5f, -1.0f);
        glVertex3f(0.5f,-0.5f, -1.0f);						
	glEnd();


    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 32; i++) {
        double Angle = 2*M_PI/32.0 * i;
        double y = cos(Angle);
        double z = sin(Angle);
        
        if (i % 2 == 0) {
            glNormal3f(1.0f, 0, 0);
        } else {
            glNormal3f(-1.0f, 0, 0);
        }
        glVertex3f(0, y, z);
    }
    glEnd();

	glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f,-0.5f,1.0f);
		glVertex3f(-0.5f,0.5f,1.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f,0.5f,1.0f);
        glVertex3f(0.5f,-0.5f,1.0f);
	glEnd();											
    
    glPopMatrix();

    glutSwapBuffers();
}

void idle(void) {

    angle += (M_PI / 180.0f) * 100.0f;

    currentRed = copydiffColors[colorRow][0];
    currentGreen = copydiffColors[colorRow][1];
    currentBlue = copydiffColors[colorRow][2];

    radd = -((currentRed - copydiffColors[colorRow + 1][0]) / 256.0);
    gadd = -((currentGreen - copydiffColors[colorRow+1][1]) / 256.0);
    badd = -((currentBlue - copydiffColors[colorRow+1][2]) / 256.0);

    red += radd;
    green += gadd;
    blue += badd;

    counter += 1;
    if (counter == 256) {
        colorRow += 1;
        if (colorRow == 4) colorRow = 0;
        counter = 0;
    }

	draw();
	glutPostRedisplay();
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(480, 480);
    glutCreateWindow("TinyGL experiment");
	init();
    glutDisplayFunc(draw);
    glutIdleFunc(idle);
    glutMainLoop();
	
	return 0;
}

