#include "HeadingIndicator.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

float heading = 0.0f;

void key_callback(GLFWwindow* window, int key, int, int action, int) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_RIGHT)
            heading += 5.0f;
        if (key == GLFW_KEY_LEFT)
            heading -= 5.0f;
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Heading Indicator", nullptr, nullptr);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetKeyCallback(window, key_callback);
    glEnable(GL_LINE_SMOOTH);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawHeadingIndicator(heading);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
