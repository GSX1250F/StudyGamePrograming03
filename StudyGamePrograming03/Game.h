#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	void SetRunning(bool isrunning) { mIsRunning = isrunning; }

	//ゲームウィンドウの大きさ
	int mWindowWidth;
	int mWindowHeight;

	//Game-specific	
	void AddAsteroid();
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
	class Ship* GetShip() { return mShip; }
	class ClearPict* GetClearPict() { return mClearPict; }
	
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// テクスチャの配列
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// すべてのアクター
	std::vector<class Actor*> mActors;
	// すべての待ちアクター
	std::vector<class Actor*> mPendingActors;

	// すべての描画されるスプライトコンポーネント
	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// アクターが更新中か
	bool mUpdatingActors;


	//Game-specific
	class Ship* mShip; // プレイヤーの宇宙船
	std::vector<class Asteroid*> mAsteroids; //小惑星
	class ClearPict* mClearPict;	//ゲームクリア画像
};