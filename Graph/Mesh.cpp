//
// Created by lost on 23/06/17.
//

#include "Mesh.h"

Mesh::Mesh(const std::string &fileName) {
    IndexedModel model = OBJModel(fileName).ToIndexedModel();

    initMech(model);
}

Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices) {
    IndexedModel model;

    for (unsigned int i = 0; i < numVertices; i++) {
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTexCoord());
    }

    for (unsigned int i = 0; i < numIndices; i++) {
        model.indices.push_back(indices[i]);
    }

    initMech(model);
}

Mesh::~Mesh() {
    glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::draw() {
    glBindVertexArray(vertexArrayObject);

    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::initMech(const IndexedModel &model) {
    drawCount = model.indices.size();

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[TEXCOORDS_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffer[INDICES_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0],
                 GL_STATIC_DRAW);


    glBindVertexArray(0);
}
