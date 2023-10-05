#include "Texture.hpp"

int Texture::currentId = 0;

Texture::Texture() { 
    this->id = currentId++;
    this->generate();
}

Texture::Texture(const char* path, const char* name, bool defaultParams) {
    this->path = path;
    this->name = name;
    this->id = currentId++;
    this->generate();
    if (defaultParams) {
        this->SetFilters(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
        this->SetWrap(GL_REPEAT);
    }
}

void Texture::generate() {
    glGenTextures(1, &this->tex);
    glBindTexture(GL_TEXTURE_2D, this->tex);
}

void Texture::Load(bool flip) {
    stbi_set_flip_vertically_on_load(flip);

    unsigned char* data = stbi_load(this->path, &this->width, &this->height, &this->nChannels, 0);

    GLenum colorMode = GL_RGB;
    switch(this->nChannels) {
        case 1:
            colorMode = GL_RED;
            break;
        case 4: 
            colorMode = GL_RGBA;
            break;
    }

    if(data) {
        glBindTexture(GL_TEXTURE_2D, this->id);
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, this->width, this->height, 0, colorMode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Image not loaded at " << this->path << std::endl;
    }
    stbi_image_free(data);
}

void Texture::SetFilters(GLenum all) {
    this->SetFilters(all, all);
}
void Texture::SetFilters(GLenum mag, GLenum min) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
}

void Texture::SetWrap(GLenum all) {
    this->SetWrap(all, all);
}

void Texture::SetWrap(GLenum s, GLenum t) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
