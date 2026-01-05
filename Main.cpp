#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return -1;
    }

    // Initialize SDL3
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL3 initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    // GLFW window creation
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL + SDL3 Test", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return -1;
    }

    // GLM test
    glm::vec3 position(1.0f, 2.0f, 3.0f);
    std::cout << "GLM Vector: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

    // SDL3 test
    std::cout << "SDL3 Version: " << SDL_GetVersion() << std::endl;

    // OpenGL test
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    SDL_Quit();

    return 0;
}
