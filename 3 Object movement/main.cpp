#include <GLFW/glfw3.h>
#include <cmath>
#include <stdio.h>

float positionY = 0.0f; // Position for the up and down movement
float positionZ = 0.0f; // Position for the forward and backward movement
float angle = 0.0f;     // Angle for the rotation

static void drawObject(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();
}

void static updatePositions() {
    // Update the first object's position (up and down)
    positionY = sin(glfwGetTime()) * 0.5f;

    // Update the second object's position (forward and backward)
    positionZ = sin(glfwGetTime()) * 1.0f;

    // Update the third object's angle (rotation)
    angle += 1.0f; // Rotate at a constant speed
}

void checkOpenGLError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %d\n", err);
    }
}

void static render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Move the camera back a bit
    glTranslatef(0.0f, 0.0f, -10.0f);

    // Draw first object (moving up and down)
    drawObject(-2.0f, positionY, 0.0f);

    // Draw second object (moving forward and backward)
    drawObject(0.0f, 0.0f, positionZ);

    // Draw third object (rotating)
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    drawObject(0.0f, 0.0f, 0.0f);
    glPopMatrix();

    checkOpenGLError();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    float aspect = (float)width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-aspect * 5, aspect * 5, -5, 5, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Objects", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initial viewport and projection setup
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        updatePositions();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}