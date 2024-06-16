#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include <string>

class BackGround : public Actor
{
public:
	BackGround(class Game* game);
	~BackGround();

	void Update(float deltaTime);
	
	void LoadData();

private:
	struct BGTexture
	{
		SpriteComponent* sprite;
		Vector2 BGpos;
		float scrollSpeed;
	};
	std::vector<BGTexture> mBGTextures;
};

