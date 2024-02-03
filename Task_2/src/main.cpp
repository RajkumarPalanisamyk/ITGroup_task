#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

// Display Window Size
const int windowWidth = 800;
const int windowHeight = 600;

// Constant Factor for Rotation speed
float rotationSpeed = 1.0f;

void readSettingsFromFile() {
    // Read WindMill Speed from settings.txt file , .ini files are genreally prefered
    std::ifstream file("settings.txt");
    if (file.is_open()) {
        file >> rotationSpeed;
        file.close();
    }
}

void updateSettings() {
    // Callforward function for Reading setting from txt file
    readSettingsFromFile();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Exit Sequence for Display window using ESC key
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void drawWindmill() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the windmill tower
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-10, -200);
    glVertex2f(10, -200);
    glVertex2f(10, 0);
    glVertex2f(-10, 0);
    glEnd();

    // Draw three windmill blades
    for (int i = 0; i < 3; ++i) {
        glPushMatrix();
        // multiply the current matrix by a rotation matrix 
        // 3 Triangles at 120 deg are the Blades , i indicates the Blade ID, Time*Rotational speed over one Axis gives us Rotation
        glRotatef(120.0f * i + glfwGetTime() * rotationSpeed, 0.0, 0.0, 1.0);
        glColor3f(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 100);
        glVertex2f(10, 0);
        glVertex2f(-10, 0);
        glEnd();
        glPopMatrix();
    }
}

int main() {

    // Check if GLFW OpenGL is Initialized
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Display Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create Display window
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Windmill", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Check Window status
    while (!glfwWindowShouldClose(window)) {
        updateSettings();
        drawWindmill();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
