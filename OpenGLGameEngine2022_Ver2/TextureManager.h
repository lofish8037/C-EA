#pragma once
#include "Engine.h"
#include <map>

struct cmp_str
{
	bool operator()(char const* a, char const* b) const
	{
		return std::strcmp(a, b) < 0;
	}
};

struct TextureInfo
{
	int textureID;
	int width;
	int height;
};

class TextureManager
{
public:
	static TextureManager* instance;

public:
	static TextureManager* GetInstance();

public:
	TextureManager();
	~TextureManager();

	TextureInfo LoadImg(const char* imgName);
	int GetTextureID(const char* imgName);
	TextureInfo GetTextureInfo(const char* imgName);

public:
	map<const char*, TextureInfo, cmp_str>* textureIDs;
};