/*
 * Main Entry Point
 * Initializes the graphics context and manages the top-level application lifecycle.
 */
#include "App.h"
#include "UI.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

int main()
{
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    // Set OpenGL/GLSL versions
    const char* glsl_version = "#version 130";

    // Configure window: larger size for multi-panel layout, resizable
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(1280, 850, "Advanced Image Processor", NULL, NULL);
    if (window == NULL)
        return 1;
        
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    // Enable docking if needed in the future (optional)
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    // Initialize the App state
    App app;
    if (!app.Init()) {
        printf("Failed to initialize App state\n");
        return 1;
    }

    // Apply the custom modern theme
    ApplyModernTheme();

    // Bind ImGui to GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main Control Loop
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();

        // Start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Update application logic (e.g., progress bars, status changes)
        app.Update();

        // RUN UI RENDER LOGIC
        // We pass the app reference so the UI can modify and display application state
        RenderUI(window, app);


        // Finalize frame and clear screen
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        // Background color matches the theme window background
        glClearColor(0.85f, 0.85f, 0.85f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        // Render draw data
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Shutdown and Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


