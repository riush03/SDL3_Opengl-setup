Here's a clean, formatted README.md file with your vcpkg setup instructions:

```markdown
# OpenGL Project Setup with vcpkg

This guide explains how to set up an OpenGL project with GLEW, GLFW, GLM, and SDL3 using vcpkg package manager in Visual Studio 2025/2026.

## Prerequisites

- Visual Studio 2025/2026 (with C++ development workload)
- Git installed on your system
- Administrator privileges (for vcpkg integration)

## Installation Steps

### 1. Install vcpkg

Open PowerShell as **Administrator**:

```powershell
# Clone vcpkg repository
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

# Bootstrap vcpkg
.\bootstrap-vcpkg.bat

# Integrate with Visual Studio
.\vcpkg integrate install
```

### 2. Install Required Libraries

```powershell
# Install required libraries (x64)
.\vcpkg install glew:x64-windows glfw3:x64-windows glm:x64-windows sdl3:x64-windows

# Or for x86 architecture
.\vcpkg install glew:x86-windows glfw3:x86-windows glm:x86-windows sdl3:x86-windows

# Note: SDL3 extensions (sdl3-image, sdl3-ttf, sdl3-mixer) might not be available yet
# Check availability with: .\vcpkg search sdl
```

### 3. Create Visual Studio Project

1. Create a new **C++ Console App** in Visual Studio 2025/2026
2. Configure project properties:

#### Project Properties → vcpkg
- ✅ Enable: **Use vcpkg**

#### Project Properties → C/C++ → General
- **Additional Include Directories**: Add:
  ```
  $(VCPKG_ROOT)/installed/x64-windows/include
  ```

#### Project Properties → Linker → General
- **Additional Library Directories**: Add:
  ```
  $(VCPKG_ROOT)/installed/x64-windows/lib
  ```

### 4. Link Libraries

#### Project Properties → Linker → Input
- **Additional Dependencies**: Add:
  ```
  glew32.lib
  glfw3.lib
  SDL3.lib
  opengl32.lib
  ```

### 5. Test Code

Create a simple test to verify the setup:

```cpp
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

int main() {
    // Test GLM
    glm::vec3 testVec(1.0f, 2.0f, 3.0f);
    std::cout << "GLM test: (" << testVec.x << ", " << testVec.y << ", " << testVec.z << ")" << std::endl;
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return -1;
    }
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    if (!window) {
        std::cerr << "Window creation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return -1;
    }
    
    // Initialize SDL3
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL3 initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "All libraries initialized successfully!" << std::endl;
    
    // Cleanup
    SDL_Quit();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
```

## Troubleshooting

### Common Issues

1. **SDL3 not found in vcpkg**
   - SDL3 might be too new for the main vcpkg repository
   - Use `.\vcpkg search sdl` to check available packages
   - Consider using SDL2 as a temporary alternative

2. **Architecture mismatch**
   - Ensure all libraries use the same architecture (x64 or x86)
   - Use consistent triplet: `:x64-windows` or `:x86-windows`

3. **Library linking errors**
   - Verify library paths are correct
   - Check that DLLs are in the executable directory
   - Ensure `opengl32.lib` is included

4. **vcpkg integration not working**
   - Run `.\vcpkg integrate install` as Administrator
   - Restart Visual Studio
   - Check `Tools → Options → vcpkg` in Visual Studio

## File Structure

```
YourProject/
├── src/
│   └── main.cpp
├── README.md
└── vcpkg.json (optional)
```

## Using vcpkg.json (Manifest Mode)

Create `vcpkg.json` in your project root:

```json
{
  "name": "opengl-project",
  "version": "1.0.0",
  "dependencies": [
    "glew",
    "glfw3",
    "glm",
    "sdl3"
  ]
}
```

Then run `vcpkg install` in your project directory.

## Notes

- SDL3 extensions (image, ttf, mixer) may not be available in vcpkg yet
- For production, consider SDL2 which has full vcpkg support
- Always build in `Release` and `Debug` configurations separately
- Copy required DLLs to your output directory

## License

This setup guide is provided as-is. Refer to individual library licenses for usage.
```

## Additional Files to Include

You might also want to create these files:

### **vcpkg.json** (for manifest mode)
```json
{
  "name": "opengl-project",
  "version-string": "1.0.0",
  "dependencies": [
    "glew",
    "glfw3",
    "glm",
    "sdl3"
  ]
}
```

### **.gitignore**
```
# Build outputs
build/
bin/
obj/

# vcpkg
vcpkg_installed/

# Visual Studio
.vs/
*.vcxproj.user
*.sln
*.suo
*.sdf
*.opensdf

# Executables
*.exe
*.dll
*.ilk
*.pdb
```

This README provides clear, step-by-step instructions that users can follow to set up their OpenGL project with vcpkg.
