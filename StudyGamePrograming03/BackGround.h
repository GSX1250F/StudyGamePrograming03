#pragma once
#include "Actor.h"
#include "BGSpriteComponent.h"

class BackGround : public Actor
{
public:
	BackGround(class Game* game);

	void UpdateActor(float deltaTime) override;
	
	void LoadData();

private:
	std::vector<BGSpriteComponent*> mBGsprites;
};

