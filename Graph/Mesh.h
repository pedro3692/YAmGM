//
// Created by lost on 23/06/17.
//

#ifndef YAMGE_MESH_H
#define YAMGE_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "OBJLoader.h"

class Vertex {
public:
    Vertex(const glm::vec3 &pos, const glm::vec2 &texCoord) :
            pos(pos), texCoord(texCoord) {}

    inline glm::vec3 *getPos() { return &pos; }

    inline glm::vec2 *getTexCoord() { return &texCoord; }

private:
    glm::vec3 pos;
    glm::vec2 texCoord;
};

class Mesh {
public:

    Mesh(const std::string &fileName);

    Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices);

    void draw();

    virtual ~Mesh();

private:
    enum {
        POSITION_VB,
        TEXCOORDS_VB,
        INDICES_VB,

        NUM_BUFFERS
    };

    GLuint vertexArrayObject;
    GLuint vertexArrayBuffer[NUM_BUFFERS];
    unsigned int drawCount;

    void initMech(const IndexedModel &model);

};


#endif //YAMGE_MESH_H
