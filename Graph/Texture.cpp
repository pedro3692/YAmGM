//
// Created by lost on 23/06/17.
//
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string &fileName) {
    int width, height, numComponents;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if (data == NULL) {
        std::cerr << "Unable to load texture: " << fileName << std::endl;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}