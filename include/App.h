/*
 * Application Class Interface
 * Manages the persistent state and lifecycle of the application.
 */
#pragma once

#include <string>
#include <vector>

class App {
public:
    App();
    
    // Lifecycle methods
    bool Init();
    void Update();
    void Cleanup();

    // --- Application State ---
    
    // Camera Settings
    int cameraIndex = 0;
    bool cameraRunning = false;
    float exposure = 0.0f;
    float gain = 1.0f;
    
    // Image Processing Settings
    bool denoiseEnable = false;
    float brightness = 1.0f;
    float contrast = 1.0f;
    int filterType = 0; // 0: None, 1: Gaussian, 2: Median
    
    // Crop Settings
    int cropX = 0, cropY = 0;
    int cropWidth = 640, cropHeight = 480;
    bool autoCrop = false;
    
    // Stitch Settings
    float overlapThreshold = 0.7f;
    int stitchMode = 0; // 0: Fast, 1: Accurate
    bool blendEdges = true;
    
    // Scan Controls
    bool scanInProgress = false;
    float scanProgress = 0.0f;
    std::string currentStatus = "Ready";
    
    // Path Management
    char inputPath[260] = "";
    char outputPath[260] = "";
};


