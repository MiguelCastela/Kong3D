#pragma once

#include "ofMain.h"
#include "cg_extras.h"


//desenha ponto 3D na origem
inline void drawPoint() {
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
}

//desenha axis 3D
inline void axis3d() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

//função que desenha quadrado unitário 
//centrado na origem e preenchido
inline void rectFill_unit() {
	glBegin(GL_QUADS);
	glVertex3d(-0.5, -0.5, 0.);
	glVertex3d(-0.5, 0.5, 0.);
	glVertex3d(0.5, 0.5, 0.);
	glVertex3d(0.5, -0.5, 0.);
	glEnd();
}

//função que desenha malha unitária com resolução mxn
inline void malha_unit(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex2d(i * x_step + x_start, j * y_step + y_start);
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();
}


inline void cube_unit(GLfloat p) {
    // Draw the body of the cube (as quads)
    glBegin(GL_QUADS);

    // Front face
    glVertex3f(-p, -p, p);
    glVertex3f(-p, p, p);
    glVertex3f(p, p, p);
    glVertex3f(p, -p, p);

    // Back face
    glVertex3f(-p, -p, -p);
    glVertex3f(p, -p, -p);
    glVertex3f(p, p, -p);
    glVertex3f(-p, p, -p);

    // Bottom face
    glVertex3f(-p, -p, -p);
    glVertex3f(-p, -p, p);
    glVertex3f(p, -p, p);
    glVertex3f(p, -p, -p);

    // Top face
    glVertex3f(-p, p, p);
    glVertex3f(-p, p, -p);
    glVertex3f(p, p, -p);
    glVertex3f(p, p, p);

    // Left face
    glVertex3f(-p, -p, p);
    glVertex3f(-p, -p, -p);
    glVertex3f(-p, p, -p);
    glVertex3f(-p, p, p);

    // Right face
    glVertex3f(p, -p, p);
    glVertex3f(p, p, p);
    glVertex3f(p, p, -p);
    glVertex3f(p, -p, -p);

    glEnd();
}
inline void cube_unit_outline(GLfloat p) {
    glColor3f(0, 0, 0); // Set color to black for the outline
    glBegin(GL_LINES);

    // Front face edges
    glVertex3f(-p, -p, p); glVertex3f(p, -p, p);
    glVertex3f(p, -p, p); glVertex3f(p, p, p);
    glVertex3f(p, p, p); glVertex3f(-p, p, p);
    glVertex3f(-p, p, p); glVertex3f(-p, -p, p);

    // Back face edges
    glVertex3f(-p, -p, -p); glVertex3f(p, -p, -p);
    glVertex3f(p, -p, -p); glVertex3f(p, p, -p);
    glVertex3f(p, p, -p); glVertex3f(-p, p, -p);
    glVertex3f(-p, p, -p); glVertex3f(-p, -p, -p);

    // Connecting edges between front and back faces
    glVertex3f(-p, -p, p); glVertex3f(-p, -p, -p);
    glVertex3f(p, -p, p); glVertex3f(p, -p, -p);
    glVertex3f(p, p, p); glVertex3f(p, p, -p);
    glVertex3f(-p, p, p); glVertex3f(-p, p, -p);

    glEnd();
}

//funcao que desenha cubo unit�rio com malha_unit()
inline void cube_malha_unit(GLint m, GLint n) {


	//tras
	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslated(0., 0., -0.5);
	glRotated(180, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//cima
	glColor3f(0, 1, 1);
	glPushMatrix();
	glTranslated(0., -0.5, 0.);
	glRotated(90, 1, 0, 0);
	malha_unit(m, n);
	glPopMatrix();

	//baixo
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(0., 0.5, 0.);
	glRotated(-90, 1, 0, 0);
	malha_unit(m, n);
	glPopMatrix();

	//esquerda
	glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslated(-0.5, 0., 0.);
	glRotated(-90, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//direita
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(0.5, 0., 0.);
	glRotated(90, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//frente
	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslated(0., 0., 0.5);
	malha_unit(m, n);
	glPopMatrix();


}
