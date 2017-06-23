//
// Created by lost on 23/06/17.
//

#ifndef YAMGE_TEXTURE_H
#define YAMGE_TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
public:
    Texture(const std::string &fileName);

    void bind();

    virtual ~Texture();

private:
    GLuint texture;
};


#endif //YAMGE_TEXTURE_H
