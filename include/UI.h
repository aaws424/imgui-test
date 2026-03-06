#pragma once

#include <GLFW/glfw3.h>

void ApplyModernTheme();
void RenderUI(float &sliderValue, int &counter, char *textBuffer, char *imagePath, char *feedbackBuffer, int feedbackBufSize, GLFWwindow *window);
