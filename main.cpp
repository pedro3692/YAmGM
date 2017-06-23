#include <iostream>
#include <glm/vec2.hpp>
#include "Window.h"
#include "Graph/Mesh.h"
#include "Graph/Shader.h"
#include "Graph/Texture.h"


float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


void processInput(Window &window, Camera &camera) {
    float cameraSpeed = 2.5f * deltaTime;

    if (window.isKeyPressed(GLFW_KEY_W))
        camera.moveCamera(camera.FORWARD, cameraSpeed);
    else if (window.isKeyPressed(GLFW_KEY_S))
        camera.moveCamera(camera.BACKWARD, cameraSpeed);
    if (window.isKeyPressed(GLFW_KEY_A))
        camera.moveCamera(camera.RIGHT, cameraSpeed);
    else if (window.isKeyPressed(GLFW_KEY_D))
        camera.moveCamera(camera.LEFT, cameraSpeed);
}

int main() {
    Window window("OGL");
    window.init();

    Shader shader("./res/shaders/basicShader");
//    Texture texture("./res/textures/bricks.jpg");
    Texture texture("./res/textures/grassblock.png");

    Transform transform;
    Camera camera(glm::vec3(0, 0, -3), 70.0f, (float) window.getWidth() / (float) window.getHeight(), 0.01f, 1000.0f);

    Mesh mesh("res/models/cube.obj");

    float counter = 0.0f;

    while (window.isOpen()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, camera);

        window.clear(0.2f, 0.3f, 0.3f, 1.0f);


        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);

        transform.getPosition().x = sinCounter;
        transform.getPosition().z = cosCounter;
        transform.getRotation().x = counter * 2;
        transform.getRotation().y = counter * 2;
        transform.getRotation().z = counter * 2;
        //transform.getScale() = glm::vec3(cosCounter, cosCounter, cosCounter);

        shader.bind();
        texture.bind();
        shader.update(transform, camera);
        mesh.draw();


        counter += 0.01f;
        window.update();
    }

    return 0;
}
