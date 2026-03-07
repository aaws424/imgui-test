#pragma once

#include <GLFW/glfw3.h>

void ApplyModernTheme();
// CHANGED: Simplified RenderUI to take only window parameter - UI state is now managed internally
void RenderUI(GLFWwindow *window);
