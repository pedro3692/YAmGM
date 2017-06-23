//
// Created by lost on 23/06/17.
//

#ifndef YAMGE_CAMERA_H
#define YAMGE_CAMERA_H


#include <glm/glm.hpp>

class Camera {
public:
    Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar);

    glm::mat4 getViewProjection() const;

    glm::vec3 &getPosition();

    void moveCamera(int direction, float cameraSpeed);

    enum {
        FORWARD,
        BACKWARD,
        RIGHT,
        LEFT
    };

    virtual ~Camera();

private:
    glm::mat4 perspective;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
};


#endif //YAMGE_CAMERA_H
