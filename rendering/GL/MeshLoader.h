#pragma once

static DrawDetails UploadMesh(const GLfloat* verts, const GLfloat* colors, const int v_count, const GLuint* elems, const int e_count){
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    // Populate the position buffers
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), verts, GL_STATIC_DRAW);
    // Populate the color buffers
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    // Create and set up the Vertex Array Object (VAO)
    GLuint vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0); // Vertex position
    glEnableVertexAttribArray(1); // Vertex color

    glBindVertexBuffer(0, positionBufferHandle, 0, sizeof (GLfloat) * 3);
    glBindVertexBuffer(1, colorBufferHandle, 0, sizeof (GLfloat) * 3);

    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0); // Map to shader
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(1, 1); // Map to shader

    GLuint elemHandle;
    glGenBuffers(1, &elemHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_count * sizeof(GLuint), elems, GL_STATIC_DRAW);

    return DrawDetails(vaoHandle, static_cast<uint32_t>(e_count));
}

static void UnloadMesh(std::vector<DrawDetails>& details){
    for(auto& d : details){
        glDeleteBuffers(1, &d.vao);
    }
    details.clear();
}