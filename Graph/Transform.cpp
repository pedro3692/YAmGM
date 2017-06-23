//
// Created by lost on 23/06/17.
//

#include "Transform.h"
#include <glm/gtx/transform.hpp>

Transform::Transform(const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 scale) :
        position(pos),
        rotation(rot),
        scale(scale) {}

Transform::~Transform() {

}

glm::vec3 &Transform::getPosition() {
    return position;
}

glm::vec3 &Transform::getRotation() {
    return rotation;
}

glm::vec3 &Transform::getScale() {
    return scale;
}

glm::mat4 Transform::getModel() const {
    glm::mat4 posMatrix = glm::translate(position);

    glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
    glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
    glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
    glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

    glm::mat4 scaleMatrix = glm::scale(scale);

    return posMatrix * rotMatrix * scaleMatrix;
}

