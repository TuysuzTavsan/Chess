#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <ptr.h>

class Texture
{
    SoftPtr<unsigned int> texture;
    bool isLoaded;

public:
    Texture();
    ~Texture();

    bool LoadTexture(const std::string& path);
    bool IsLoaded();
    unsigned int GetTextureData();

};



#endif //TEXTURE_H