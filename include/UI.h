/*
 * UI Module Interface
 * Contains functions for styling and rendering the application interface.
 */
#pragma once

#include <GLFW/glfw3.h>
#include "App.h"

// Configures the ImGui style with a modern, Windows-inspired theme
void ApplyModernTheme();

// Renders the main user interface components (sidebar, file reader, feedback)
// @param window: The GLFW window context for UI positioning and sizing
// @param app: Reference to the application state
void RenderUI(GLFWwindow *window, App& app);


