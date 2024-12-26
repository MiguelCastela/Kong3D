#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include <cmath>


inline void filled(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


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
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-p, -p, p);
    glVertex3f(-p, p, p);
    glVertex3f(p, p, p);
    glVertex3f(p, -p, p);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-p, -p, -p);
    glVertex3f(p, -p, -p);
    glVertex3f(p, p, -p);
    glVertex3f(-p, p, -p);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-p, -p, -p);
    glVertex3f(-p, -p, p);
    glVertex3f(p, -p, p);
    glVertex3f(p, -p, -p);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-p, p, p);
    glVertex3f(-p, p, -p);
    glVertex3f(p, p, -p);
    glVertex3f(p, p, p);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-p, -p, p);
    glVertex3f(-p, -p, -p);
    glVertex3f(-p, p, -p);
    glVertex3f(-p, p, p);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(p, -p, p);
    glVertex3f(p, p, p);
    glVertex3f(p, p, -p);
    glVertex3f(p, -p, -p);

    glEnd();
}
/*

inline void sphere_unit(GLfloat radius, GLint slices, GLint stacks) {
    for (int i = 0; i < stacks; ++i) {
        // Latitude bounds for this stack
        float theta1 = i * M_PI / stacks - M_PI / 2.0f; // Bottom of stack
        float theta2 = (i + 1) * M_PI / stacks - M_PI / 2.0f; // Top of stack

        for (int j = 0; j < slices; ++j) {
            // Longitude bounds for this slice
            float phi1 = j * 2.0f * M_PI / slices; // Left of slice
            float phi2 = (j + 1) * 2.0f * M_PI / slices; // Right of slice

            // Compute vertices for the current quad
            GLfloat v1[3] = {radius * cosf(theta1) * cosf(phi1), radius * sinf(theta1), radius * cosf(theta1) * sinf(phi1)};
            GLfloat v2[3] = {radius * cosf(theta2) * cosf(phi1), radius * sinf(theta2), radius * cosf(theta2) * sinf(phi1)};
            GLfloat v3[3] = {radius * cosf(theta2) * cosf(phi2), radius * sinf(theta2), radius * cosf(theta2) * sinf(phi2)};
            GLfloat v4[3] = {radius * cosf(theta1) * cosf(phi2), radius * sinf(theta1), radius * cosf(theta1) * sinf(phi2)};

            // Normalize the normals (for a unit sphere, divide each vertex by radius to get the normal)
            GLfloat n1[3] = {v1[0] / radius, v1[1] / radius, v1[2] / radius};
            GLfloat n2[3] = {v2[0] / radius, v2[1] / radius, v2[2] / radius};
            GLfloat n3[3] = {v3[0] / radius, v3[1] / radius, v3[2] / radius};
            GLfloat n4[3] = {v4[0] / radius, v4[1] / radius, v4[2] / radius};

            // Draw the two triangles forming the quad
            glBegin(GL_TRIANGLES);

            // Triangle 1
            glNormal3fv(n1);
            glVertex3fv(v1);

            glNormal3fv(n2);
            glVertex3fv(v2);

            glNormal3fv(n3);
            glVertex3fv(v3);

            // Triangle 2
            glNormal3fv(n1);
            glVertex3fv(v1);

            glNormal3fv(n3);
            glVertex3fv(v3);

            glNormal3fv(n4);
            glVertex3fv(v4);

            glEnd();
        }
    }
}
*/
inline void sphere_unit(GLfloat radius, GLint slices, GLint stacks) {
    for (int i = 0; i < stacks; ++i) {
        // Latitude bounds for this stack
        float theta1 = i * M_PI / stacks - M_PI / 2.0f;        // Bottom of stack
        float theta2 = (i + 1) * M_PI / stacks - M_PI / 2.0f;  // Top of stack

        for (int j = 0; j < slices; ++j) {
            // Longitude bounds for this slice
            float phi1 = j * 2.0f * M_PI / slices;            // Left of slice
            float phi2 = (j + 1) * 2.0f * M_PI / slices;      // Right of slice

            // Compute vertices for the current quad
            GLfloat v1[3] = {radius * cosf(theta1) * cosf(phi1), radius * sinf(theta1), radius * cosf(theta1) * sinf(phi1)};
            GLfloat v2[3] = {radius * cosf(theta2) * cosf(phi1), radius * sinf(theta2), radius * cosf(theta2) * sinf(phi1)};
            GLfloat v3[3] = {radius * cosf(theta2) * cosf(phi2), radius * sinf(theta2), radius * cosf(theta2) * sinf(phi2)};
            GLfloat v4[3] = {radius * cosf(theta1) * cosf(phi2), radius * sinf(theta1), radius * cosf(theta1) * sinf(phi2)};

            // Normalize the normals (for a unit sphere, divide each vertex by radius to get the normal)
            GLfloat n1[3] = {v1[0] / radius, v1[1] / radius, v1[2] / radius};
            GLfloat n2[3] = {v2[0] / radius, v2[1] / radius, v2[2] / radius};
            GLfloat n3[3] = {v3[0] / radius, v3[1] / radius, v3[2] / radius};
            GLfloat n4[3] = {v4[0] / radius, v4[1] / radius, v4[2] / radius};

            // Texture coordinates (U, V) for each vertex
            GLfloat t1[2] = {j / (float)slices, i / (float)stacks};           // Bottom-left
            GLfloat t2[2] = {j / (float)slices, (i + 1) / (float)stacks};     // Top-left
            GLfloat t3[2] = {(j + 1) / (float)slices, (i + 1) / (float)stacks}; // Top-right
            GLfloat t4[2] = {(j + 1) / (float)slices, i / (float)stacks};     // Bottom-right

            // Draw the two triangles forming the quad
            glBegin(GL_TRIANGLES);

            // Triangle 1
            glTexCoord2fv(t1); glNormal3fv(n1); glVertex3fv(v1);
            glTexCoord2fv(t2); glNormal3fv(n2); glVertex3fv(v2);
            glTexCoord2fv(t3); glNormal3fv(n3); glVertex3fv(v3);

            // Triangle 2
            glTexCoord2fv(t1); glNormal3fv(n1); glVertex3fv(v1);
            glTexCoord2fv(t3); glNormal3fv(n3); glVertex3fv(v3);
            glTexCoord2fv(t4); glNormal3fv(n4); glVertex3fv(v4);

            glEnd();
        }
    }
}

inline void rect_texture_unit_aux(int N){
	// Bottom left - start of tiling
	glTexCoord2f(0, N);
	glVertex3f(-0.5, -0.5, 0);
	
	// Top left - N tiles up
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.5, 0);
	
	// Top right - N tiles across and up  
	glTexCoord2f(N, 0);
	glVertex3f(0.5, 0.5, 0);

	// Bottom right - N tiles across
	glTexCoord2f(N, N); 
	glVertex3f(0.5, -0.5, 0);
}

inline void rect_texture_unit(int N){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
		rect_texture_unit_aux(N);
    glEnd();
}


inline void cube_texture_unit(int N){
	glEnable(GL_NORMALIZE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
		glTranslatef(0, 0, 0.5);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			rect_texture_unit_aux(N);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, -0.5);
		glRotatef(180, 0, 1, 0);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			rect_texture_unit_aux(N);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0.5, 0);
		glRotatef(90, 1, 0, 0);
		glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			rect_texture_unit_aux(N);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, -0.5, 0);
		glRotatef(270, 1, 0, 0);
		glBegin(GL_QUADS);
			glNormal3f(0, -1, 0);
			rect_texture_unit_aux(N);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS);
			glNormal3f(1, 0, 0);
			rect_texture_unit_aux(N);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.5, 0, 0);
		glRotatef(270, 0, 1, 0);
		glBegin(GL_QUADS);
			glNormal3f(-1, 0, 0);
			rect_texture_unit_aux(N);
		glEnd();
	glPopMatrix();
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
