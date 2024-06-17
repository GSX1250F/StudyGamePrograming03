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
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

	void SetTexWidth(int width) { mTexWidth = width; }
	void SetTexHeight(int height) { mTexHeight = height; }


protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;			//スプライトの横幅
	int mTexHeight;			//スプライトの縦幅
};