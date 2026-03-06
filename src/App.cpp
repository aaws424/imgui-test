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
