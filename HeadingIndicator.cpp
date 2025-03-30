#include "HeadingIndicator.h"
#include "Constants.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <cmath>

void drawAirplane() {
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0f, 0.5f);     // Nose
    glVertex2f(0.0f, 0.15f);    // Top center
    glVertex2f(-0.2f, -0.2f);   // Left wing
    glVertex2f(0.0f, 0.15f);     // Back to center
    glVertex2f(0.2f, -0.2f);    // Right wing
    glVertex2f(0.0f, 0.15f);    // Back to top center
    glVertex2f(0.0f, -0.5f);    // Tail
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.1f, -0.4f);   // Left tail fin
    glVertex2f(0.1f, -0.4f);    // Right tail fin
    glEnd();
    glLineWidth(1.0f);
}

void drawHeadingIndicator(float headingDegrees) {
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float aspect = (float)viewport[2] / (float)viewport[3];
    int cx = viewport[2] / 2;
    int cy = viewport[3] / 2;
    float radius = (float)(viewport[2] < viewport[3] ? viewport[2] : viewport[3]) * 0.45f;

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

	// Draw outer circle
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(cosf(angle) * 0.9f / aspect, sinf(angle) * 0.9f);
    }
    glEnd();

	// Draw tick marks (gauge lines)
    for (int i = 0; i < 360; i += 30) {
        float angle = (i + headingDegrees) * DEG2RAD;
        float x1 = cosf(angle) * 0.9f / aspect;
        float y1 = sinf(angle) * 0.9f;
        float x2 = cosf(angle) * 0.85f / aspect;
        float y2 = sinf(angle) * 0.85f;

        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    glColor3f(1.0f, 0.5f, 0.0f);
    drawAirplane();
    glLineWidth(1.0f);
    glPopMatrix();

    // Draw labels
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    const char* labels[] = {
        "N", "33", "30", "W", "24", "21", "S", "15", "12", "E", "6", "3"
    };

    for (int idx = 0; idx < 12; ++idx) {
        int angleDeg = idx * 30;
        float angle = (angleDeg - headingDegrees - 90.0f) * DEG2RAD;
        float labelRadius = radius * 0.9f;
        float x = cx + cosf(angle) * labelRadius;
        float y = cy + sinf(angle) * labelRadius;
        drawList->AddText(ImVec2(x - 6, y - 6), IM_COL32(255, 255, 255, 255), labels[idx]);
    }
}

// HeadingIndicator.h
#pragma once
void drawHeadingIndicator(float headingDegrees);
