#include "UI.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>
#include <filesystem>  // CHANGED: Added for directory listing

// CHANGED: Moved UI state variables from main.cpp to here (global UI state)
static float sliderValue = 0.5f;
static int counter = 0;
static char textBuffer[128] = "";
static char imagePath[260] = "";
static char feedbackBuffer[512] = "";

// CHANGED: Windows-inspired theme with more gray tones and better text contrast
void ApplyModernTheme() {
    ImGuiStyle &style = ImGui::GetStyle();
    
    // CHANGED: Reduced roundness for a more Windows-native appearance
    style.WindowRounding = 4.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
    style.ScrollbarRounding = 8.0f;
    
    // CHANGED: Windows-like padding
    style.WindowPadding = ImVec2(10.0f, 10.0f);
    style.FramePadding = ImVec2(6.0f, 5.0f);
    style.ItemSpacing = ImVec2(8.0f, 7.0f);
    
    // CHANGED: More gray palette with better text readability
    ImVec4 *colors = style.Colors;
    
    // Medium gray backgrounds (less bright white, easier on eyes)
    colors[ImGuiCol_WindowBg] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    
    // Bold dark text for better contrast and readability
    colors[ImGuiCol_Text] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    
    // Header styling with subtle blue (Windows accent)
    colors[ImGuiCol_Header] = ImVec4(0.78f, 0.84f, 0.94f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.80f, 0.94f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.65f, 0.77f, 0.92f, 1.00f);
    
    // Button styling: medium gray with blue hover (Windows-like)
    colors[ImGuiCol_Button] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.68f, 0.80f, 0.95f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.60f, 0.75f, 0.93f, 1.00f);
    
    // Frame backgrounds (input fields, etc.) - light gray
    colors[ImGuiCol_FrameBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    
    // Separator line - medium gray
    colors[ImGuiCol_Separator] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.65f, 0.75f, 0.88f, 1.00f);
    
    // Slider and checkmark - Windows blue accent
    colors[ImGuiCol_SliderGrab] = ImVec4(0.45f, 0.65f, 0.95f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.55f, 0.90f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.60f, 0.95f, 1.00f);
}

// CHANGED: Simplified RenderUI signature - removed all UI state parameters since they're now static
void RenderUI(GLFWwindow *window) {
    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);

    // CHANGED: Panel width adjusted for better proportions
    float panelWidth = 320.0f;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(panelWidth, (float)window_height));

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Sidebar", NULL, window_flags);
    
    // CHANGED: Updated header color to match Windows theme
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.20f, 0.20f, 0.20f, 1.0f), "Main Menu");
    ImGui::Separator();
    ImGui::Spacing();

    // CHANGED: Updated section header color to match Windows theme
    ImGui::TextColored(ImVec4(0.35f, 0.35f, 0.35f, 1.0f), "File Reader");
    ImGui::InputText("Image Path##path", imagePath, 260);
    ImGui::Spacing();
    
    // CHANGED: Replaced Browse with "Read Path" button that reads file contents
    if (ImGui::Button("Read Path", ImVec2(-1, 32))) {
        if (strlen(imagePath) == 0) {
            snprintf(feedbackBuffer, sizeof(feedbackBuffer), "No path specified.");
        } else {
            // CHANGED: Read directory contents and list image filenames instead
            feedbackBuffer[0] = '\0';
            
            try {
                std::filesystem::path dirPath(imagePath);
                
                if (!std::filesystem::exists(dirPath)) {
                    snprintf(feedbackBuffer, sizeof(feedbackBuffer), "Error: Path does not exist.");
                } else if (!std::filesystem::is_directory(dirPath)) {
                    snprintf(feedbackBuffer, sizeof(feedbackBuffer), "Error: Path is not a directory.");
                } else {
                    // List all image files in the directory
                    int imageCount = 0;
                    char* bufPtr = feedbackBuffer;
                    int remainingSize = sizeof(feedbackBuffer);
                    
                    for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
                        if (entry.is_regular_file()) {
                            std::string ext = entry.path().extension().string();
                            // CHANGED: Check for common image extensions
                            if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || 
                                ext == ".bmp" || ext == ".gif" || ext == ".tiff" ||
                                ext == ".JPG" || ext == ".JPEG" || ext == ".PNG" || 
                                ext == ".BMP" || ext == ".GIF" || ext == ".TIFF") {
                                
                                std::string filename = entry.path().filename().string();
                                int written = snprintf(bufPtr, remainingSize, "%s\n", filename.c_str());
                                if (written > 0) {
                                    bufPtr += written;
                                    remainingSize -= written;
                                    imageCount++;
                                }
                                if (remainingSize <= 1) break;
                            }
                        }
                    }
                    
                    if (imageCount == 0) {
                        snprintf(feedbackBuffer, sizeof(feedbackBuffer), "No image files found in directory.");
                    }
                }
            } catch (const std::exception& e) {
                snprintf(feedbackBuffer, sizeof(feedbackBuffer), "Error: %s", e.what());
            }
        }
    }
    
    // CHANGED: Removed Preview Image button
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // CHANGED: Updated Feedback header color to match Windows theme
    ImGui::TextColored(ImVec4(0.35f, 0.35f, 0.35f, 1.0f), "Feedback");
    ImGui::InputTextMultiline("##feedback", feedbackBuffer, (size_t)sizeof(feedbackBuffer), ImVec2(-1, 100), ImGuiInputTextFlags_ReadOnly);
    if (ImGui::Button("Clear Feedback", ImVec2(-1, 28))) {
        feedbackBuffer[0] = '\0';
    }

    ImGui::End();
}
