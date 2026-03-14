/*
 * UI Module Implementation
 * Implements a structured, multi-panel interface for camera control and image processing.
 */
#include "UI.h"
#include "imgui.h"
#include <cstdio>
#include <string>

/**
 * ApplyModernTheme
 * Defines a clean, gray, professional theme.
 */
void ApplyModernTheme() {
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 0.0f; // Flat design for professional feel
    style.FrameRounding = 2.0f;
    style.GrabRounding = 2.0f;
    style.ScrollbarRounding = 0.0f;
    
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.FramePadding = ImVec2(8.0f, 4.0f);
    style.ItemSpacing = ImVec2(10.0f, 8.0f);
    
    ImVec4 *colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    colors[ImGuiCol_Text] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.50f);
    
    // Accents
    colors[ImGuiCol_Header] = ImVec4(0.80f, 0.85f, 0.95f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.65f, 0.75f, 0.90f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.20f, 0.50f, 0.90f, 1.00f);
}

// Helper for section headers
void SectionHeader(const char* label) {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.4f, 0.7f, 1.0f));
    ImGui::Text("%s", label);
    ImGui::PopStyleColor();
    ImGui::Separator();
}

/**
 * RenderUI
 * Orchestrates the main window layout.
 */
void RenderUI(GLFWwindow *window, App& app) {
    // 1. MAIN MENU BAR
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open Project...")) {}
            if (ImGui::MenuItem("Save Project")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) { glfwSetWindowShouldClose(window, true); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Camera")) {
            if (ImGui::MenuItem("Settings")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Processing")) { ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Crop")) { ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Stitch")) { ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Scan")) { ImGui::EndMenu(); }
        ImGui::EndMainMenuBar();
    }

    // Calculate dimensions
    int ww, wh;
    glfwGetWindowSize(window, &ww, &wh);
    float menu_height = ImGui::GetFrameHeight();
    float status_height = 25.0f;
    float content_height = (float)wh - menu_height - status_height;
    float sidebar_width = 300.0f;
    float main_content_width = (float)ww - sidebar_width;

    // 2. CONTROLS PANEL (SIDEBAR)
    ImGui::SetNextWindowPos(ImVec2(0, menu_height));
    ImGui::SetNextWindowSize(ImVec2(sidebar_width, content_height));
    ImGui::Begin("Controls Panel", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

    if (ImGui::CollapsingHeader("Camera Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Combo("Device", &app.cameraIndex, "Integrated Camera\0External USB\0Network Feed\0\0");
        ImGui::SliderFloat("Exposure", &app.exposure, -5.0f, 5.0f);
        ImGui::SliderFloat("Gain", &app.gain, 1.0f, 10.0f);
        if (ImGui::Button(app.cameraRunning ? "Stop Camera" : "Start Camera", ImVec2(-1, 0))) {
            app.cameraRunning = !app.cameraRunning;
        }
    }

    if (ImGui::CollapsingHeader("Image Processing")) {
        ImGui::Checkbox("Enable Denoising", &app.denoiseEnable);
        ImGui::SliderFloat("Brightness", &app.brightness, 0.5f, 2.0f);
        ImGui::SliderFloat("Contrast", &app.contrast, 0.5f, 2.0f);
        ImGui::Combo("Filter", &app.filterType, "None\0Gaussian Blur\0Median Filter\0\0");
    }

    if (ImGui::CollapsingHeader("Crop Settings")) {
        ImGui::InputInt("X", &app.cropX);
        ImGui::InputInt("Y", &app.cropY);
        ImGui::InputInt("Width", &app.cropWidth);
        ImGui::InputInt("Height", &app.cropHeight);
        ImGui::Checkbox("Auto-detect Edges", &app.autoCrop);
    }

    if (ImGui::CollapsingHeader("Stitch Settings")) {
        ImGui::SliderFloat("Overlap", &app.overlapThreshold, 0.0f, 1.0f);
        ImGui::RadioButton("Fast", &app.stitchMode, 0); ImGui::SameLine();
        ImGui::RadioButton("Accurate", &app.stitchMode, 1);
        ImGui::Checkbox("Blend Edges", &app.blendEdges);
    }

    if (ImGui::CollapsingHeader("Scan Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::Button("Perform Full Scan", ImVec2(-1, 40))) {
            app.scanInProgress = true;
            app.scanProgress = 0.0f;
            app.currentStatus = "Scanning...";
        }
        if (app.scanInProgress) {
            ImGui::ProgressBar(app.scanProgress, ImVec2(-1, 0));
        }
    }

    ImGui::End();

    // 3. MAIN CONTENT AREA (Camera Feed & Mosaic Preview)
    ImGui::SetNextWindowPos(ImVec2(sidebar_width, menu_height));
    ImGui::SetNextWindowSize(ImVec2(main_content_width, content_height));
    ImGui::Begin("ContentArea", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

    float feed_height = content_height * 0.6f;
    float preview_height = content_height - feed_height - 10.0f;

    // Live Camera Feed area
    ImGui::BeginChild("LiveFeed", ImVec2(0, feed_height), true);
    ImGui::Text("LIVE CAMERA FEED");
    ImGui::Separator();
    // Placeholder for video frame
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(p0.x + main_content_width - 40.0f, p0.y + feed_height - 60.0f);
    draw_list->AddRectFilled(p0, p1, IM_COL32(50, 50, 50, 255));
    if (app.cameraRunning) {
        draw_list->AddText(ImVec2(p0.x + 20, p0.y + 20), IM_COL32(0, 255, 0, 255), "[ CAMERA ACTIVE ]");
    } else {
        draw_list->AddText(ImVec2(p0.x + 20, p0.y + 20), IM_COL32(200, 200, 200, 255), "Camera Offline");
    }
    ImGui::EndChild();

    ImGui::Spacing();

    // Stitched Mosaic Preview area
    ImGui::BeginChild("MosaicPreview", ImVec2(0, preview_height), true);
    ImGui::Text("STITCHED MOSAIC PREVIEW");
    ImGui::Separator();
    ImVec2 m0 = ImGui::GetCursorScreenPos();
    ImVec2 m1 = ImVec2(m0.x + main_content_width - 40.0f, m0.y + preview_height - 60.0f);
    draw_list->AddRectFilled(m0, m1, IM_COL32(30, 30, 40, 255));
    draw_list->AddText(ImVec2(m0.x + 20, m0.y + 20), IM_COL32(255, 255, 255, 200), "Preview will appear here after stitching...");
    ImGui::EndChild();

    ImGui::End();

    // 4. STATUS BAR
    ImGui::SetNextWindowPos(ImVec2(0, (float)wh - status_height));
    ImGui::SetNextWindowSize(ImVec2((float)ww, status_height));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 2));
    ImGui::Begin("StatusBar", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
    
    ImGui::Text("Status: %s", app.currentStatus.c_str());
    ImGui::SameLine(ww - 150);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::SameLine(ww - 80);
    ImGui::Text("Cam: %s", app.cameraRunning ? "ON" : "OFF");
    
    ImGui::End();
    ImGui::PopStyleVar();
}


