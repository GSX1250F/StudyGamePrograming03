#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "BackGround.h"
#include "ClearPict.h"
#include "Random.h"

Game::Game()
	:mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mUpdatingActors(false),
	mWindowWidth(1024),
	mWindowHeight(768)
{
}

bool Game::Initialize()
{
	// SDL初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("SDLを初期化できません: %s", SDL_GetError());
		return false;
	}
	// SDLウィンドウを作成
	mWindow = SDL_CreateWindow("Game Programming in C++", 100, 100, mWindowWidth, mWindowHeight, 0);
	if (!mWindow)
	{
		SDL_Log("ウィンドウの作成に失敗しました: %s", SDL_GetError());
		return false;
	}
	// SDLレンダラーを作成
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("レンダラーの作成に失敗しました: %s", SDL_GetError());
		return false;
	}
	// SDL_imageを初期化
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("SDL_imageを初期化できません: %s", SDL_GetError());
		return false;
	}

	Random::Init();		//乱数設定の初期化?

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	// キューにイベントがあれば繰り返す
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			mIsRunning = false;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)	// キーが押されたら実行する
		{
			mIsRunning = false;
		}
		
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->ProcessInput(event);
		}
		mUpdatingActors = false;
	}	
}

void Game::UpdateGame()
{
	// デルタタイムの計算
	// 前のフレームから 16ms 経つまで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// デルタタイムを最大値で制限する
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// すべてのアクターを更新
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// 待ちアクターをmActorsに移動
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 死んだアクターを一時配列に追加
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// 死んだアクターを削除
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// すべてのスプライトコンポーネントを描画
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::LoadData()
{
	//プレイヤーの宇宙船を作成
	mShip = new Ship(this);

	// 小惑星を最初に複数生成
	int initialNumAsteroids = 15;		//初期値
	for (int i = 0; i < initialNumAsteroids; i++)
	{
		AddAsteroid();
	}

	//背景を作成
	new BackGround(this);

	mClearPict = new ClearPict(this);
}

void Game::UnloadData()
{
	// アクターを配列から消去
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// テクスチャを配列から消去
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;

	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// ファイルからロード
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("テクスチャファイルの読み込みに失敗しました %s", filename.c_str());
			return nullptr;
		}

		// サーフェイスからテクスチャを作成
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("サーフェイスからテクスチャに変換するのに失敗しました %s", filename.c_str());
			return nullptr;
		}

		mTextures.emplace(filename.c_str(), tex);
	}
	return tex;
}

void Game::AddActor(Actor* actor)
{
	// アクターが更新中は、待ちアクターに追加する
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// 消去したいアクターが待ちアクターにある場合
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// 配列の一番最後と交換し、消去する
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// 消去したいアクターがアクターにある場合
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// 配列の一番最後と交換し、消去する
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// 更新順で配列に挿入する
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

//Game Specific
void Game::AddAsteroid()
{
	Asteroid* ast = new Asteroid(this);	
	mAsteroids.emplace_back(ast);	//小惑星が増加するときは配列の一番最後に追加する。
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}



