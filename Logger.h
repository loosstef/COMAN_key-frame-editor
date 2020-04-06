//
// Created by stef on 17.02.20.
//

#ifndef ANTONGERDELAN_LOGGER_H
#define ANTONGERDELAN_LOGGER_H

#include <GL/glew.h>
#include <iostream>

class Logger {
public:
    static void log_gl_params() {
        GLenum params[] = {
                GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
                GL_MAX_CUBE_MAP_TEXTURE_SIZE,
                GL_MAX_DRAW_BUFFERS,
                GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
                GL_MAX_TEXTURE_IMAGE_UNITS,
                GL_MAX_TEXTURE_SIZE,
                GL_MAX_VARYING_FLOATS,
                GL_MAX_VERTEX_ATTRIBS,
                GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
                GL_MAX_VERTEX_UNIFORM_COMPONENTS,
                GL_MAX_VIEWPORT_DIMS,
                GL_STEREO,
        };
        const char* names[] = {
                "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
                "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
                "GL_MAX_DRAW_BUFFERS",
                "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
                "GL_MAX_TEXTURE_IMAGE_UNITS",
                "GL_MAX_TEXTURE_SIZE",
                "GL_MAX_VARYING_FLOATS",
                "GL_MAX_VERTEX_ATTRIBS",
                "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
                "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
                "GL_MAX_VIEWPORT_DIMS",
                "GL_STEREO",
        };
        printf("GL Context Params:\n");
        char msg[256];
        // integers - only works if the order is 0-10 integer return types
        for (int i = 0; i < 10; i++) {
            int v = 0;
            glGetIntegerv(params[i], &v);
            printf("%s %i\n", names[i], v);
        }
        // others
        int v[2];
        v[0] = v[1] = 0;
        glGetIntegerv(params[10], v);
        printf("%s %i %i\n", names[10], v[0], v[1]);
        unsigned char s = 0;
        glGetBooleanv(params[11], &s);
        printf("%s %u\n", names[11], (unsigned int)s);
        printf("-----------------------------\n");
    }
};

#endif //ANTONGERDELAN_LOGGER_H
