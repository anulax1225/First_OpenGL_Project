#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "../../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../../lib/stb_image/stb_image.h"

#include <iostream>
#include <string>


class Texture {
    public:
        Texture();
        Texture(const char* path, const char* name, bool defaultParams = true);

        void Load(bool flip = true);

        void SetFilters(GLenum all);
        void SetFilters(GLenum mag, GLenum min);

        void SetWrap(GLenum all);
        void SetWrap(GLenum s, GLenum t);

        void Bind();

        int id;
        unsigned int tex;
        const char* name;

    private:
        static int currentId;

        const char* path;
        int width;
        int height;
        int nChannels;

        void generate();
};

#endif