#include "HeadingIndicator.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>


constexpr float DEG2RAD = 3.14159f / 180.0f;

void drawCircle(float r, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * r, sinf(angle) * r);
    }
    glEnd();
}

void drawAirplane() {
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0.5f); // Nose
    glVertex2f(0, -0.5f); // Tail
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glEnd();
}

void drawHeadingIndicator(float headingDegrees) {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);

    // Outer Circle
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.9f, 100);

    // Rotate compass according to heading
    glPushMatrix();
    glRotatef(-headingDegrees, 0.0f, 0.0f, 1.0f);

    // Tick marks
    for (int i = 0; i < 360; i += 30) {
        float rad = i * DEG2RAD;
        glBegin(GL_LINES);
        glVertex2f(cos(rad) * 0.85f, sin(rad) * 0.85f);
        glVertex2f(cos(rad) * 0.75f, sin(rad) * 0.75f);
        glEnd();
    }

    glPopMatrix();

    // Draw airplane in center
    glColor3f(1.0f, 0.5f, 0.0f);
    drawAirplane();

    glPopMatrix();
}
