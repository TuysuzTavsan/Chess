#include <texture.h>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <assert.h>
#include <iostream>

Texture::Texture()
: texture(new unsigned int{0}), isLoaded(false)
{
    glGenTextures(1, this->texture.getP());
    glBindTexture(GL_TEXTURE_2D, *this->texture.getP());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, this->texture.getP());
}

bool Texture::LoadTexture(const std::string& path)
{
    glBindTexture(GL_TEXTURE_2D, *this->texture.getP());
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    assert(data && "STBI_LOAD FAILED");
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
        this->isLoaded = true;
        return true;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
        return false;
    }

}

bool Texture::IsLoaded()
{
    return this->isLoaded;
}

unsigned int Texture::GetTextureData()
{
    return *this->texture.getP();
}