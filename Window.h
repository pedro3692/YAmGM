//
// Created by lost on 23/06/17.
//

#ifndef YAMGE_WINDOW_H
#define YAMGE_WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const std::string &title = "DefaultTitle", int width = 800, int height = 600, bool vSync = true);

    void init();

    void update();

    void clear(float r, float g, float b, float a);

    int getWidth() const;

    int getHeight() const;

    const std::string &getTitle() const;

    bool isOpen();

    bool isvSync();

    bool isKeyPressed(int keyCode);

    GLFWwindow *getGLFWWindow() const;

    virtual ~Window();

private:
    int width;
    int height;
    const std::string &title;
    bool vSync;

    GLFWwindow *window;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

};


#endif //YAMGE_WINDOW_H
