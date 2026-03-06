

files setup

MyProject/
├── .vscode/             # VS Code settings (including your vcpkg path)
├── assets/              # Fonts (.ttf), Icons, Images
├── include/             # Header files (.h)
│   ├── App.h            # Main application class
│   └── UI.h             # UI rendering functions
├── src/                 # Source files (.cpp)
│   ├── main.cpp         # Only handles entry point
│   ├── App.cpp          # App lifecycle (init, loop, cleanup)
│   └── UI.cpp           # Your ImGui layouts
├── CMakeLists.txt       # Build instructions
└── .clang-format        # Keeps your code style consistent