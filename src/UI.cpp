#include "UI.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>

void ApplyModernTheme() {
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 12.0f;

    ImVec4 *colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.25f, 1.00f);
}

void RenderUI(float &sliderValue, int &counter, char *textBuffer, char *imagePath, char *feedbackBuffer, int feedbackBufSize, GLFWwindow *window) {
    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);

    float panelWidth = 300.0f;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(panelWidth, (float)window_height));

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Sidebar", NULL, window_flags);

    ImGui::Text("Main Menu");
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Add to Counter", ImVec2(-1, 36))) { counter++; }
    if (ImGui::Button("Reset All", ImVec2(-1, 36))) { counter = 0; sliderValue = 0.5f; }

    ImGui::Spacing();
    ImGui::Separator();

    ImGui::Text("Images");
    ImGui::Spacing();

    ImGui::InputText("Image Path", imagePath, 260);
    ImGui::SameLine();
    if (ImGui::Button("Browse", ImVec2(70, 0))) {
        // Placeholder: real file dialog integration would go here
        snprintf(feedbackBuffer, feedbackBufSize, "Browse clicked - implement file dialog (not available).");
    }

    if (ImGui::Button("Preview Image", ImVec2(-1, 36))) {
        if (strlen(imagePath) == 0) {
            snprintf(feedbackBuffer, feedbackBufSize, "No image path specified.");
        } else {
            snprintf(feedbackBuffer, feedbackBufSize, "Previewing image(s) in: %s", imagePath);
        }
    }

    if (ImGui::Button("Stitch Images", ImVec2(-1, 36))) {
        if (strlen(imagePath) == 0) {
            snprintf(feedbackBuffer, feedbackBufSize, "Cannot stitch: no image path provided.");
        } else {
            snprintf(feedbackBuffer, feedbackBufSize, "Stitching images in: %s\nStitch complete.", imagePath);
        }
    }

    ImGui::Spacing();
    ImGui::Separator();

    ImGui::Text("Settings");
    ImGui::SliderFloat("Opacity", &sliderValue, 0.0f, 1.0f);
    ImGui::InputText("Label", textBuffer, 128);

    ImGui::Spacing();

    ImGui::Text("Feedback");
    ImGui::InputTextMultiline("##feedback", feedbackBuffer, (size_t)feedbackBufSize, ImVec2(-1, 120), ImGuiInputTextFlags_ReadOnly);
    if (ImGui::Button("Clear Feedback", ImVec2(-1, 30))) {
        feedbackBuffer[0] = '\0';
    }

    ImGui::SetCursorPosY((float)window_height - 60);
    if (ImGui::Button("Exit", ImVec2(-1, 40))) {
        glfwSetWindowShouldClose(window, true);
    }

    ImGui::End();
}
