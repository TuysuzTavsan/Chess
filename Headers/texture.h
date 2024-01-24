#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <memory>

class Texture
{
    std::shared_ptr<unsigned int> texture;
    bool isLoaded;

public:
    Texture();
    ~Texture();

    bool LoadTexture(const std::string& path);
    bool IsLoaded();
    unsigned int GetTextureData();

};



#endif //TEXTURE_H