#pragma once

const char * getTypeString(GLenum type){
    switch (type) {
        case GL_FLOAT:
            return "float";
        case GL_FLOAT_VEC2:
            return "vec2";
        case GL_FLOAT_VEC3:
            return "vec3";
        case GL_FLOAT_VEC4:
            return "vec4";
        case GL_DOUBLE:
            return "double";
        case GL_INT:
            return "int";
        case GL_UNSIGNED_INT:
            return "unsigned int";
        case GL_BOOL:
            return "bool";
        case GL_FLOAT_MAT2:
            return "mat2";
        case GL_FLOAT_MAT3:
            return "mat3";
        case GL_FLOAT_MAT4:
            return "mat4";
        case GL_TRUE:
            return "true";
        case GL_FALSE:
            return "false";
        default:
            return "?";
    }
}

void QueryAttribs(GLuint vaoHandle){
    GLint numAttribs;
    glGetProgramInterfaceiv(vaoHandle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

    printf("Active input attributes(total %i):\n", numAttribs);
    for (int i = 0; i < numAttribs; ++i)
    {
        GLint results[3];
        glGetProgramResourceiv(vaoHandle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);

        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        glGetProgramResourceName(vaoHandle, GL_PROGRAM_INPUT, i, nameBufSize, NULL, name);
        printf("%-5d %s (%s)\n", results[2], name, getTypeString(results[1]));
        delete[] name;
    }
}