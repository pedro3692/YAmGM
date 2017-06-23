//
// Created by lost on 23/06/17.
//

#include <iostream>
#include "Window.h"

Window::Window(const std::string &title, int width, int height, bool vSync) : title(title), width(width),
                                                                              height(height), vSync(vSync) {

}

Window::~Window() {
    glfwTerminate();
}

void Window::init() {
    glfwInit();
    glfwDefaultWindowHints(); // optional, the current window hints are already the default
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    // Center our window
    glfwSetWindowPos(
            window,
            (vidmode->width - width) / 2,
            (vidmode->height - height) / 2
    );

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    GLenum status = glewInit();

    if (status != GLEW_OK) {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }


    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    if (isvSync()) {
        glfwSwapInterval(1);
    }

    glfwShowWindow(window);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

const std::string &Window::getTitle() const {
    return title;
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(window);
}

bool Window::isvSync() {
    return vSync;
}

bool Window::isKeyPressed(int keyCode) {
    return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, true); // We will detect this in the rendering loop
    }
}

GLFWwindow *Window::getGLFWWindow() const {
    return window;
}



