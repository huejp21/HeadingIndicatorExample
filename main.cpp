#include "HeadingIndicator.h"
#include "Constants.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <cmath>

float heading = 0.0f;

void setupImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
}

void cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main() {
    if (!glfwInit()) return -1;

	// setup window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Heading Indicator", nullptr, nullptr);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    glewInit();

    setupImGui(window);

	// render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw angle slider
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, 70), ImGuiCond_Always);
        ImGui::Begin("Heading Control", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SliderFloat("(degrees)", &heading, 0.0f, 359.0f, "%.0f");
        ImGui::End();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawHeadingIndicator(heading);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

	// Cleanup window
    cleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}