//
// Created by lost on 23/06/17.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar) {
    perspective = glm::perspective(fov, aspect, zNear, zFar);
    position = pos;
    forward = glm::vec3(0, 0, 1);
    up = glm::vec3(0, 1, 0);
}

Camera::~Camera() {

}

glm::mat4 Camera::getViewProjection() const {
    return perspective * glm::lookAt(position, position + forward, up);
}

glm::vec3 &Camera::getPosition() {
    return position;
}

void Camera::moveCamera(int direction, float cameraSpeed) {

    switch (direction) {
        case FORWARD :
            position += cameraSpeed * forward;
            break;
        case BACKWARD :
            position -= cameraSpeed * forward;
            break;
        case RIGHT :
            position -= glm::normalize(glm::cross(forward, up)) * cameraSpeed;
            break;
        case LEFT :
            position += glm::normalize(glm::cross(forward, up)) * cameraSpeed;
            break;
        default:
            break;
    }

}

