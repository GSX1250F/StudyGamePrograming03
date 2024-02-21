#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	// 描画順序(draworder)が低いほど遠くに置かれる
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
	float GetTexRotation() const { return mTexRotation; }

private:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;			//スプライトの横幅
	int mTexHeight;			//スプライトの縦幅
	float mTexRotation;		//スプライトの回転
};