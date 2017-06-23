//
// Created by lost on 23/06/17.
//

#ifndef YAMGE_SHADER_H
#define YAMGE_SHADER_H

#include <string>
#include "Transform.h"
#include "Camera.h"
#include <GL/glew.h>

class Shader {
public:
    Shader(const std::string &fileName);

    void bind();

    void update(const Transform transform, const Camera &camera);

    virtual ~Shader();

private:
    static const unsigned int NUM_SHADERS = 2;

    enum {
        TRANFORM_U,

        NUM_UNIFORMS
    };

    GLuint program;
    GLuint shaders[NUM_SHADERS];
    GLuint uniforms[NUM_UNIFORMS];

    std::string loadShader(const std::string &fileName);

    void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);

    GLuint createShader(const std::string &text, GLenum shaderType);

};


#endif //YAMGE_SHADER_H
