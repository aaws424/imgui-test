// CHANGED: Marked as UNUSED - this class is not currently used in the application
// TODO: Remove this file and include/App.h if not needed in the future
#include "App.h"
#include <iostream>

bool App::Init() {
    std::cout << "Init\n";
    return true;
}

void App::Loop() {
    std::cout << "Loop\n";
}

void App::Cleanup() {
    std::cout << "Cleanup\n";
}
