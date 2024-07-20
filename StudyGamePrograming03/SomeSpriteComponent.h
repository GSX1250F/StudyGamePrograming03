#pragma once
#include "SpriteComponent.h"
#include <vector>

class SomeSpriteComponent : public SpriteComponent
{
public:
	SomeSpriteComponent(class Actor* owner, int drawOrder);

	void SetSomeTextures(std::vector<SDL_Texture*> textures) { mSomeTextures = textures; }
	void SetTextureFromId(int id) { SetTexture(mSomeTextures[id]); }

private:
	std::vector<SDL_Texture*> mSomeTextures;		//すべてのテクスチャ
};