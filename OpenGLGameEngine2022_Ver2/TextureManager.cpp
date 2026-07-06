#include "TextureManager.h"
#include "Sprite.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::GetInstance()
{
    if (instance == nullptr) {
        instance = new TextureManager();
    }
    return instance;
}

TextureManager::TextureManager()
{
    textureIDs = new map<const char*, TextureInfo, cmp_str>();
}

TextureManager::~TextureManager()
{
}

TextureInfo TextureManager::LoadImg(const char* imgName)
{
    string path = "Resources/";
    path = path + imgName;
    Sprite s(path.c_str());

    int texID = s.GenTexture();
    TextureInfo info;
    info.textureID = texID;
    info.width = s.width;
    info.height = s.height;

    pair<const char*, TextureInfo> p = make_pair(imgName, info);
    textureIDs->insert(p);

    return info;
}

int TextureManager::GetTextureID(const char* imgName)
{
    int texID = GetTextureInfo(imgName).textureID;
    return texID;
}

TextureInfo TextureManager::GetTextureInfo(const char* imgName)
{
    map<const char*, TextureInfo>::iterator it = textureIDs->find(imgName);

    map<const char*, TextureInfo>::iterator it2;
    cout << "==================" << endl;
    for (it2 = textureIDs->begin() ; it2 != textureIDs->end(); it2++) {
        cout << it2->first << endl;
    }
    cout << "------------------" << endl;

    if (it != textureIDs->end()) {
        return it->second;
    }
    else {
        return LoadImg(imgName);
    }
}


