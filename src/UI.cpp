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
    
    // Windows 11 inspired rounding and padding
    style.WindowRounding    = 8.0f;
    style.FrameRounding     = 4.0f;
    style.GrabRounding      = 4.0f;
    style.PopupRounding     = 8.0f;
    style.ScrollbarRounding = 12.0f;
    style.TabRounding       = 4.0f;
    
    style.WindowBorderSize  = 1.0f;
    style.FrameBorderSize   = 1.0f;
    
    style.WindowPadding     = ImVec2(12.0f, 12.0f);
    style.FramePadding      = ImVec2(8.0f, 4.0f);
    style.ItemSpacing       = ImVec2(8.0f, 8.0f);
    
    ImVec4 *colors = style.Colors;
    
    // Windows 11 Light Themeish palette
    ImVec4 color_bg          = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    ImVec4 color_window_bg   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 color_text        = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    ImVec4 color_primary     = ImVec4(0.00f, 0.45f, 0.84f, 1.00f); // Windows Blue
    ImVec4 color_primary_hv  = ImVec4(0.10f, 0.55f, 0.94f, 1.00f);
    ImVec4 color_border      = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    
    colors[ImGuiCol_Text]                   = color_text;
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = color_window_bg;
    colors[ImGuiCol_ChildBg]                = color_bg;
    colors[ImGuiCol_PopupBg]                = color_window_bg;
    colors[ImGuiCol_Border]                 = color_border;
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    
    colors[ImGuiCol_FrameBg]                = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    
    colors[ImGuiCol_TitleBg]                = color_window_bg;
    colors[ImGuiCol_TitleBgActive]          = color_window_bg;
    colors[ImGuiCol_TitleBgCollapsed]       = color_window_bg;
    
    colors[ImGuiCol_MenuBarBg]              = color_window_bg;
    
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    
    colors[ImGuiCol_CheckMark]              = color_primary;
    colors[ImGuiCol_SliderGrab]             = color_primary;
    colors[ImGuiCol_SliderGrabActive]       = color_primary_hv;
    
    colors[ImGuiCol_Button]                 = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    
    colors[ImGuiCol_Header]                 = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    
    colors[ImGuiCol_Separator]              = color_border;
    colors[ImGuiCol_SeparatorHovered]       = color_primary;
    colors[ImGuiCol_SeparatorActive]        = color_primary_hv;
    
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    
    colors[ImGuiCol_Tab]                    = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_TabActive]              = color_window_bg;
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = color_window_bg;
    
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = color_border;
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = color_primary;
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
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

    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float child_width = (main_content_width - spacing - 20.0f) * 0.5f;
    float child_height = content_height - 10.0f;

    // Live Camera Feed area
    ImGui::BeginChild("LiveFeed", ImVec2(child_width, child_height), true);
    ImGui::Text("LIVE CAMERA FEED");
    ImGui::Separator();
    // Placeholder for video frame
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(p0.x + child_width - 20.0f, p0.y + child_height - 60.0f);
    draw_list->AddRectFilled(p0, p1, IM_COL32(50, 50, 50, 255));
    if (app.cameraRunning) {
        draw_list->AddText(ImVec2(p0.x + 20, p0.y + 20), IM_COL32(0, 255, 0, 255), "[ CAMERA ACTIVE ]");
    } else {
        draw_list->AddText(ImVec2(p0.x + 20, p0.y + 20), IM_COL32(200, 200, 200, 255), "Camera Offline");
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // Stitched Mosaic Preview area
    ImGui::BeginChild("MosaicPreview", ImVec2(child_width, child_height), true);
    ImGui::Text("STITCHED MOSAIC PREVIEW");
    ImGui::Separator();
    ImVec2 m0 = ImGui::GetCursorScreenPos();
    ImVec2 m1 = ImVec2(m0.x + child_width - 20.0f, m0.y + child_height - 60.0f);
    draw_list->AddRectFilled(m0, m1, IM_COL32(30, 30, 40, 255));
    draw_list->AddText(ImVec2(m0.x + 20, m0.y + 20), IM_COL32(255, 255, 255, 200), "Preview will appear here...");
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


