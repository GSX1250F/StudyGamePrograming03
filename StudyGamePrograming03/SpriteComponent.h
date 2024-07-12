#pragma once
#include "Component.h"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
	// •`‰æ‡˜(draworder)‚ª’á‚¢‚Ù‚Ç‰“‚­‚É’u‚©‚ê‚é
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class SDL_Renderer* renderer);
	
	virtual void SetTexture(class SDL_Texture* texture);
	SDL_Texture* GetTexture() const { return mTexture; }

	int GetDrawOrder() const { return mDrawOrder; }
	void SetTexWidth(int width) { mTexWidth = width; }
	int GetTexWidth() const { return mTexWidth; }
	void SetTexHeight(int height) { mTexHeight = height; }
	int GetTexHeight() const { return mTexHeight; }
	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }
	
private:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	bool mVisible;
};