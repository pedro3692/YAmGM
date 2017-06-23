//
// Created by lost on 23/06/17.
//



#include "Shader.h"

#include <fstream>
#include <iostream>

Shader::Shader(const std::string &fileName) {
    program = glCreateProgram();
    shaders[0] = createShader(loadShader(fileName + ".vs.glsl"), GL_VERTEX_SHADER);
    shaders[1] = createShader(loadShader(fileName + ".fs.glsl"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++) {
        glAttachShader(program, shaders[i]);
    }

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "texCoord");

    glLinkProgram(program);
    checkShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed!");

    glValidateProgram(program);
    checkShaderError(program, GL_VALIDATE_STATUS, true, "Error: Invalid shader program!");

    uniforms[TRANFORM_U] = glGetUniformLocation(program, "transform");
}

Shader::~Shader() {
    for (unsigned int i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }

    glDeleteProgram(program);
}

void Shader::bind() {
    glUseProgram(program);
}


GLuint Shader::createShader(const std::string &text, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0) {
        std::cerr << "Error: Shader creation failed!" << std::endl;
    }

    const GLchar *shaderSourceCode[1];
    GLint shaderSourceCodeLenght[1];

    shaderSourceCode[0] = text.c_str();
    shaderSourceCodeLenght[0] = text.length();

    glShaderSource(shader, 1, shaderSourceCode, shaderSourceCodeLenght);
    glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");

    return shader;
}

void Shader::update(const Transform transform, const Camera &camera) {
    glm::mat4 model = camera.getViewProjection() * transform.getModel();

    glUniformMatrix4fv(uniforms[TRANFORM_U], 1, GL_FALSE, &model[0][0]);
}


std::string Shader::loadShader(const std::string &fileName) {
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage) {
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE) {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

