#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "UI.h"

#include <GLFW/glfw3.h>
#include <stdio.h>


int main()
{
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";

    // CHANGED: Make window unresizable and set size to match panel (320x700)
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(320, 700, "File Reader", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    // CHANGED: Set custom modern theme (replaced StyleColorsDark)
    ApplyModernTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main loop
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // CHANGED: Call RenderUI with only window - all UI state managed in UI.cpp
        RenderUI(window);

        // Rendering
        ImGui::Render();
        
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        // CHANGED: Updated background color to match improved modern theme
        glClearColor(0.05f, 0.05f, 0.08f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}