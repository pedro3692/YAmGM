//
// Created by lost on 23/06/17.
//

#ifndef YAMGE_TRANSFORM_H
#define YAMGE_TRANSFORM_H

#include <glm/glm.hpp>

class Transform {
public:
    Transform(const glm::vec3 &pos = glm::vec3(), const glm::vec3 &rot = glm::vec3(),
              const glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

    glm::mat4 getModel() const;

    glm::vec3 &getPosition();

    glm::vec3 &getRotation();

    glm::vec3 &getScale();

    virtual ~Transform();

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

};


#endif //YAMGE_TRANSFORM_H
