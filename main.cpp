#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

// new theme
void ApplyModernTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    // --- Visual Rounding ---
    style.WindowRounding = 5.0f;       // Slightly rounded windows
    style.FrameRounding = 4.0f;        // Rounded buttons and inputs
    style.GrabRounding = 4.0f;         // Rounded sliders
    style.ScrollbarRounding = 12.0f;   // Fully rounded scrollbars

    // --- Modern Color Palette (Deep Charcoal & Soft Blue) ---
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]          = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    colors[ImGuiCol_Header]            = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_HeaderHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_Button]            = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_FrameBg]           = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]    = ImVec4(0.24f, 0.24f, 0.25f, 1.00f);
}
int main()
{
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";

    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Test Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ApplyModernTheme();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // UI variables
    float sliderValue = 0.5f;
    int counter = 0;
    char textBuffer[128] = "Type here";

    // Main loop
  while (!glfwWindowShouldClose(window)){
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. GET CURRENT WINDOW SIZE
    // We need this to make the panel span the full height of the app
    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);

    // 2. SET THE PANEL POSITION AND SIZE
    // We set the position to (0,0) and the height to match the window height
    float panelWidth = 250.0f; 
    ImGui::SetNextWindowPos(ImVec2(0, 0)); 
    ImGui::SetNextWindowSize(ImVec2(panelWidth, (float)window_height));

    // 3. DEFINE WINDOW FLAGS
    // This makes it feel like a "UI Panel" rather than a floating window
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;   // Remove the top bar
    window_flags |= ImGuiWindowFlags_NoMove;       // Prevent user from dragging it
    window_flags |= ImGuiWindowFlags_NoResize;     // Prevent user from changing size
    window_flags |= ImGuiWindowFlags_NoCollapse;   // Prevent hiding via double-click
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; // Keep it in the background

    // 4. CREATE THE WINDOW
    ImGui::Begin("Sidebar", NULL, window_flags);

    ImGui::Text("Main Menu");
    ImGui::Separator(); // Adds a horizontal line
    ImGui::Spacing();   // Adds some vertical breathing room

    // --- ADDING MORE BUTTONS ---

    // Button 1: Increments your counter
    if (ImGui::Button("Add to Counter", ImVec2(-1, 40))) { // -1 width fills the panel
        counter++;
    }

    // Button 2: Resets the counter
    if (ImGui::Button("Reset All", ImVec2(-1, 40))) {
        counter = 0;
        sliderValue = 0.5f;
    }

    ImGui::Spacing();
    ImGui::Separator();

    // Input fields
    ImGui::Text("Settings");
    ImGui::SliderFloat("Opacity", &sliderValue, 0.0f, 1.0f);
    ImGui::InputText("Label", textBuffer, IM_ARRAYSIZE(textBuffer));

    // Button 3: A simple exit button
    ImGui::SetCursorPosY((float)window_height - 50); // Move "Exit" to the bottom
    if (ImGui::Button("Quit App", ImVec2(-1, 30))) {
        glfwSetWindowShouldClose(window, true);
    }

    ImGui::End();

    // --- RENDERING ---
    ImGui::Render();
    
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    
    // Background color (matching the "empty" space next to the sidebar)
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
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